# FoMT 渲染架构深度分析

## 文件导航

| 文件 | 内容 |
|------|------|
| `include/gbaio.h` | GBA硬件寄存器定义(DISPCNT, BGxCNT, DMA, 调色板等) |
| `include/decomp/graphics.hh` | 图形系统结构体(TextBox, VRAM管理, Tile分配) |
| `include/decomp/script_scene.hh` | GameScene结构体 |
| `include/scene.hh` | 场景系统基类 |
| `asm/scene.s` | SceneMain循环 |
| `asm/game_state.s` | 游戏状态、地图加载 |
| `asm/data/data_080F9EB8.s` | MapData数据表 |
| `src/crt0.s` | ROM入口和初始化 |

## 一、GBA硬件图形管线

### 1.1 寄存器映射

GBA图形硬件通过以下寄存器配置:

| 地址 | 名称 | 功能 |
|------|------|------|
| 0x04000000 | REG_DISPCNT | 显示控制(模式、层开关、HBlank等) |
| 0x04000004 | REG_DISPSTAT | 显示状态(VBlank/HBlank/VCounter) |
| 0x04000006 | REG_VCOUNT | 当前扫描线 |
| 0x04000008 | REG_BG0CNT | 背景层0控制 |
| 0x0400000A | REG_BG1CNT | 背景层1控制 |
| 0x0400000C | REG_BG2CNT | 背景层2控制(主地图) |
| 0x0400000E | REG_BG3CNT | 背景层3控制 |
| 0x04000010-1E | REG_BGxHOFS/VOFS | 背景层滚动偏移 |
| 0x04000020-3E | REG_BG2PA-REG_BG3PD | 仿射变换参数 |
| 0x04000040-4A | REG_WINxH/V/WININ/OUT | 窗口控制 |
| 0x04000050-54 | REG_BLDCNT/ALPHA/Y | 混合/透明度 |

### 1.2 内存映射

| 地址范围 | 大小 | 功能 |
|----------|------|------|
| 0x05000000-0x050003FF | 1KB | BG调色板(256色调色板或16色调色板x16) |
| 0x05000400-0x050005FF | 512B | OBJ调色板 |
| 0x06000000-0x06017FFF | 96KB | VRAM(用于tile数据、tilemap、OBJ) |
| 0x06000000-0x0600FFFF | 64KB | BG tile数据 |
| 0x06010000-0x06017FFF | 32KB | OBJ tile数据 |

### 1.3 BGCNT(BG控制寄存器)格式

每个BGxCNT是16位寄存器:
```
bits [0-1]:  优先级(0最高,3最低)
bits [2-3]:  tilemap数据所在的charblock(每块16KB)  
bits [4-5]:  未使用/mosaic
bit [6]:     256色调色板/16色(每格256色或16色)
bits [7-12]: tilemap所在的screenblock(每块2KB)
bits [13]:   外部显示区
bits [14-15]:地图大小(0=32x32,1=64x32,2=32x64,3=64x64 tiles)
```

## 二、地图加载流程

### 2.1 GetMapData函数

```
GetMapData(map_id):
    return 0x08105EDC + map_id * 40(0x28)
```

36字节的MapData结构:
```
+0x00 packed_img     - 压缩的tileset指针(32KB=1024tiles)
+0x04 packed_pal1    - 压缩的调色板1指针(480B)
+0x08 packed_pal2    - 压缩的调色板2指针(480B)
+0x0C packed_tiles1  - 压缩的tilemap层1指针
+0x10 packed_tiles2  - 压缩的tilemap层2指针
+0x14 packed_tiles3  - 压缩的tilemap层3指针
+0x18 terrain_info   - terrain属性数组指针(每项4字节,bit0=碰撞)
+0x1C terrain_map    - 每格terrain索引(w*h字节)
+0x20 width          - 地图宽度(tiles)
+0x22 height         - 地图高度(tiles)
+0x24 is_interior    - 室内标志
```

### 2.2 地图进入流程

1. **场景切换**: SceneMain调用当前AScene的Run()
2. **GameScene::Run()**: 处理地图逻辑循环
3. **地图加载**: 调用GetMapData(map_id)获取MapData
4. **Tile解压**: 解压packed_img(tileset)→上传到VRAM(0x06000000+)
5. **调色板上传**: 解压packed_pal→上传到调色板RAM(0x05000000)
6. **Tilemap设置**: 解压packed_tiles1→写入VRAM tilemap区
7. **BG配置**: 设置REG_BGxCNT指定tile数据位置、tilemap位置、大小
8. **相机设置**: 计算相机边界(MapData.width*8-240, height*8-160)
9. **地形加载**: 处理terrain_info和terrain_map建立碰撞

### 2.3 Popuri压缩格式

格式: 魔数0x70(1B) + 预期解压大小(3B) + 格式字节(1B) + 数据(bitstream)

格式字节分解:
```
bits[2:0] = lzss_fmt (0-4: 不同的LZSS变体)
bits[4:3] = atom_fmt (0=raw, 1=Huff4, 2=Huff8)
bits[7:5] = diff_fmt (0-4: 不同的差值滤波器)
```

Farm tilemap各层格式:
- Layer1: "134" (Huff4 + LZSS3 + diff4)
- Layer2: "130" (Huff4 + LZSS3 + diff0)
- Layer3: 非popuri(magic=0x0B, 另一格式)

## 三、场景系统

### 3.1 场景生命周期

```
AScene基类
  |-- Run() = 0 (纯虚, 返回下一个场景)
  |-- ~AScene() (析构, 清理)

场景切换:
  SceneMain:
    loop:
      current_scene->Run() → SmartPtr<AUnk_0800080C>
        AUnk_0800080C->vfunc_0C() → SmartPtr<AScene>
      销毁旧场景 → 切换到新场景
```

### 3.2 GameScene

GameScene是实际游戏场景,处理:
- 地图渲染
- NPC更新
- 玩家控制
- 脚本执行
- 实体交互

## 四、房屋/建筑设计

建筑在FoMT中不是独立的数据结构,而是通过组合实现:

1. **视觉**: tilemap中的一组tile拼成建筑图形
2. **碰撞**: terrain_map中对应区域设为blocked
3. **交互**: 门/入口通过Entity系统分配脚本ID
4. **NPC路径**: NPC日程表(WayPoint路径)绕过建筑

所以"建筑"= tilemap图形 + terrain碰撞 + entity门触发器

## 五、Entity系统

- Entity函数表: 0x080E602C (66个地图各一个函数指针)
- 仅有map 2(农场)和map 5(北镇)有实际entity handler
- 其他地图使用空handler (0x08000639)
- Entity在运行时动态创建(C++对象),数据不存储在静态表中

## 六、NPC系统

- 35个NPC entity创建函数(对应entity type 0-34)
- 每个NPC有ScheduleInfo(日程表)
- 日程=时间→路径映射
- 路径PathInfo: 起点坐标+地图ID + 行走路径点
- NPC的selector函数决定当天使用哪个日程

## 七、调试/工具接口

可以直接读取MapData验证:
```
python3 tools/decode_map_data_table.py --rom baserom.gba
python3 tools/edit_terrain.py fomt.gba --map 2 --info
```

## 八、渲染数据流总结

```
MapData
 ├── packed_img → 解压 → Tile VRAM (0x06000000)
 ├── packed_pal → 解压 → Palette RAM (0x05000000)
 ├── packed_tiles1/2/3 → 解压 → BG Tilemap (VRAM screenblock)
 ├── terrain_info + terrain_map → RAM → Collision system
 ├── width/height → Camera bounds → REG_BGxHOFS/VOFS limit
 └── is_interior → 室内/室外 → BG显示配置切换
```

## 九、房屋/建筑数据结构

### 9.1 建筑 = 三层组合

建筑在FoMT中不是独立的数据结构，而是三个系统叠加:

1. **视觉层** — tilemap中的一组tile拼成建筑图形(屋顶、墙壁、门)
2. **碰撞层** — terrain_map对应区域设为blocked(terrain_info中bit0=1)
3. **交互层** — Entity系统在门位置放置触发器，关联脚本ID

### 9.2 建筑数据存储

| 系统 | 数据位置 | 格式 |
|------|----------|------|
| 建筑图形 | MapData.packed_tiles1/2/3 | 每格2字节(tile index+palette+flip) |
| 建筑碰撞 | MapData.terrain_info + terrain_map | 属性数组 + 每格索引 |
| 门触发器 | Entity函数表(0x080E602C) | 运行时创建，不存储在静态表 |
| 内部空间 | 独立map_id + GameData.PlayerHouse | 另一张地图+房屋物品数据 |

### 9.3 PlayerHouse数据

PlayerHouse结构体(0x22C字节)，包含:
- house_size (2bit): 房屋大小(小/中/大)
- 物品格: 64个ItemEx(4字节每个)
- 工具格: 64个ToolEx(2字节每个)
- 房屋标志位
- 额外数据

### 9.4 建筑与内部地图的关联

门Entity → script(如script_167) → Proc016(内部map_id, x, y)

所以建筑外部门触发脚本，脚本用Proc016传送到内部地图。

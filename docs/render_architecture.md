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
````
bits [0-1]:  优先级(0最高,3最低)
bits [2-3]:  tilemap数据所在的charblock(每块16KB)  
bits [4-5]:  未使用/mosaic
bit [6]:     256色调色板/16色(每格256色或16色)
bits [7-12]: tilemap所在的screenblock(每块2KB)
bits [13]:   外部显示区
bits [14-15]:地图大小(0=32x32,1=64x32,2=32x64,3=64x64 tiles)
````

## 二、地图加载流程

### 2.1 GetMapData函数

````
GetMapData(map_id):
    return 0x08105EDC + map_id * 40(0x28)
````

36字节的MapData结构:
````
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
````

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
````
bits[2:0] = lzss_fmt (0-4: 不同的LZSS变体)
bits[4:3] = atom_fmt (0=raw, 1=Huff4, 2=Huff8)
bits[7:5] = diff_fmt (0-4: 不同的差值滤波器)
````

Farm tilemap各层格式:
- Layer1: "134" (Huff4 + LZSS3 + diff4)
- Layer2: "130" (Huff4 + LZSS3 + diff0)
- Layer3: 非popuri(magic=0x0B, 另一格式)

## 三、场景系统

### 3.1 场景生命周期

````
AScene基类
  |-- Run() = 0 (纯虚, 返回下一个场景)
  |-- ~AScene() (析构, 清理)

场景切换:
  SceneMain:
    loop:
      current_scene->Run() → SmartPtr<AUnk_0800080C>
        AUnk_0800080C->vfunc_0C() → SmartPtr<AScene>
      销毁旧场景 → 切换到新场景
````

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
````
python3 tools/decode_map_data_table.py --rom baserom.gba
python3 tools/edit_terrain.py fomt.gba --map 2 --info
````

## 八、渲染数据流总结

````
MapData
 ├── packed_img → 解压 → Tile VRAM (0x06000000)
 ├── packed_pal → 解压 → Palette RAM (0x05000000)
 ├── packed_tiles1/2/3 → 解压 → BG Tilemap (VRAM screenblock)
 ├── terrain_info + terrain_map → RAM → Collision system
 ├── width/height → Camera bounds → REG_BGxHOFS/VOFS limit
 └── is_interior → 室内/室外 → BG显示配置切换
````

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

## 十、精灵/OAM渲染系统

### 10.1 角色渲染流程

````
Entity → AActorEntity → SpriteAnimator → OAM → GBA硬件显示
````

1. AActorEntity设置了动画ID和朝向
2. RefreshSprite()调用func_0805E860()更新精灵
3. func_0805E860()配置GBA的OAM(Object Attribute Memory, 0x07000000)
4. GBA硬件在每个扫描线读取OAM，在指定位置渲染精灵

### 10.2 OAM(对象属性内存)格式

GBA的OAM位于0x07000000，每个对象占用8字节:
````
byte[0]: Y坐标
byte[1]: X坐标
byte[2]: tile索引 + 旋转/缩放标志
byte[3]: 属性0(调色板、翻转、模式、形状)
byte[4-5]: 属性1(大小、形状)
byte[6-7]: 属性2(tile索引高位、优先级、调色板)
````

### 10.3 SpriteAnimator结构

SpriteAnimator管理精灵的动画状态:
- 当前帧
- 动画速度
- 循环模式
- 帧序列指针

### 10.4 精灵数据来源

- 精灵tile数据存储在ROM中(非MapData)
- 通过DMA传输到OBJ VRAM(0x06010000)
- OBJ调色板存储在0x05000400

### 10.5 渲染层顺序

````
BG0: UI/文本(优先级最高)
BG1: 地图细节
BG2: 主地图
BG3: 辅助地图/特效
OBJ: 角色/NPC/物品(在BG之上或之间)
````

## 十一、DMA/VRAM传输系统

### 11.1 GBA BIOS函数

| 函数 | 用途 |
|------|------|
| CpuSet | 16位内存拷贝(用于VRAM传输) |
| CpuFastSet | 32位内存拷贝(高效批量传输) |

### 11.2 DMA寄存器

| 地址 | 名称 | 功能 |
|------|------|------|
| 0x040000B0 | REG_DMA0SAD | DMA0源地址 |
| 0x040000D4 | REG_DMA3SAD | DMA3源地址(用于VRAM传输) |
| 0x040000D8 | REG_DMA3DAD | DMA3目标地址 |
| 0x040000DC | REG_DMA3CNT | DMA3控制(大小、模式、使能) |

### 11.3 传输配置

DMA控制寄存器格式:
- bits[0-1]: 目标地址控制(递增/递减/固定)
- bits[2-3]: 源地址控制(递增/递减/固定)
- bit[4]: 重复
- bit[5]: 16/32位传输
- bit[6]: DREQ
- bits[12-13]: 启动时机(立即/VBlank/HBlank/专用)
- bit[14]: 中断使能
- bit[15]: 使能

### 11.4 Tile上传流程

````
1. 解压packed_img → 临时缓冲区
2. 设置DMA源=临时缓冲区, 目标=0x06000000(VRAM)
3. 启动DMA传输
4. 等待DMA完成
5. 继续上传调色板和tilemap
```

## 十二、视频模式配置

### 12.1 DISPCNT初始化

```c
// main_reset.c: 复位时关闭显示
REG_DISPCNT = 0x0080;  // Force Blank (bit 7)
```

### 12.2 视频模式位定义

REG_DISPCNT (16位):
```
bit[0-2]: 视频模式(0-5):
  模式0: 4个BG层(字符模式)
  模式1: 2个BG层 + 1个仿射BG
  模式2: 2个仿射BG层
bit[3]:  保留/GBFrame
bit[4]:  HBlank Interval
bit[5]:  OBJ映射(1=1D映射, 0=2D映射)
bit[6]:  强制Blank
bit[7]:  显示BG0
bit[8]:  显示BG1
bit[9]:  显示BG2
bit[10]: 显示BG3
bit[11]: 显示OBJ
bit[12]: 显示窗口1
bit[13]: 显示窗口2
bit[14]: 显示OBJ窗口
bit[15]: 显示模式
```

### 12.3 FoMT的显示配置

游戏使用 **模式0**(字符模式)显示地图:
- BG0: UI/对话框(优先级最高)
- BG1: 地图上层细节(树冠、屋顶等)
- BG2: 主地图地面
- BG3: 预留/特效
- OBJ: 角色、NPC、物品精灵

### 12.4 BG控制寄存器配置

每个BG的REG_BGxCNT配置:
- Char Base Block: 指定tile数据在VRAM中的位置(每块16KB)
- Screen Base Block: 指定tilemap在VRAM中的位置(每块2KB)
- 大小: 32x32 / 64x32 / 32x64 / 64x64
- 调色板模式: 16色/格(默认)或256色/格

## 十三、相机/滚动系统

### 13.1 滚动硬件

GBA通过以下寄存器控制每个BG层的滚动偏移:
- REG_BG0HOFS/VOFS (0x04000010/0x12): BG0滚动
- REG_BG1HOFS/VOFS (0x04000014/0x16): BG1滚动
- REG_BG2HOFS/VOFS (0x04000018/0x1A): BG2滚动(主地图)
- REG_BG3HOFS/VOFS (0x0400001C/0x1E): BG3滚动

### 13.2 相机计算

```
camera_x = player_x - screen_width/2
camera_y = player_y - screen_height/2

// 限制在边界内
max_x = MapData.width * 8 - 240  // GBA屏幕宽240px
max_y = MapData.height * 8 - 160 // GBA屏幕高160px
camera_x = clamp(camera_x, 0, max_x)
camera_y = clamp(camera_y, 0, max_y)

// 写入硬件寄存器
REG_BG2HOFS = camera_x
REG_BG2VOFS = camera_y
```

### 13.3 多BG层同步

当地图有多个BG层时:
- BG1(上层细节)与BG2(主地图)同步滚动
- 某些特效层(BG3)可能以不同速度滚动(视差效果)
- 对话框(BG0)锁定在屏幕上(不滚动)

### 13.4 边界检查

滚动边界存储在MapData的width/height字段:
- 代码位于asm/code_0803EE94.s
- 比较: `cmp r1, #0x80` (0x80 << 1 = 256像素最小滚动阈值)
- 边界上限: `width*8 - 240` 和 `height*8 - 160`

## 十四、地图切换系统

### 14.1 地图切换流程

1. **边界检测**: 玩家走到地图边缘(或进入门/传送点)
2. **场景切换函数**: func_08050D0C / func_08050DC8 等
3. **旧地图清理**: 销毁当前地图的实体和VRAM数据
4. **新地图加载**: 调用GetMapData(new_map_id)
5. **重新初始化**: 
   - 解压新tileset→VRAM
   - 解压新调色板→Palette RAM
   - 解压新tilemap→BG screenblock
   - 设置新相机边界
   - 重新创建实体

### 14.2 切换触发方式

- **走路**: 玩家走到地图边缘,系统检测坐标变化
- **门交互**: Entity门触发器→调用脚本→Proc016(dest_map, x, y)
- **脚本**: Proc016直接切换地图

### 14.3 切换相关函数

| 函数 | 用途 |
|------|------|
| func_08050D0C | 通用场景切换 |
| func_08050D34 | 场景切换辅助 |
| func_08050DC8 | Entity交互处理 |
| func_08050E68 | NPC/实体更新 |
| func_08050E30 | 地图更新循环 |

## 十五、Tileset图形格式

### 15.1 压缩格式

tileset(packed_img)使用popuri压缩,格式"230":
- atom_fmt=2(Huff8): 8位Huffman编码
- lzss_fmt=3: LZSS3解压 
- diff_fmt=0: 无差值滤波

### 15.2 解压后数据

32KB = 1024个tile,每个tile 32字节

### 15.3 GBA 4bpp tile格式

每个tile 8×8像素,每像素4位(16色):
```
Row 0: byte[0-3]  = 4像素×2(高4位/低4位)
Row 1: byte[4-7]
...
Row 7: byte[28-31]
```

每个半字节(4bit)索引调色板中的颜色(0-15)。

### 15.4 Tilemap引用

tilemap中每格2字节指向tileset:
- bit[0-9]: tile index(0-1023)
- bit[10]:  水平翻转
- bit[11]:  垂直翻转
- bit[12-15]: 调色板号(0-15)

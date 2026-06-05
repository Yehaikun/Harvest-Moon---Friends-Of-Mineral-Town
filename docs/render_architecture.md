# FoMT 渲染架构

## 一、场景系统 (Scene System)

- **AScene**: 场景基类，纯虚类，通过 `Run()` 返回下一个场景
- **SceneMain**: 主循环，不断执行 `Run() → 切换 → Run()` 
- **GameScene**: 实际游戏场景，处理地图渲染、NPC、交互等
- 文件: `src/scene.cc`, `include/scene.hh`, `asm/scene.s`

## 二、图形系统 (Graphics System)

### VRAM 管理 (TileVramManager)
- 管理 GBA VRAM 中 tile 空间的分配/释放
- 基于二叉树(5层)的分配器
- 每个分配记录: 位置(10bit) + 大小(4bit) + 计数 + ID
- 文件: `include/decomp/graphics.hh` (TileVramManager 节)

### 数据传输 (TransferRequest)
- DMA/VRAM 传输请求 (16字节)
- 用于将 tile 数据从 ROM/RAM 传输到 VRAM
- 挂载到 VBlankNode 链表，在 VBlank 期间执行

### 调色板管理 (PaletteSlotHolder)
- 8字节的调色板插槽持有者
- 管理 GBA 调色板内存 (0x05000000)

## 三、地图渲染

### MapData 结构
```
struct MapData {
    u32 packed_img;       // +0x00: 压缩的 tileset (32KB 解压 = 1024 tiles)
    u32 packed_pal1;      // +0x04: 压缩的调色板1 (480B)
    u32 packed_pal2;      // +0x08: 压缩的调色板2 (480B)
    u32 packed_tiles1;    // +0x0C: 压缩的 tilemap 层1 (60x56x2B)
    u32 packed_tiles2;    // +0x10: 压缩的 tilemap 层2
    u32 packed_tiles3;    // +0x14: 压缩的 tilemap 层3
    u32 terrain_info;     // +0x18: terrain 属性数组
    u32 terrain_map;      // +0x1C: 每格 terrain 索引
    u16 width;            // +0x20: 地图宽度(tiles)
    u16 height;           // +0x22: 地图高度(tiles)
    u8  is_interior;      // +0x24: 室内标志
};
```

### 渲染流程
1. 进入地图 → `GetMapData(map_id)` 读取 MapData
2. 解压 `packed_img` (tileset) → 上传到 VRAM tile 区
3. 解压 `packed_pal1/2` → 上传到调色板 RAM
4. 解压 `packed_tiles1/2/3` → 设置 BG tilemap (GBA 硬件渲染)
5. GBA 的 PPU 自动将 tile 数据 + tilemap + palette 合成画面

### Popuri 压缩格式
- 魔数 0x70 + 解压后大小 (4字节头)
- 格式字节: bits[2:0]=lzss_fmt, bits[4:3]=atom_fmt, bits[7:5]=diff_fmt
- 三层: atom(Huff4/raw) → LZSS(0-4) → diff(0-4)
- 工具: `tools/scripts/decompress.py`

## 四、GBA 硬件背景层

GBA 有 4 个背景层 (BG0-BG3):
- **BG0/BG1**: 通常用于文本/UI (text mode)
- **BG2**: 通常用于主地图 (affine/rotation mode 或 text mode)
- **BG3**: 通常用于副地图或特效

每个 BG 可以配置:
- 显示区域 (REG_BGxHOFS, REG_BGxVOFS)
- Tilemap 在 VRAM 中的位置 (BGxCNT)
- 调色板选择

Tilemap 格式 (GBA 硬件):
- 每格 2 字节: tile_index(10bit) + hflip(1) + vflip(1) + palette(4bit)
- 地图大小: 32x32 / 64x32 / 32x64 / 64x64 tiles

## 五、房屋/建筑数据

建筑数据不在 MapData 中，而是通过以下方式实现:
1. **Tilemap 直接绘制**: 建筑是 tilemap 中的一组 tile，没有独立的结构体
2. **Entity 系统**: 门/交互点通过 Entity 系统添加脚本触发器
3. **Terrain 系统**: 建筑的碰撞通过 terrain_map + terrain_info 控制

建筑 = tilemap 图形 + terrain 碰撞 + entity 触发器

## 六、Entity 系统

- 函数表: 0x080E602C (66 entries, 每个地图一个)
- 每个 entry 是 entity 初始化函数指针
- map 2(农场)和 map 5(北镇)有实际的 entity 初始化
- 其他地图使用空 handler (0x08000639)

## 七、NPC 系统

- 35 个 NPC entity 创建函数
- 每个 NPC 有自己的日程表 (ScheduleInfo)
- 日程决定 NPC 在特定时间出现在特定地图位置
- NPC 通过 ANpcEntity 类实现

## 关键文件

| 文件 | 内容 |
|------|------|
| `include/decomp/graphics.hh` | 图形系统结构体 (TextBox, VRAM, Tile) |
| `include/decomp/script_scene.hh` | GameScene 结构体布局 |
| `include/scene.hh` | 场景基类 |
| `src/scene.cc` | 场景系统实现 |
| `asm/game_scene.s` | GameScene 汇编代码 |
| `asm/game_state.s` | 游戏状态管理 |
| `src/data_schedules.cc` | NPC 日程数据 |
| `include/schedule_info.hh` | 日程结构体 |
| `asm/data/data_080F9EB8.s` | MapData 表 |
| `tools/scripts/decompress.py` | Popuri 解压 |

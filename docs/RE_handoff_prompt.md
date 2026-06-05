# FoMT MapData 缓存机制 - 分析接力提示词

## 项目概述

这是《牧场物语-矿石镇的伙伴们》(GBA) 的 modding 框架项目。核心问题：**修改 ROM 中 MapData 结构的 tilemap 相关字段（packed_tiles1、packed_tiles2、packed_tiles3、width、height）后，游戏中不生效**。而 terrain_map/terrain_info 的修改是生效的。

项目路径：`/home/lyjew/Documents/github/fomt/`
ROM文件：`fomt.gba`（请先 cd 到该目录）
分析工具已安装：Capstone、Keystone、Unicorn、radare2、Ghidra 12.1（含 GBA Loader）、gdb-multiarch
符号文件：`fomt.map` 包含大部分函数符号

## 关键数据结构和地址

### MapData 结构（每项 0x28=40 字节，66 张地图）

```
MapData 表基址: 0x08105EDC
GetMapData(map_id): 0x080A4698 — 返回 0x08105EDC + map_id * 0x28

结构体偏移:
+0x00 packed_img     - 压缩的 tileset 指针(32KB=1024tiles)
+0x04 packed_pal1    - 压缩的调色板1指针(480B)
+0x08 packed_pal2    - 压缩的调色板2指针(480B)
+0x0C packed_tiles1  - 压缩的 tilemap 层1指针
+0x10 packed_tiles2  - 压缩的 tilemap 层2指针
+0x14 packed_tiles3  - 压缩的 tilemap 层3指针
+0x18 terrain_info   - terrain 属性数组指针(每项4字节,bit0=碰撞)
+0x1C terrain_map    - 每格 terrain 索引(w*h字节)
+0x20 width          - 地图宽度(格数)
+0x22 height         - 地图高度(格数)
+0x24 is_interior    - 室内标志
```

### 地图数据示例（农场 map_id=2）

```
packed_tiles1 = 0x086FD240 → Popuri 压缩格式 "730" (lzss3+huff8+diff0)
packed_tiles2 = 0x086FD7D0 → Popuri 压缩格式 "730"
packed_tiles3 = 0x086FD9F4 → 非 Popuri (0x0B 开头，LZ77格式)
width = 60, height = 56
```

Popuri 压缩格式头部：`0x70 + 3字节解压大小 + 1字节格式码 + 比特流`

### 已知可用的 Python 工具
```
tools/decode_map_data_table.py --rom baserom.gba  # 解码 MapData 表
tools/edit_terrain.py fomt.gba --map 2 --info     # 地形碰撞编辑器（已验证可用）
tools/patch_farm_expansion.py                     # 农场扩增脚本
tools/render_map.py                               # 文本 tilemap 预览
```

## 已完成分析——关键发现

### 1. 地形修改为何生效

函数 `0x08017214` 直接调用 `GetMapData(map_id)` 获取 MapData 指针，然后直接读取地形字段:
```
ldr r0, [r3, 0x1C]  ; terrain_map
ldrb r0, [r0]        ; 读取碰撞数据
ldr r1, [r3, 0x18]   ; terrain_info
```

每次踏入地图时，该函数会重新从 ROM 读取地形数据并重建碰撞系统。**这是地形修改能立即生效的原因。**

### 2. packed_tiles1 走的是完全不同路径

我搜索了 ROM 中 **所有调用 GetMapData 的函数**（约 20 个），追踪它们后续访问的 MapData 偏移。结果：

| 偏移 | 字段 | 被几个函数访问 |
|------|------|--------------|
| +0x00 | packed_img (tileset) | 13 个函数 |
| +0x18 | terrain_info | 仅 0x08017214 |
| +0x1C | terrain_map | 仅 0x08017214 |
| +0x20 | width | 6 个函数 |
| +0x22 | height | 3 个函数 |
| **+0x0C** | **packed_tiles1** | **0 个函数！** |
| **+0x10** | **packed_tiles2** | **0 个函数！** |
| **+0x14** | **packed_tiles3** | **0 个函数！** |

**结论：packed_tiles1/2/3 的加载不经过 GetMapData 路径。** 瓦片地图一定是通过其他方式加载的——可能是某个函数接收 MapData 指针作为参数（而非自己调用 GetMapData）。

### 3. handler 表系统

发现了疑似构造函数的函数 `0x0804EA58`，它接收 packed_tiles1/tiles3/terrain_info/terrain_map 等参数并存储到类实例中：

```
0x0804EA58: push {r4-r7, lr}
    加载栈上参数 r5/r6/r7
    清空 [this+0] 和 [this+4]（链表指针？）
    ldr r4, =0x080E7868  ← 临时 handler 表
    str r4, [this+8]     ← 存储 handler 表地址
    str r1, [this+0x0C]  ← packed_tiles1
    strh r2, [this+0x12] ← field_12
    str r3, [this+0x14]  ← packed_tiles3
    str r5, [this+0x18]  ← terrain_info
    strh r6, [this+0x10] ← field_10
    str r7, [this+0x1C]  ← terrain_map
    bx lr
```

**但是** 紧接着调用的通用初始化函数 `0x080098AC` **立即覆盖了 handler 表地址**：
```
0x080098AC: ldr r0, =0x080E5BE8   ← 真正的 handler 表
            str r0, [r3, 8]        ← 覆盖临时 handler 表地址！
            初始化链表（双向链表插入）
            可选调用 func_08000608
```

所以临时 handler 表 `0x080E7868`（含瓦片加载函数 `0x0804EEFC`）**在初始化完成后就不再使用**。真正的 handler 表 `0x080E5BE8` 被安装。

### 4. 瓦片加载函数 0x0804EEFC 从未被调用

函数 `0x0804EEFC` 的功能：从类实例中读取缓存的 packed_tiles1 等字段，调用子函数 `0x0804E9F4` 生成顺序递增的 tile 索引。

但是用 Capstone 扫描全 ROM 后确认：**没有任何 BL 指令指向 `0x0804EEFC`**。它没有被任何代码调用。

### 5. handler 表格式

handler 表的格式是**16 字节一个条目**：
```
entry[N]:
  +0x00: 8 字节填充（全零）
  +0x08: 函数指针 0（或 NULL）
  +0x0C: 函数指针 1（或 NULL）
```

临时 handler `0x080E7868` 只有 entry[0]：
  - [0x0804EEFD, 0x0804EA81]（瓦片加载器, init包装器）

真正 handler `0x080E5BE8` 有多个条目：
  - entry[0]: [0x08000639（空函数）, 0x080098AD（init）]
  - entry[1]: [0x08010159, 0x0801004D]  ← 可能是渲染函数
  - 更多条目...

**但 0x080E5BE8 只在初始化时被存储，从未作为分发表使用过**——全 ROM 搜索 0x080E5BE8 的引用，4 处出现都是 literal pool（LDR 加载出来存到对象里用的），没有一处是用它来做函数分发。

## 待解决的问题

### 核心问题
瓦片地图到底是通过哪条代码路径加载的？已知：
1. ❌ 不走 GetMapData
2. ❌ 不走 0x0804EEFC（从未被调用）
3. ❌ 不走 handler 表 0x080E5BE8（只存不用）
4. ✅ 地形走 GetMapData 直读，所以修改生效

### 需要你做的

#### 第一步：追踪 packed_tiles1 的数据流

用以下方式定位实际加载 packed_tiles1 的函数：

**方法 A：Ghidra 反编译**
```bash
cd /home/lyjew/Documents/github/fomt
ghidra &
```
在 Ghidra 中：
1. File → New Project → 拖入 fomt.gba → GBA Loader
2. 自动分析完成后，搜索 packed_tiles1 在 MapData 结构中的偏移 0x0C
3. 查找所有引用 MapData+0x0C 的代码
4. 反编译包含这些引用的函数

**方法 B：radare2 快速查找**
```bash
# 搜索所有解压函数的调用者
r2 -q -c 'e asm.bits=16; aaa' fomt.gba
# 然后使用 axt 找引用
```

**方法 C：写 Python 脚本用 Capstone 扫描**
全 ROM 扫描 LDR Rx, [Ry, #0x0C] (即 imm5=3) 指令，对有该模式的函数提取前 20 条指令的上下文，定位哪些函数是在加载 MapData 字段（应该同时有对 +0x00、+0x04、+0x0C 等多个偏移的访问）。

#### 第二步：定位地图切换函数

已知场景切换函数在 `0x08050D0C` 附近。进入新地图时会触发的关键步骤：
1. 调用 GetMapData 读取地图配置 ✅（已确认有多个调用点）
2. 解压 tileset (packed_img) 到 VRAM ✅（通过多个 GetMapData 调用者）
3. **解压 tilemap (packed_tiles1) 到 VRAM screenblock** ❓（未知路径）
4. 解压调色板 (packed_pal) 到调色板 RAM ❓
5. 设置 BGxCNT 寄存器配置 BG 大小和位置

需要定位**第 3 步**的函数。

#### 第三步：设计补丁方案

找到瓦片地图加载路径后，最简单的修复方案有：

**方案 A：强制重读**
在解压 packed_tiles1 的前一刻，插入代码重新从 MapData 读取 packed_tiles1 指针，确保使用的是修改后的值。

**方案 B：NOP 缓存**
如果能找到缓存机制的写入点，直接 NOP 掉缓存写入，让系统每次都走直读路径。

**方案 C：运行时修补**
如果瓦片地图确实缓存在 VRAM，可以在 GBA 的 VBlank 中断中插入 DMA，将修改后的 tilemap 数据写入 VRAM screenblock。

## 可参考的 ROM 布局

```
0x08000000-0x0800FFFF: 启动代码/中断向量/BIOS
0x08010000-0x0803FFFF: 引擎代码（场景管理、实体系统）
0x08040000-0x0805FFFF: 游戏逻辑（地图、NPC、物品）
0x08060000-0x080CFFFF: 更多游戏代码
0x080D0000-0x080EFFFF: 数据表
0x080F0000-0x08100000: 更多数据表
0x08100000-0x08106xxx: MapData 表
0x08105EDC: MapData 表基址
0x08106xxx+: 脚本表、文本数据
0x086xxxxx-0x08xxxxxx: 压缩资源（tileset、palette、tilemap）
```

## 关键函数/地址速查

| 地址 | 说明 |
|------|------|
| 0x080A4698 | GetMapData(map_id) → MapData 指针 |
| 0x0804EA58 | "构造函数"——缓存 MapData 字段到类实例 |
| 0x0804EA80 | init 包装器——存储临时 handler 0x080E7868 |
| 0x080098AC | 通用 init——覆盖 handler 为 0x080E5BE8，链表初始化 |
| 0x0804EEFC | 临时 handler 中的瓦片加载函数（从未被调用） |
| 0x0804E9F4 | 瓦片加载子函数——生成顺序 tile 索引（从未被调用） |
| 0x080E7868 | 临时 handler 表（含 [0x0804EEFC, 0x0804EA80]） |
| 0x080E5BE8 | 真正 handler 表（初始化后被安装） |
| 0x08017180 | 地形处理函数——调用 GetMapData 直读地形 |
| 0x08017214 | → 其中的 GetMapData 调用点 |
| 0x08050D0C | 场景切换函数（附近） |
| 0x080CA6F4 | BG2CNT 设置函数（固定值 0x3E43） |
| 0x080E5BBC | 解压函数表（7 个函数指针） |
| 0x08009984 | 解压函数链中的一个（有被调用） |

## 已排除的假设

- ❌ 不是标准 C++ vtable（handler 表格式不同，且只存不用）
- ❌ 不是通过 BL 直接调用 0x0804EEFC（全 ROM 无 BL 指向它）
- ❌ 不是通过 handler 表分发（0x080E5BE8 只存不用）
- ❌ packed_tiles1/2/3 不是通过 GetMapData 访问的
- ✅ 地形数据是通过 GetMapData 直读 ROM 的
- ✅ Popuri LZSS3 "030" 格式是游戏兼容的

## 参考文档

项目中有详细文档：
```bash
cat /home/lyjew/Documents/github/fomt/docs/render_architecture.md
```
如果你需要看更多代码上下文，该目录下所有 Python 工具也在 `tools/` 下。

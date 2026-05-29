// ═══════════════════════════════════════════════════════════════════════════════
// 反编译笔记：图形系统相关结构体定义
// 来源: FOMT-DOC (StanHash)
// 涵盖: TextBox 文本框系统 / TextDrawing 文本绘制 / MapData 地图数据 /
//        TileVramManager Tile/VRAM 管理 / ScreenTransitionVNode 场景过渡
// ═══════════════════════════════════════════════════════════════════════════════
// 注意：这些只是反编译笔记，不是编译所需的正式头文件。
// ═══════════════════════════════════════════════════════════════════════════════

#ifndef DECOMP_GRAPHICS_HH
#define DECOMP_GRAPHICS_HH

#include "types.hh"

// =============================================================================
// 占位结构体（用于本文件中未详细展开、但在其他反编译笔记中定义的子系统）
// =============================================================================

// VBlankNode      — VBlank 回调链节点基类（vtable + 内部数据，共 0x0C 字节）
struct VBlankNode {
    u32 vtable;         // +00: vtable 指针
    u8 data[8];         // +04: 内部数据
};

// VBlankNodeList  — VBlank 回调链表节点（0x1C 字节）
struct VBlankNodeList {
    u8 data[0x1C];
};

// PaletteSlotHolder   — 调色板插槽持有者（8 字节）
struct PaletteSlotHolder {
    u8 data[8];
};

// TileVramSlotHodler  — Tile VRAM 插槽持有者（8 字节；保留原始拼写 "Hodler"）
struct TileVramSlotHodler {
    u8 data[8];
};

// DefinedSprite   — 已定义的精灵对象（0x30 = 48 字节）
struct DefinedSprite {
    u8 data[0x30];
};

// SpriteAnimator  — 精灵动画控制器（0x14 = 20 字节）
struct SpriteAnimator {
    u8 data[0x14];
};

// TransferRequest — DMA / VRAM 传输请求（0x10 = 16 字节）
struct TransferRequest {
    u8 data[0x10];
};

// CheckerboardFakeTransparencyVNode — 棋盘格伪透明效果 VNode（0x18 字节）
struct CheckerboardFakeTransparencyVNode {
    u8 data[0x18];
};

// =============================================================================
// 一、TextBox 文本框系统（来源: TextBoxes.txt）
// =============================================================================

// TextBoxHandle — 文本框句柄（仅含一个指向 TextBox 的 auto_ptr）
struct TextBoxHandle {
    u32 auto_ptr_to_textbox; // +00: auto_ptr 指向 TextBox
};

// TextBoxLineGfx — 文本框单行图形数据（用于在 VRAM 中管理一行文本的 tile）
struct TextBoxLineGfx {
    struct Entry {
        u32 ptr_gfx_buffer;         // +00: 指针，指向动态分配的图形缓冲（大小 $104）
        TileVramManagerHandle handle; // +04: TileVramManagerHandle
        u32 tile_identifier;        // +08: tile 标识符
        u8 needs_sync;              // +0C: 需要同步标志（图形已更新）
    } entries[7];                   // 每行 7 个精灵（sprite），每个 $10 字节
};                                  // 合计 7 * 0x10 = 0x70 字节
// 注：动态分配的图形缓冲（$104 字节）布局：
//   +00: word       — ??
//   +04: u8[0x100]  — tile 图形数据（8 个 tile）

// TextBoxDisplayManager — 文本框显示管理器基类（虚函数表）
struct TextBoxDisplayManager {
    u32 vtable;                     // +00: vtable（080EFE48）
};
// vtable 布局:
//   +08: (析构函数)
//   +0C: int  textDrawCharacter(int character);           // 绘制单个字符（返回 0 表示失败）
//   +10: void textDoCarriageReturn(void);                  // 回车（复位 X 光标）
//   +14: void textDoLineFeed(void);                        // 换行
//   +18: void textDoFormFeed(void);                        // 换页（清空文本框重新开始）

// TextBoxDisplayManagerImpl — 文本框显示管理器实现
struct TextBoxDisplayManagerImpl {
    TextBoxDisplayManager base;     // +00: 基类（vtable 080EFE00）
    u32 ptr_palette_holder;         // +04: 指针，指向 TextBox+10（PaletteSlotHolder）
    u32 ptr_line_gfx[3];           // +08: 指针数组，指向动态分配的 TextBoxLineGfx（每行一个）
    s16 current_x_tile;            // +14: 当前 X tile
    s16 current_display_line;      // +16: 当前显示行（0-3）
    u8 current_top_gfx_line;       // +18: 当前顶部图形行（滚动时顶部行会被复用到底部）
    u8 oam_needs_update;           // +19: OAM 需要更新标志（滚动时置位）
    u8 character_added;            // +1A: 有字符添加标志
    u8 non_blank_char_added;       // +1B: 有非空白字符添加标志（用于播放音效）
};                                  // 合计 0x1C 字节

// TextBoxCharExpander — 文本字符扩展器（用于展开特殊标记如玩家名等）
struct TextBoxCharExpander {
    u32 vtable;                     // +00: vtable
};
// vtable 布局:
//   +08: (析构函数)
//   +0C: <something> textTryExpandCharacter(int character);  // 尝试扩展字符

// TextBoxInterpreter — 文本框文本解释器
struct TextBoxInterpreter {
    u32 state;                      // +00: 状态标识符
    //  0 = 结束（end）
    //  1 = 正常推进（advance normally）
    //  2 = 等待输入（waiting for input）
    u16 text_speed;                 // +04: 文本速度（$100 = 每 tick/帧 1 个字符）
    u16 text_cursor;                // +06: 文本光标（每 tick/帧 按 text_speed 递增）
    u32 ptr_string;                 // +08: 指针，指向以 null 结尾的字符串
    u32 ptr_char_expander;          // +0C: 指针，指向 TextBoxCharExpander 实例
    u32 ptr_secondary_string;       // +10: 指针，指向另一以 null 结尾的字符串（优先级高于 +08）
    u8 string_buffer[0x20];         // +14: 字符串缓冲（用于存放展开后的文本片段）
};                                  // 合计 0x34 字节

// TextBoxTextTileSyncVNode — 文本框文本 Tile 同步 VNode（VBlank 时同步文本图形）
struct TextBoxTextTileSyncVNode {
    VBlankNode base;                // +00: VBlankNode 基类（vtable 080EFDC8）
    u32 ptr_display_mgr_impl;      // +0C: 指针，指向 TextBoxDisplayManagerImpl
};

// TextBoxBoxSyncVNode — 文本框背景框同步 VNode（VBlank 时同步背景框图形）
struct TextBoxBoxSyncVNode {
    VBlankNode base;                // +00: VBlankNode 基类（vtable 080EFDB8）
    // +0C: 位域（从 TextBox 各字段组装而来）
    u32 bg_map_block        : 5;   // bit[00-04]：来自 [TextBox bit[02-06]]（bg map block，$800 递增）
    u32 bg_base_tile_index  : 10;  // bit[05-14]：来自 [TextBox bit[09-18]]（bg 基础 tile 索引）
    u32 bg_pal_id           : 4;   // bit[15-18]：来自 [TextBox bit[19-22]]（bg 调色板 ID）
    u32 pal_idx_from_tx     : 4;   // bit[19-22]：来自 TextBox+10 的调色板索引（某种 obj tile ID）
    u32 : 9;                       // bit[23-31]：未使用
};

// TextBoxInputManager — 文本框输入管理器基类
struct TextBoxInputManager {
    u32 vtable;                     // +00: vtable（080EFE30）
};
// vtable 布局:
//   +08: (析构函数)
//   +0C: int textIsInstant(void);          // 文本是否为即时显示
//   +10: int textShouldWaitForInput(void); // 文本是否等待输入
//   +1C: int textCheckInput(void);         // 检查输入

// StaticTextBoxInputManager — 静态文本框输入管理器（按下按键即推进）
struct StaticTextBoxInputManager {
    TextBoxInputManager base;       // +00: 基类（vtable 080EFDE8）
    u32 pressed_keys;               // +04: 已按下的按键
    u8 allow_advance;               // +08: 允许推进到下一文本框
};

// Some sub-object referenced by TextBox+1E4（动态分配，大小 $20 = 32 字节）
struct TextBoxDynSubObject {
    struct Entry {
        u32 field_00;   // +00: word ?
        s16 field_04;   // +04: short ?
    } entries[4];       // 4 个条目，共 24 字节
    u8 unknown[8];      // 填充至 0x20 字节
};

// TextBox — 文本框主结构体
struct TextBox {
    // ---- 字段 0x000-0x00C ----
    // +000: 位域（背景框图形参数）
    u32 unk_000              : 2;  // bit[00-01]：未知
    u32 bg_map_block         : 5;  // bit[02-06]：用于背景框图形的 bg map block（$800 递增）
    u32 bg_tile_block        : 2;  // bit[07-08]：用于背景框图形的 bg tile block（$4000 递增）
    u32 bg_base_tile_index   : 10; // bit[09-18]：用于背景框图形的 bg 基础 tile 索引
    u32 bg_pal_id            : 4;  // bit[19-22]：用于背景框图形的 bg 调色板 ID
    u32 : 9;                       // bit[23-31]：未使用

    u32 field_004;                  // +004: word
    u32 state;                      // +008: 状态标识符
    //  0 = 无文本框（no box）
    //  1 = 文本框打开中（box opening）
    //  2 = 文本框关闭中（box closing）
    //  3 = 文本已结束（text is finished）
    //  4 = 文本推进中（text is advancing）
    //  5 = 文本等待输入（text is waiting for input）
    //  6 = 等待用户选择（waiting for user choice）

    u8 display_level;               // +00C: 文本框"显示程度"（开/关动画用），范围 0（关闭）~ 8（完全打开）
    u8 field_00D;                   // +00D: 字节

    u8 pad_00E[2];                  // 对齐填充至 0x10

    // ---- 字段 0x010-0x1DC ----
    PaletteSlotHolder pal_holder;           // +010: 调色板插槽持有者
    TileVramSlotHodler tile_slot_holder;    // +018: Tile VRAM 插槽持有者
    VBlankNodeList vblank_node_list;        // +020: VBlankNode 链表

    // +03C: TransferRequest 列表（最多 8 个）
    u32 transfer_req_count;                 // +03C: 当前已使用数量（最大 8）
    TransferRequest transfer_reqs[8];       // +040: TransferRequest 数组，每个 $10 字节
    // （+03C + 0x84 = +0C0）

    // +0C0: VBlankNode 子类对象（vtable 080EFDD8，大小 $10，[+0C] 指向 TextBox+3C）
    u32 vnode_child_vtable;                 // +0C0: vtable（080EFDD8）
    u8 vnode_child_data[8];                 // +0C4: VBlankNode 内部数据
    u32 vnode_child_ptr_transfer_list;      // +0CC: 指针，指向 TextBox+3C 的 TransferRequest 列表

    TextBoxDisplayManagerImpl display_mgr;  // +0D0: 文本框显示管理器实现（大小 0x1C）
    TextBoxInterpreter interpreter;         // +0EC: 文本解释器（大小 0x34）
    TextBoxTextTileSyncVNode tile_sync_vnode; // +120: 文本 Tile 同步 VNode（大小 0x10）

    CheckerboardFakeTransparencyVNode checkerboard_vnode; // +130: 棋盘格伪透明效果 VNode（大小 0x18）

    TextBoxBoxSyncVNode box_sync_vnode;     // +148: 背景框同步 VNode（大小 0x10）

    u32 choice_id;                          // +158: 当前选择框的选中项 ID
    u32 choice_related;                     // +15C: 与选择框相关的某个值

    DefinedSprite hand_cursor_sprite;       // +160: 手形光标精灵
    DefinedSprite text_arrow_sprite;        // +190: "文本框箭头" 精灵
    SpriteAnimator sprite_animator;         // +1C0: 精灵动画控制器（用于手形光标或文本框箭头）

    TileVramSlotHodler tile_slot_holder_2;  // +1D4: Tile VRAM 插槽持有者

    // +1DC: 位标志
    u8 unk_1DC_0 : 1;   // bit[00]：?
    u8 unk_1DC_1 : 1;   // bit[01]：?
    u8 : 6;              // bit[02-07]：未使用

    u8 pad_1DD[7];                          // 填充至 0x1E4

    u32 ptr_dyn_sub_object;                 // +1E4: 指针，指向动态分配的 TextBoxDynSubObject 对象（大小 $20）

    PaletteSlotHolder pal_holder_2;         // +1E8: 调色板插槽持有者

    // +1F0: 位标志
    u8 unk_1F0_0 : 1;   // bit[00]：??
    u8 unk_1F0_1 : 1;   // bit[01]：??
    u8 : 6;              // bit[02-07]：未使用

    u8 unknown_big_gap[0x30E];              // +1F1 ~ +4FF：大面积未记录字段（0x30E 字节）

    // ---- 字段 0x500-0x554 ----
    u8 field_500;                           // +500: 字节，通常为 0
    u8 pad_501[3];                          // 填充至 0x504

    DefinedSprite heart_sprite;             // +504: 心形精灵
    SpriteAnimator heart_animator;          // +534: 心形精灵动画控制器
    PaletteSlotHolder pal_holder_3;         // +548: 调色板插槽持有者

    // +550: 配置位
    u32 cfg_play_some_sound   : 1;  // bit[00]：&01 = 播放某种声音
    u32 cfg_unk_1             : 1;  // bit[01]：未知配置位
    u32 cfg_play_text_beep    : 1;  // bit[02]：&04 = 播放文本推进提示音
    u32 cfg_unk_3             : 1;  // bit[03]：未知配置位
    u32 cfg_play_choice_sound : 1;  // bit[04]：&10 = 切换文本选项时播放音效
    u32 cfg_unk_5             : 1;  // bit[05]：未知配置位
    u32 : 26;                        // bit[06-31]：未使用
};                                  // 总大小约 0x554 字节

// 文本控制码（遵循 ASCII，附加特殊功能码）:
//   $05 = 询问（等待 A 键按下）
//   $0A = 换行（LF；移动到新行，不重置 X 光标）
//   $0C = 换页（FF；清空文本框重新开始）
//   $0D = 回车（CR；重置 X 光标）

// =============================================================================
// 二、文本绘制（来源: TextDrawing.txt）
// =============================================================================

// 字形数据格式：
//   每个字节表示 8 像素行；*最高*位是最左侧像素
//   （与 VRAM tile 相反：VRAM 中 *最低* 半字节表示最左侧像素）
//   2 tile 宽的字形：一行占 2 字节
//   共 12 行（非 16！顶部 2 行和底部 2 行总是假定为已清除）
//   1 tile 宽字形 = 12 字节数据；2 tile 宽字形 = 24 字节数据

// RAM 功能函数（用于将 1bpp 字符字形解包为 4bpp tile）：
//   RAMFunc 2 (DrawGlyph2Tile) — 用于 2 tile 宽的字形
//   RAMFunc 3 (DrawGlyph1Tile) — 用于 1 tile 宽的字形
//   参数:
//     arg1 (r0) = 指向字形图形数据的指针
//     arg2 (r1) = 指向输出缓冲的指针（未针对直接写入 VRAM 优化）

// 主字形绘制函数
// 返回字符字形所占 tile 宽度；若无法显示（如双字节字符的首字节）则返回 0
// 字符编码：Shift-JIS（双字节字符时首字节 << 8 | 次字节）
// 该函数仅在两处被调用。
int drawCharacterGlyph(void* buffer, int character); // 080D8950

// 将字符字形绘制到 2D 图形缓冲中
// vec2 size = 缓冲大小（以 tile 为单位），打包为 (高 << 16 | 宽)
// x, y 以像素为单位（非对齐位置有处理代码但实际为空操作）
// 返回字形 tile 宽度
int drawCharGlyphTo2DGfxBuffer(u32 packed_size, void* buf, int x, int y, int character); // 08050A64

// 同上，扩展版本（带两个额外参数，功能待分析）
int drawCharGlyphTo2DGfxBufferExt(u32 packed_size, void* buf, int x, int y,
                                   int character, int idk, int man); // 08050B64

// 在 2D 图形缓冲中绘制完整字符串
void drawStringTo2DGfxBuffer(u32 packed_size, void* buf, int x, int y,
                              const char* cstr); // 08050EA8

// =============================================================================
// 三、地图数据（来源: MapData.txt）
// =============================================================================

// 疑似地图数据表入口（表地址 0810EBB8）
// 地形数据: 4 字节条目数组，描述地形属性
// 地形地图: 字节数组，索引到地形数据数组（索引 = y * width + x）
//   若地形地图指针为 0，则直接用位置索引地形数据
struct MapTableEntry {
    u32 ptr_compressed_0;   // +00: 指针，指向压缩数据 ?
    u32 ptr_compressed_1;   // +04: 指针，指向压缩数据 ?
    u32 ptr_compressed_2;   // +08: 指针，指向压缩数据 ?
    u32 ptr_compressed_3;   // +0C: 指针，指向压缩数据 ?
    u32 ptr_compressed_4;   // +10: 指针，指向压缩数据 ?
    u32 ptr_compressed_5;   // +14: 指针，指向压缩数据 ?
    u32 ptr_terrain_data;   // +18: 指针，指向地形数据 ?
    u32 ptr_terrain_map;    // +1C: 指针，指向地形地图 ?
    s16 map_width;          // +20: 地图宽度 ?
    s16 map_height;         // +22: 地图高度 ?
    u8 field_24;            // +24: bool ?
};                          // 至少 0x25 字节

// 未知结构体（可能与农场布局相关，由 080A9CC8 构造，大小 $94 = 148 字节）
struct UnkFarmStruct {
    u32 field_00;               // +00: word ?（默认值: $23A）
    u32 field_04;               // +04: word ?（默认值: $48）
    u32 field_08;               // +08: word ?
    u32 field_0C;               // +0C: word ?
    u32 ptr_array_big[3];       // +10: 指针数组（指向大小 $7900 的未知对象）
    u32 ptr_array_small[3];     // +1C: 指针数组（指向大小 $1E0 的未知对象）

    u8 field_28;                // +28: byte ?
    u8 field_29;                // +29: byte ?
    u8 field_2A;                // +2A: byte ?

    u32 ptr_huge_object;        // +2C: 指针，指向大小 $F200 的未知对象

    // 以下三字节一组（共 10 组），疑似某种子结构
    u8 f30, f31, f32;          // +30: 3 字节 ?
    u8 f34, f35, f36;          // +34: 3 字节 ?
    u8 f38, f39, f3A;          // +38: 3 字节 ?
    u8 f3C, f3D, f3E;          // +3C: 3 字节 ?
    u8 f40, f41, f42;          // +40: 3 字节 ?
    u8 f44, f45, f46;          // +44: 3 字节 ?
    u8 f48, f49, f4A;          // +48: 3 字节 ?
    u8 f4C, f4D, f4E;          // +4C: 3 字节 ?
    u8 f50, f51, f52;          // +50: 3 字节 ?
    u8 f54, f55, f56;          // +54: 3 字节 ?

    u8 field_58;                // +58: byte ?

    u8 pad_59[3];               // 填充至 0x5C

    // +5C: 继承自 VBlankNode 的对象（大小 0x30 = 48 字节）
    u32 vnode_vtable;           // +5C: vtable ?
    u8 vnode_internal[0x0C];    // +60: VBlankNode 内部数据（0x0C 字节）
    u8 vnode_child_data[0x20];  // +6C: 子类额外数据（0x20 字节）
    // （+5C + 0x30 = +8C）

    u32 field_8C;               // +8C: word ?
    u32 vtable;                 // +90: vtable（080F0834）
};                              // 总大小 0x94

// 另一未知结构体（由 080AB6A8 构造，大小 $BC = 188 字节，继承 UnkFarmStruct）
// vtable 为 080F086C
struct UnkFarmStruct2 {
    UnkFarmStruct base;         // +00: 基类（大小 0x94，vtable 080F086C）

    u32 field_94;               // +94: word ?
    u8 field_98;                // +98: byte ?

    u8 pad_99[3];               // 填充至 0x9C

    // +9C: 某个未知对象（大小 $18 = 24 字节）
    u8 unk_obj_9C_data[0x0C];   // +9C: 前 0x0C 字节未知
    u32 unk_obj_9C_ptr;         // +AC: 指针，指向大小 $18 的未知对象（可能是自引用？）
    u32 unk_obj_9C_field_10;    // +B0: word ?
    u32 unk_obj_9C_field_14;    // +B4: word ?

    // 原笔记推测 +B4 等三字节对也是某种结构体
    u8 field_B4;                // +B4: byte ?
    u8 field_B5;                // +B5: byte ?
    u8 field_B6;                // +B6: byte ?
    u8 field_B8;                // +B8: byte ?
    u8 field_B9;                // +B9: byte ?
    u8 field_BA;                // +BA: byte ?
};                              // 总大小 0xBC

// =============================================================================
// 四、TileVramManager — Tile/VRAM 分配管理（来源: TileVramManager.txt）
// =============================================================================

// TileVramManagerHandle — 空对象，仅用于利用 C++ 构造/析构机制管理单例生命周期
struct TileVramManagerHandle {
};

// TileVramManagerEntry — VRAM 分配条目（数组中的一项，8 字节）
struct TileVramManagerEntry {
    union {
        u32 all_bits;                           // 整个 word
        u32 next_ptr;                           // （未使用时）指向下一空闲条目的指针（0 = 最后一项）
        struct {
            u32 alloc_position : 10;            // bit[00-09]：（已使用时）分配位置
            u32 alloc_size     : 4;             // bit[10-13]：（已使用时）分配大小（2 的幂，3 表示 8 个"槽位"）
            u32 : 18;                           // bit[14-31]：未使用
        };
    };
    u16 alloc_count;                            // +02: （已使用时）分配计数
    u16 unique_id;                              // +04: （已使用时）唯一标识符（从 [+922] 自增初始化）
};                                              // 共 8 字节

// ---- 分配树节点（5 层二叉树，叶节点存储分配位图） ----
// L5 节点（叶，$04 字节）
struct TileVramAllocL5 {
    u32 allocation_bits;                        // +00: 分配位图
};

// L4 节点（$0C 字节）
struct TileVramAllocL4 {
    u8 has_allocation;                          // +00: 1 = 此节点下有已分配项
    u8 is_saturated;                            // +01: 1 = 此节点已满（无剩余空间）
    u8 pad[2];
    TileVramAllocL5 children[2];                // +04: 两个子节点
};

// L3 节点（$1C 字节）
struct TileVramAllocL3 {
    u8 has_allocation;
    u8 is_saturated;
    u8 pad[2];
    TileVramAllocL4 children[2];
};

// L2 节点（$3C 字节）
struct TileVramAllocL2 {
    u8 has_allocation;
    u8 is_saturated;
    u8 pad[2];
    TileVramAllocL3 children[2];
};

// L1 节点（$7C 字节）
struct TileVramAllocL1 {
    u8 has_allocation;
    u8 is_saturated;
    u8 pad[2];
    TileVramAllocL2 children[2];
};

// L0 根节点（$FC 字节）
struct TileVramAllocRoot {
    u8 has_allocation;                          // +00: 1 = 此节点下有已分配项
    u8 is_saturated;                            // +01: 1 = 此节点已满
    u8 pad[2];                                  // +02-03: 填充
    TileVramAllocL1 children[2];                // +04: 两个 L1 子节点
};

// TileVramManager — VRAM Tile 分配管理器单例（实例指针位于 03000408）
struct TileVramManager {
    // ---- 使用状况位图 & 条目数组（0x000-0x824） ----
    u32 usage_bitmap[8];                        // +000: 使用状况位图（按 bits / 字节顺序指示 +24 数组使用情况；置位 = 已用）
    u32 ptr_next_free_entry;                    // +020: 指针，指向 +24 数组中下一个空闲条目

    TileVramManagerEntry entries[0x100];        // +024: 条目数组，0x100 个条目，每个 8 字节；总计 0x800 字节
    // （+024 + 0x800 = +824）

    // ---- 分配树（0x824-0x920） ----
    TileVramAllocRoot alloc_tree;               // +824: 分配树根节点（大小 0xFC）

    // ---- 管理字段（0x920-0x92C） ----
    s16 used_entry_count;                       // +920: 数组中已使用条目数 ?
    s16 id_counter;                             // +922: 标识符计数器（自增，用于生成 unique_id）
    u32 handle_refcount;                        // +924: 存活的 TileVramManagerHandle 数量（归零时释放此对象）
    s16 field_928;                              // +928: 0 ?
    s16 field_92A;                              // +92A: 0 ?
};                                              // 总大小 0x92C

// Tile 区域标识符格式：
//   bit[00-07] = 插槽索引
//   bit[08-23] = 唯一标识符（防止插槽被复用后旧标识符仍有效）
//
// TileVramManagerHandle 函数（地址 MFOMTU）:
//   080078DC | TileVramManagerHandle*  TileVramManagerHandle_construct(TileVramManagerHandle*);
//   08007A50 | void   TileVramManagerHandle_destruct(TileVramManagerHandle*, int);
//   08007A90 | void   TileVramManagerHandle_setAllocBounds(TileVramManagerHandle*, int start, int size);
//   08007BBC | int    TileVramManagerHandle_allocate(TileVramManagerHandle*, int size);
//   08007C90 | void   TileVramManagerHandle_free(TileVramManagerHandle*, int id);
//   08007DB4 | int    TileVramManagerHandle_getTileIndex(TileVramManagerHandle*, int id);
//   08007E20 | int    TileVramManagerHandle_getSizeIdentifier(TileVramManagerHandle*, int id);
// 注：size 参数以 2 的幂形式表示。

// =============================================================================
// 五、ScreenTransitionVNode — 场景过渡效果（来源: ScreenTransitionVNode.txt）
// =============================================================================

// ScreenTransitionHandlerInternal — 场景过渡处理器内部实现
struct ScreenTransitionHandlerInternal {
    u32 ptr_disp_io;            // +00: DispIoProxy 指针（若为 null，则直接写入 IO 寄存器）
    s16 transition_speed;       // +04: 过渡速度（负值 = 反向过渡）
    u32 brightness_effect;      // +08: 亮度变化效果（0 = 无, 1 = 亮度增加, 2 = 亮度降低）
    u8 enable_mosaic;           // +0C: 启用马赛克效果（bool）
    u8 pad_0D;                  // +0D: 填充
    s16 timer;                  // +0E: 计时器（每帧递增 [+04]）
};                              // 至少 0x10 字节

// ScreenTransitionHandler — 场景过渡处理器（持有内部对象的指针）
struct ScreenTransitionHandler {
    u32 ptr_internal;           // +00: 指针，指向拥有的 ScreenTransitionHandlerInternal
};

// ScreenTransitionVNode — 场景过渡 VBlank 节点
struct ScreenTransitionVNode {
    VBlankNode base;                            // +00: VBlankNode 基类
    ScreenTransitionHandler transition_handler; // +0C: 场景过渡处理器
};

// =============================================================================
// 六、Tile 区域标识符辅助类型
// =============================================================================

// TileAreaId — 将 tile 区域标识符分解为插槽索引和唯一 ID
struct TileAreaId {
    u32 slot_index  : 8;    // bit[00-07]：插槽索引
    u32 unique_id   : 16;   // bit[08-23]：唯一标识符
    u32 : 8;                // bit[24-31]：未使用
};

#endif // DECOMP_GRAPHICS_HH

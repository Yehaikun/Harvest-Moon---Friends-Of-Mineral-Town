// ═══════════════════════════════════════════════════════════════════════════════
// 反编译笔记：实体继承体系与结构体布局
// 来源: FOMT-DOC / Entities.txt (StanHash)
// ═══════════════════════════════════════════════════════════════════════════════
// 注意：这些只是反编译笔记，不是编译所需的正式头文件。
// 基地址为 MFOMTU (美版)
// ═══════════════════════════════════════════════════════════════════════════════

#ifndef DECOMP_ENTITIES_HH
#define DECOMP_ENTITIES_HH

#include "decomp/types.hh"

// ═══════════════════════════════════════════════════════════════════════════════
// 面向/方向常量
// ═══════════════════════════════════════════════════════════════════════════════
enum FacingDirection : u8 {
    FACING_DOWN  = 0,  // 朝下
    FACING_UP    = 1,  // 朝上
    FACING_LEFT  = 2,  // 朝左
    FACING_RIGHT = 3,  // 朝右
};

// ═══════════════════════════════════════════════════════════════════════════════
// 地图 ID 常量（场景/地点）
// ═══════════════════════════════════════════════════════════════════════════════
enum MapId : u16 {
    MAP_MOTHERS_HILL    = 0x000,  // 母亲之山
    MAP_BEACH           = 0x001,  // 海滩
    MAP_FARM            = 0x002,  // 农场
    MAP_FOREST          = 0x003,  // 森林
    MAP_CHURCH_REAR     = 0x004,  // 教堂后院
    MAP_NORTH_TOWN      = 0x005,  // 矿物镇北
    MAP_ROSE_SQUARE     = 0x006,  // 玫瑰广场
    MAP_SOUTH_TOWN      = 0x007,  // 矿物镇南
    MAP_MOTHERS_PEAK    = 0x008,  // 母亲之山顶
    MAP_SHOP_INTERIOR   = 0x00F,  // 商店室内
    MAP_PLAYER_HOUSE    = 0x01D,  // 玩家房屋
    MAP_SPRING_MINE     = 0x03A,  // 泉水矿洞
};

// ═══════════════════════════════════════════════════════════════════════════════
// 实体继承体系（基于 vtables 推断）
// ═══════════════════════════════════════════════════════════════════════════════
//
// AbstractEntity (080EE790)                    [纯虚]
//   +-- AbstractActor (080EEDB8)               [纯虚]
//       +-- vtable_80EEA94                     [纯虚]
//       |   +-- DogActor (080EEA08)
//       |   +-- HorseActor (080EE968)
//       |   +-- (多个 vtable 子节点)
//       +-- AbstractPlayerActor (080EECAC)     [纯虚]
//       |   +-- PlayerActor (080EEB98)
//       +-- ScheduledActor (080EF718)          [纯虚]
//       |   +-- LilliaActor (080EF6D8)
//       |   +-- RickActor (080EF698)
//       |   +-- ... (众多 NPC 角色)
//       |   +-- GoddessActor (080EEF18)
//       +-- HannahActor (080EF79C)
//       +-- (多个 vtable 子节点)
//   +-- (多个 vtable 子节点)

// ═══════════════════════════════════════════════════════════════════════════════
// AbstractEntity 结构体 (大小: 0x18)
// vtable: 080EE790 (纯虚)
// ═══════════════════════════════════════════════════════════════════════════════
struct AbstractEntity {
    /* +00 */ u32       game_object_ptr;    // 指向 Game 对象的指针
    /* +04 */ u16       map_id;             // 当前地图/地点 ID
    /* +06 */ u8        is_active;          // 是否正在执行特殊操作?
    /* +08 */ s32       x_pos_q16;          // X 坐标 (Q16 定点数)
    /* +0C */ s32       y_pos_q16;          // Y 坐标 (Q16 定点数)
    /* +10 */ u32       display_obj_ptr;    // 显示相关对象指针
                                            //   +04: vtable 指针
                                            //   +30: SpriteAnimator
                                            //   +70: SpriteAnimator
                                            //   +84: byte ?
                                            //   +86: byte ?
                                            //   +87: byte ?
                                            //   +88: byte ?
                                            //   +8A+00bit: 2bit ?
    /* +14 */ u32       vtable_ptr;         // vtable 指针 (080EE790)
};

// Assert: sizeof(AbstractEntity) == 0x18

// ═══════════════════════════════════════════════════════════════════════════════
// AbstractActor 结构体 (继承自 AbstractEntity)
// vtable: 080EEDB8 (纯虚)
// ═══════════════════════════════════════════════════════════════════════════════
struct AbstractActor {
    /* +00 */ AbstractEntity    base;           // 基类 (vtable: 080EEDB8)
    /* +18 */ s32              x_speed_q16;    // X 速度? (Q16)
    /* +1C */ s32              y_speed_q16;    // Y 速度? (Q16)
    /* +20 */ u8               facing;         // 朝向/动画标识偏移? (见 FacingDirection)
    /* +21 */ u8               unk_21;         // 构造函数参数 r3 传入 (PlayerActor 和 ScriptedActor 传 2)
    /* +22 */ u16              anim_base_id;   // 动画标识基准值?
    /* +24 */ u16              anim_duration_1;// 动画持续时间?
    /* +26 */ u16              anim_duration_2;// 动画持续时间?
    /* +28 */ u32              unk_28;         // 某种对象/字 (构造函数 080326BC; 脚本函数 0x009 和 0x00A 会操作此字段)
    /* +2C */ u16              unk_2C;         // ?
    /* +2E */ u8               unk_2E;         // ?
};

// Assert: sizeof(AbstractActor) == 0x30

// ═══════════════════════════════════════════════════════════════════════════════
// PlayerActor 结构体 (大小: 0xC8)
// vtable: 080EEB98
// 继承自 AbstractPlayerActor (080EECAC) [纯虚]
// ═══════════════════════════════════════════════════════════════════════════════
struct PlayerActor {
    /* +00 */ AbstractActor     base;               // 基类 AbstractActor (vtable: 080EEB98)
    // --- AbstractPlayerActor 扩展字段 ---
    /* +30 */ u32               unk_30;             // 某种对象指针，看起来很大很重要?
    /* +34 */ u32               gamedata_ptr;       // GameData 指针
    /* +38 */ u32               unk_38;             // 某种对象指针
    /* +3C */ u8                state;              // 状态标识符
                                                    //   0x00 = 正常移动 (包括手持物品)
                                                    //   0x01 = 按住 A 键
                                                    //   0x02 = 按住 B 键
                                                    //   0x06 = 空闲太久而睡着
                                                    //   0x09 = 使用工具动画中?
                                                    //   0x0D = 正在放下物品?
                                                    //   0x11 = 正在举起物品?
                                                    //   0x2C = 跳过地图上的某个东西
                                                    //   0x35 = 两天之间黑屏切换? 由状态0更新方法在检测到碰撞时进入
                                                    //   0x07/0x2D = 碰撞盒变大 ({x-7,y-9,x+7,y+5} 取代默认)
    /* +3D */ u8                unk_3D;             // ?
    /* +3E */ u8                unk_3E;             // ?
    /* +3F */ u8                unk_3F;             // ?
    /* +40 */ u8                unk_40;             // ?
    /* +41 */ u8                _pad_41[0x60-0x41]; // 填充至偏移 0x60
    /* +60 */ struct {                              // 某种内联对象
        /* +60+00 */ u32        cstr_ptr;           // C 字符串指针
        /* +60+04 */ u16        unk_60_04;          // ?
    } unk_60;
    /* +62 */ u8                _pad_62[0x7A-0x62]; // 填充至偏移 0x7A
    /* +7A */ u8                unk_7A;             // 状态0更新方法开始时被设为 0
    /* +7B */ u8                _pad_7B[0x7C-0x7B]; // 填充
    /* +7C */ u16               unk_7C;             // ?
    /* +7E */ u8                _pad_7E[0x88-0x7E]; // 填充至偏移 0x88
    /* +88 */ struct {                              // 某种内联对象
        /* +88+00 */ u8         has_item_in_hand;   // 非零表示手中有物品?
        /* +88+01 */ u8         unk_88_01;          //
        /* +88+02 */ u8         _pad_88_02[0x04-0x02];
        /* +88+04 */ u32        unk_88_04;          //
        /* +88+08 */ u32        unk_88_08;          //
        /* +88+0C */ u8         _pad_88_0C[0x14-0x0C];
        /* +88+14 */ u32        unk_88_14;          //
    } unk_88;
    /* +8C */ u8                _pad_8C[0xA4-0x8C]; // 填充至偏移 0xA4
    /* +A4 */ u8                unk_A4;             // ?
    /* +A5 */ u8                _pad_A5[0xA6-0xA5]; // 填充
    /* +A6 */ u16               unk_A6;             // 状态0更新方法在转为状态35(碰撞)时设为 0
    /* +A8 */ u8                _pad_A8[0xB3-0xA8]; // 填充至偏移 0xB3
    /* +B3 */ u8                unk_B3;             // 在 0802D0A0 中递减计数的某个值?
    /* +B4 */ u8                unk_B4;             // ?
    /* +B5 */ u8                _pad_B5[0xC0-0xB5]; // 填充至偏移 0xC0
    /* +C0 */ u8                unk_C0;             // 状态0更新方法开始时被设为 0
    /* +C1 */ u8                unk_C1;             // 状态改变时有时被设为 1
    /* +C2 */ u8                _pad_C2;            // 填充
    /* +C3 */ u8                next_state;         // 下一个状态标识符; 状态0更新方法检测到非零时会切换到此状态
    /* +C4 */ u8                anim_counter;       // 动画计数器?
    /* +C5 */ u8                unk_C5;             // 递减计数; 0802F3CC 检查此值做处理
    /* +C6 */ u8                unk_C6;             // ?
};

// Assert: sizeof(PlayerActor) == 0xC8

// ═══════════════════════════════════════════════════════════════════════════════
// ScheduledActor 结构体 (继承自 AbstractActor)
// vtable: 080EF718 (纯虚)
// ═══════════════════════════════════════════════════════════════════════════════
struct ScheduledActor {
    /* +00 */ AbstractActor    base;               // 基类 (vtable: 080EF718)
    /* +30 */ u32              character_data_ptr; // 指向角色数据 (CharacterData) 的指针
    /* +34 */ u32              game_data_ptr;      // 指向游戏数据 (GameData) 的指针
    /* +38 */ u32              actor_script_ptr;   // 指向角色脚本 (ActorScript) 的指针
    /* +3C */ u8               current_schedule;   // 当前日程标识符 (默认: CharacterData+0x96 bit)
    /* +3D */ u8               running_schedule_entry; // 正在执行的日程条目 ID (-1?) (默认: CharacterData+0x101 bit)
    /* +3E */ u8               running_script_entry;   // 正在执行的脚本条目 ID? (默认: CharacterData+0x106 bit)
    /* +3F */ u8               unk_3F;             // ?
    /* +40 */ u16              script_timer;       // 距离上一个脚本节点的时间 (帧数)? (默认: CharacterData+0x111 bit)
    /* +42 */ u16              unk_42;             // 构造函数参数 7 ([sp+0x0C]) 传入
    /* +44 */ u16              anim_id_1;          // 某个动画 ID? (默认: 构造函数参数 5 [sp+0x04])
    /* +46 */ u16              anim_id_2;          // 某个动画 ID? (默认: 构造函数参数 6 [sp+0x08])
};

// Assert: sizeof(ScheduledActor) == 0x48

// ═══════════════════════════════════════════════════════════════════════════════
// Game 对象结构体 (由 08017740 构造)
// 这是一个巨大的整体对象，包含游戏运行所需的所有数据。
// ═══════════════════════════════════════════════════════════════════════════════
struct GameObject {
    /* +0000 */ u32         vtable_ptr;             // vtable 指针

    // 重要内联对象 (由 080B18C0 构造)
    /* +0004 */ struct InlineObj {
        /* +0000 */ u32     some_obj_ptr;           // 指向某个对象的指针
            // +00: 地图 ID?
            // +04: 地图 ID?
            // +08: 摄像机 X (Q16)
            // +0C: 摄像机 Y (Q16)
            // +2C: 地形数据指针
            // +84: ?
            // +88: ?
            // +8C: ?
            // +90: vtable (080AA954)
        /* +0004 */ u32     entity_ptrs[0x64];      // 实体指针数组
            //  索引 00 = Player (玩家)
            //  索引 01 = Lillia (莉莉娅)
            //  索引 02 = Rick (里克)
            //  索引 03 = Popuri (波普莉)
            //  索引 04 = Barley (巴利)
            //  索引 05 = May (梅)
            //  索引 06 = Saibara (塞巴拉)
            //  索引 07 = Gray (格雷)
            //  索引 08 = Duke (杜克)
            //  索引 09 = Manna (曼娜)
            //  索引 0A = Basil (巴西尔)
            //  索引 0B = Anna (安娜)
            //  索引 0C = Mary (玛莉)
            //  索引 0D = Thomas (托马斯)
            //  索引 0E = Harris (哈里斯)
            //  索引 0F = Ellen (艾伦)
            //  索引 10 = Stu (斯图)
            //  索引 11 = Jeff (杰夫)
            //  索引 12 = Sasha (莎夏)
            //  索引 13 = Karen (卡莲)
            //  索引 14 = Doctor (医生)
            //  索引 15 = Elli (艾丽)
            //  索引 16 = Carter (卡特)
            //  索引 17 = Cliff (克里夫)
            //  索引 18 = Doug (道格)
            //  索引 19 = Ann (安)
            //  索引 1A = Kai (凯)
            //  索引 1B = Gotz (戈茨)
            //  索引 1C = Zack (扎克)
            //  索引 1D = Won (旺)
            //  索引 1E = Gourmet (美食家)
            //  索引 1F = Harvest Goddess (女神)
            //  索引 20 = Kappa (河童)
            //  索引 21 = Van (班)
            //  索引 22 = Luu/Ruby (露?)
            //  索引 23 = ?
            //  索引 24-2A = Harvest Sprites (小精灵)
            //     (顺序: Staid, Nappy, Bold, Chef, Aqua, Hoggy, Timid)
            //  索引 2B = Dog (狗)
            //  索引 2C = Horse (马)
            //  索引 2D-54 = 玩家动物?
            //  索引 55-57 = 养鸡场的小鸡
            //  索引 58-5A = 约德尔农场的奶牛
            //  索引 5B = Hannah (汉娜)
            //  备注: 索引 01-23 均为 ScheduledActor 实例
        /* +0194 */ u32     unk_194;                // ?
        // +0198: ...
        /* +0238 */ struct {                        // 数组，15/16 个对象 (大小: 0x84)
            u8   field_00;
            u8   field_01;
            u8   field_02;
            u8   field_03;
            u8   data[0x80];                        // ???
        } unk_238[0x15];                            // 约 21 个条目
        /* +0D10 */ struct {                        // 12/13 个对象 (大小: 0x0C)
            struct {
                u32 field_00;                       // PaletteSlotHolder?
                u32 field_04;
            } palette_holder;
            u8  palette_id;                         // 调色板 ID
            u8  unk_09;                             // ?
            u8  unk_0A;                             // ?
        } palette_entries[0x0D];                    // 约 13 个条目
        /* +0DAC */ u8     unk_DAC;                // ?
        /* +0DAD */ u8     unk_DAD;                // ?
        /* +0DB0 */ struct DefinedSprite {
            u32 field_00;
            u32 field_04;
            u32 field_08;
            u32 field_0C;
            u32 field_10;
            u32 field_14;
            u32 field_18;
            u32 field_1C;
            u32 field_20;
            u32 field_24;
            u32 field_28;
            u32 field_2C;
        } sprites[];                                // DefinedSprite 数组 (大小 0x30 每个)
        //   +00: DefinedSprite (08522C48, 地图角色)
        //   +30: DefinedSprite (08607DDC, 物品图标)
        //   +60: DefinedSprite (086C491C, 电视节目?)
        //   +90: DefinedSprite (086A049C, ?)
        //   +C0: DefinedSprite (086C2F38, 表情气泡?)
        //   +F0: DefinedSprite (086C47F0, 小圆圈?)
        //   +120: DefinedSprite (086C46C8, ?)
        //   +150: DefinedSprite (0860759C, ?)
        //   +180: DefinedSprite (086CD490, 大圆圈?)
        //   +1B0: DefinedSprite (086CC6E8, 月亮?)
        //   +1E0: DefinedSprite (086CCD84, ?)
        //   +210: DefinedSprite (086CB7BC, 云?)
        //   +240: DefinedSprite (086989C8, ?)
        /* +1020 */ u32     auto_ptr_obj_1;         // auto_ptr 指向某个对象 (析构函数: 0803AF78)
                                                    //  +00: 非拥有指针指向对象
                                                    //     +00: vtable
                                                    //  +04: 持有 TileVramManagerHandle 的对象数组 (3个, 大小0x2C?)
                                                    //  +8C: byte
        /* +1024 */ u32     auto_ptr_obj_2;         // auto_ptr (析构函数: 080B0530)
                                                    // 持有更多 TileVramManagerHandle 的对象
        /* +1028 */ u32     unk_1028;               // ?
    } inline_obj;

    /* +1038 */ u32         gamedata_ptr;           // GameData 指针 (由构造函数参数 r1 设置)
    /* +103C */ u8          unk_103C;               // ?
    /* +1040 */ struct {
        /* +00 */ u32       ptr_to_1038_plus_10;    // 指向 [+1038]+0x10 的指针
        /* +04 */ u8        unk_1040_04;            // ?
    } unk_1040;
    /* +1048 */ u32         unk_1048;               // ? (080177AA)
    /* +104C */ u8          unk_104C;               // ? (080177D6)
    /* +1050 */ u32         farm_terrain_ptr;       // 指向农场地形数据的指针 (大小: 0xB000) (080177E0)
    /* +1054 */ u32         some_obj_ptr_1;         // 指向某个对象 (初始化为构造函数参数 r2)
    /* +1058 */ u32         unk_1058;               // ? (080177F4)
    /* +105C */ u32         unk_105C;               // ? (080177FA)
    /* +1060 */ u8          _pad_1060[0x1064-0x1060];
    /* +1064 */ u32         unk_1064;               // ? (08017800)
    /* +1068 */ u32         unk_1068;               // ? (08017808)
    /* +106C */ u8          _pad_106C[0x1074-0x106C];
    /* +1074 */ u32         unk_1074[2];            // ?
    /* +107C */ u32         auto_ptr_tilevram;      // auto_ptr (析构函数: 0803B3A8)
                                                    // 持有 TileVramManagerHandle 的对象
    /* +1080 */ struct {
        u32 field_00;
        u32 field_04;
        u32 field_08;
        // +08: 2bit ?
        // +0C: word ?
    } tilevram_handles[4];                          // 4 个 TileVramManagerHandle 对象 (大小 0x0C)
    /* +10B0 */ u32         unk_10B0[6];            // 6 个指针数组 (指向 vtable 在 +24 的对象)
    /* +10C8 */ u8          unk_10C8;               // ?
};

// ═══════════════════════════════════════════════════════════════════════════════
// AbstractEntity vtable 布局 (vtable: 080EE790)
// ═══════════════════════════════════════════════════════════════════════════════
// 偏移 | 签名                        | 说明
// ─────┼─────────────────────────────┼────────────────────────────────
// +08  | ~AbstractEntity()            | 析构函数
// +0C  | Box getBox()                 | 返回碰撞盒 {left,top,right,bottom} (默认: {x,y,x,y})
// +10  | void init()                  | 初始化?
// +14  | void onMapChange()           | 地图 ID 改变时调用?
// +18  | void update()                | 更新 (默认: 调用 [+10 对象 vtable]+0C) (此方法重要)
// +1C  | void vfunc_1C(int)           | (默认: 调用 [+10 对象 vtable]+10 并传参)
// +20  | void activate()              | (默认: 将 +06 字节设为 1)
// +24  | void deactivate()            | (默认: 将 +06 字节设为 0)
// +28  | int  isActive()              | (默认: 返回 +06 字节)
// +2C  | void vfunc_2C(int)           | (默认: 调用 [+10 对象 vtable]+0C)
// +30  | GraphicalObj* makeGraphic()  | (默认: purefunc) 创建图形对象

// ═══════════════════════════════════════════════════════════════════════════════
// AbstractActor vtable 布局 (vtable: 080EEDB8)
// ═══════════════════════════════════════════════════════════════════════════════
// 偏移 | 签名                        | 说明
// ─────┼─────────────────────────────┼────────────────────────────────
// +00  | AbstractEntity vtable        | 继承基类虚函数表
//      |   +0C getBox()               | 默认返回 {x-7, y-4, x+7, y+5}
// +34  | int vfunc_34()               | (默认: 返回 0)
// +38  | void vfunc_38(...)           | (默认: nullsub)

// ═══════════════════════════════════════════════════════════════════════════════
// vtable_80EEA94 vtable 布局
// ═══════════════════════════════════════════════════════════════════════════════
// 偏移 | 签名                        | 说明
// ─────┼─────────────────────────────┼────────────────────────────────
// +00  | AbstractActor vtable         | 继承 AbstractActor
//      |   +0C getBox()               | 默认返回 {x-7, y-9, x+7, y+5}
// +3C  | void vfunc_3C(...)           | (默认: nullsub)
// +40  | void vfunc_40(...)           | (默认: nullsub)
// +44  | int  vfunc_44(...)           | (默认: 返回 0)
// +48  | int  vfunc_48(...)           | (默认: 返回 0)
// +4C  | int  vfunc_4C(...)           | (默认: 返回 0)
// +50  | int  vfunc_50(...)           | (默认: 返回 0)
// +54  | int  vfunc_54(...)           | (默认: 返回 0)
// +58  | int  vfunc_58(...)           | (默认: 返回 0)
// +5C  | int  vfunc_5C(...)           | (默认: 返回 0)
// +60  | int  vfunc_60(...)           | (默认: 返回 0)
// +64  | void vfunc_64(...)           | (默认: nullsub)
// +68  | void vfunc_68(...)           | (默认: nullsub)
// +6C  | void vfunc_6C(...)           | (默认: nullsub)
// +70  | void vfunc_70(...)           | (默认: nullsub)
// +74  | int  vfunc_74(...)           | (默认: 返回 5)
// +78  | int  vfunc_78(...)           | (默认: 返回 5)
// +7C  | void vfunc_7C(...)           | (默认: nullsub)
// +80  | void vfunc_80(...)           | (默认: nullsub)
// +84  | void setFacing(int facing,   | (默认: nullsub, 在 0802D2A6 处调用)
//      |          int unk)
// +88  | ??? vfunc_88()               | (默认: purefunc)

// ═══════════════════════════════════════════════════════════════════════════════
// AbstractPlayerActor vtable 布局
// ═══════════════════════════════════════════════════════════════════════════════
// 偏移 | 签名                        | 说明
// ─────┼─────────────────────────────┼────────────────────────────────
// +00  | AbstractActor vtable         | 继承 AbstractActor
// +40  | bool isBusy()                | 是否忙碌?
// +64  | void modifyStaminaFatigue(   | 增减体力和疲劳值
//      |     int stamina, int fatigue)|
// +6C  | void resetState()            | 将 +A4 和 +88 设为 0, 动画设为 192 (站立)

// ═══════════════════════════════════════════════════════════════════════════════
// ScheduledActor vtable 布局
// ═══════════════════════════════════════════════════════════════════════════════
// 偏移 | 签名                        | 说明
// ─────┼─────────────────────────────┼────────────────────────────────
// +00  | AbstractActor vtable         | 继承 AbstractActor
// +3C  | void scheduleUpdate(int)     | 日程更新?

// ═══════════════════════════════════════════════════════════════════════════════
// Game Object vtable 布局
// ═══════════════════════════════════════════════════════════════════════════════
// 偏移 | 签名                              | 说明
// ─────┼───────────────────────────────────┼────────────────────────────────
// +008 | ~GameObject()                      | 析构函数
// +014 | int getActiveLocation()            | 获取当前活动地点 ID
// +018 | int getCameraX()                   | 获取摄像机 X 坐标
// +01C | int getCameraY()                   | 获取摄像机 Y 坐标
// +020 | void setCamera(int x, int y)       | 设置摄像机位置
// +024 | (move camera?)                     | 移动摄像机? 涉及平方根计算!
// +02C | int getLocationPxWidth(int)        | 获取地点像素宽度
// +030 | int getLocationPxHeight(int)       | 获取地点像素高度
// +034 | TerrainData getLocationTerrain(int)| 获取地点地形数据
// +038 | void makeActorMaybe(int)           | 创建角色?
// +040 | AbstractActor* getActor(int)       | 通过 ID 获取角色指针
// +064 | AbstractSprite* getItemSprite()    | 获取物品精灵
// +068 | AbstractSprite* getMapActorSprite()| 获取地图角色精灵
// +0B4 | ??? vfunc_0B4(EntityLocation*,int) | (08019D70)
// +120 | bool vfunc_120(EntityLocation*)    |
// +144 | Unk* getUnk_144()                  | 获取 [+1038]+08
// +14C | Unk* getMusicPlayer()              | 获取音乐播放器 ([[+1054]+04]+0D0)

// ═══════════════════════════════════════════════════════════════════════════════
// 常用函数声明 (基于反编译笔记)
// ═══════════════════════════════════════════════════════════════════════════════
// 080350C0 | ScriptedActor ScriptedActor_construct(
//          |     GameObject*, CharacterData*, GameData*,
//          |     ActorScript*, int unk, int unk, int unk)
// ScriptedActor 使用 vtable_80EF718

#endif // DECOMP_ENTITIES_HH

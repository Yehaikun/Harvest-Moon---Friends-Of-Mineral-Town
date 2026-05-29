// SPDX-License-Identifier: GPL-3.0-or-later
//
// 游戏主数据对象 (GameData) — 反编译笔记
// GameData struct layout — reverse-engineering notes
//
// 来源:
//   /tmp/FOMT-DOC/GameData.txt  — GameData 结构体布局
//
// 注意: 所有地址均为 MFOMTU (美版) ROM 地址。
// 根据笔记, [GameObject+1038]/[PlayerActor+38] 引用的对象与
// 0x08011730 构造的对象是同一个 GameData 类。
// 本文档仅用于反编译参考, 部分字段含义尚未确认。
//
// 结构体总览:
//   +0000 — (未记录字段, 8 字节)
//   +0008 — DateTimeContainer (含 GameDateTime)
//   +0014 — FarmObject (农场名称/背包/房屋/…)
//   +1AB8 — WalletData (金钱/…)
//   +1BE8 — PlayerData (角色信息/工具/背包栏)
//   +1C80 — Unknown1C80
//   +1CB0 — Unknown1CB0
//   +1CDC — EntityLocation
//   +1CE4 — LargeObject1CE4 (含 CharacterData)
//   +2164 — Unknown2164 (0xA0 字节, 大量位域)
//   +2204 — Unknown2204
//   +220C — byte[9]
//   +2215 — byte[4]
//   +221C — byte
//   +222C — byte
//   +223C — byte
//   +224C — Unknown224C
//   +2250 — Unknown2250 (记录中断)
//
// 引用方构造地址:
//   - FarmObject:         0x08009AB0
//   - PlayerInventory:    0x0800B2DC
//   - PlayerHouse:        0x0800BEE0
//   - BagObject:          0x0800F650
//   - Object1C80_sub:     0x080A0298 / 0x080A0098
//   - LargeObject1CE4:    0x080A407C
//
// 工具提示: 每个 $ 前缀表示十六进制数。
// 如 $D = 0x0D = 13, $40 = 0x40 = 64.

#pragma once

#include <cstdint>
#include "types.hh"

// ============================================================================
// 基础结构体
// ============================================================================

/**
 * 实体位置 (EntityLocation) — 6 字节
 * 传给 AbstractEntity 构造函数作为 r2 参数。
 * 位布局: 10bit 地图ID + 16bit X + 16bit Y = 42bit, 打包为 48bit(6 字节)。
 * 对应 types.hh::Location。
 */
struct EntityLocation {
    uint16_t location_id : 10;  // +00bit | 10bit | 位置标识符(地图 ID, 0~1023)
    uint16_t x            : 16;  // +10bit | 16bit | X 像素坐标
    uint16_t y            : 16;  // +26bit | 16bit | Y 像素坐标
} __attribute__((packed));

/**
 * 角色位置 (ActorLocation) — 8 字节
 * 由 EntityLocation + 朝向组成。
 * 对应 types.hh::ActorLocation。
 */
struct ActorLocation {
    EntityLocation location;  // +00 | EntityLocation | 实体位置
    uint8_t        facing;    // +06 | byte | 朝向 (0=下, 1=上, 2=左, 3=右)
    uint8_t        _pad;      // +07 | 对齐填充
} __attribute__((packed));

/**
 * 游戏日期时间 — 4 字节
 * 位于外层对象的 +08 偏移处。
 */
struct GameDateTime {
    uint8_t year    : 8;  // +00bit | 8bit | 年
    uint8_t season  : 2;  // +08bit | 2bit | 季节 (0=春, 1=夏, 2=秋, 3=冬)
    uint8_t day     : 5;  // +10bit | 5bit | 日
    uint8_t hours   : 5;  // +16bit | 5bit | 小时
    uint8_t minutes : 6;  // +21bit | 6bit | 分钟 (每 25 帧增加 1)
    // 总计 26bit, 打包至 4 字节
} __attribute__((packed));

/**
 * 角色数据 (CharacterData)
 */
struct CharacterData {
    /* +00 */ ActorLocation actor_location;  // 角色位置与朝向 (8 字节)
    /* +08 */ uint8_t       _pad_08[4];      // 未记录字段 / 对齐填充

    // 位域块 (+0C, 4 字节, 共 25bit)
    /* +0C */ uint16_t relationship   : 5;   // +0C+00bit | 5bit  | 好感度字段?
    /* +0C */ uint16_t field_0C_5     : 5;   // +0C+05bit | 5bit  | ?
    /* +0C */ uint16_t field_0C_10    : 5;   // +0C+10bit | 5bit  | ?
    /* +0C */ uint16_t field_0C_15    : 10;  // +0C+15bit | 10bit | ?

    /* +10 */ uint8_t  _pad_10[2];            // 对齐填充
    /* +12 */ int16_t  animation_id;          // +12 | short | 动画 ID
    // 若 animation_id == -1(0xFFFF), ScriptedActor 构造函数将取 sp+04 参数
} __attribute__((packed));

/**
 * 物品参考 (ItemEx) — 4 字节
 * 在 PlayerHouse 的 +008 处作为 ItemEx[$40] 出现 (地址 0x0800B6D0, 0x0800DEDC)。
 */
struct ItemEx {
    /* +00 */ uint8_t  unknown[4];  // 物品扩展数据
} __attribute__((packed));

/**
 * 工具数据 (ToolEx) — 2 字节
 * 工具/道具在背包中的存储格式。
 * 在 ToolBox 中作为 ToolEx[$40] 出现 (地址 0x0800DC3C)。
 */
struct ToolEx {
    /* +00 */ uint8_t data[2];  // 工具数据
} __attribute__((packed));

// ============================================================================
// 农场对象 (FarmObject) — 位于 GameData+0x0014, 大小 0x1AA4 字节
// 构造地址: 0x08009AB0
// ============================================================================

/**
 * 玩家背包 (PlayerInventory) — 0x1A0 字节
 * 位于 FarmObject+0x40。
 */
struct PlayerInventory {
    // 手持物品信息头部 (4 字节, 位域布局):
    //   [0:2]   = held_type  (3bit)  — 手持物品类型 (0=普通物品)
    //   [3]     = has_held   (1bit)  — 是否持有物品
    //   [4:15]  = 未使用/未知 (12bit)
    //   [16:23] = item_id    (8bit)  — 物品 ID (可能为 union, 由 held_type 区分)
    //   [24:31] = field_24   (8bit)  — ?
    /* +00 */ uint32_t header;                // 头部位域 (4 字节)

    // 物品数组 (103 个条目, 每个 4 字节)
    // 构造地址: 0x0800B2DC
    /* +04 */ struct InventoryEntry {
        /* +00 */ uint8_t unk_bits  : 7;  // +00bit | 7bit | ?
        /* +00 */ uint8_t flag      : 1;  // +07bit | 1bit | ? (默认 false, 由 0x0800B344 设置)
        /* +01 */ uint8_t _pad[3];        // 剩余 3 字节未使用
    } __attribute__((packed)) items[103];  // 103 个物品槽
} __attribute__((packed));

/**
 * 房屋物品槽 (2 字节) — 位于 PlayerHouse+0x108 的数组元素
 * 数组构造地址: 0x0800B954, 0x0800E080
 */
struct HouseItemSlot {
    /* +00 */ uint8_t data[2];  // 2 字节物品数据
} __attribute__((packed));

/**
 * 工具盒 (ToolBox) — 0x80 字节
 * 位于 PlayerHouse+0x18C, 存放 ToolEx[$40]。
 * 构造地址: 0x0800B35C (构造函数会填充默认内容)
 */
struct ToolBox {
    /* +00 */ ToolEx tools[64];  // ToolEx[$40] — 64 个工具槽
} __attribute__((packed));

/**
 * 房屋未知对象 (at +0x20C) — 0x20 字节
 * 构造地址: 0x0800BCC8。
 */
struct HouseExtraData {
    // 数组: 4 个对象, 每个 4 字节
    /* +00 */ struct Entry4 {
        /* +00 */ uint8_t  field_bits : 1;  // +00bit | 1bit  | ?
        /* +00 */ uint16_t field_val  : 16; // +01bit | 16bit | ? (总计 17bit)
        /* +02 */ uint8_t  _pad[2];
    } __attribute__((packed)) group_a[4];

    // 同上格式的第二个数组 (4 个对象, 每个 4 字节)
    /* +10 */ Entry4 group_b[4];
} __attribute__((packed));

/**
 * 玩家房屋数据 (PlayerHouse) — 0x22C 字节
 * 位于 FarmObject+0x1E0。
 * 构造地址: 0x0800BEE0
 */
struct PlayerHouse {
    // 房屋位域 (6 字节, 48bit)
    /* +000 */ uint8_t  house_size : 2;  // +000+00bit | 2bit  | 房屋大小标识符
    /* +000 */ uint8_t  flag_008   : 1;  // +000+08bit | 1bit  | ?
    /* +000 */ uint8_t  flag_009   : 1;  // +000+09bit | 1bit  | ?
    /* +000 */ uint8_t  flag_010   : 1;  // +000+10bit | 1bit  | ?
    /* +000 */ uint8_t  flag_011   : 1;  // +000+11bit | 1bit  | ?
    /* +000 */ uint8_t  flag_012   : 1;  // +000+12bit | 1bit  | ?
    /* +000 */ uint8_t  flag_013   : 1;  // +000+13bit | 1bit  | ?
    /* +000 */ uint8_t  flag_014   : 1;  // +000+14bit | 1bit  | ?
    /* +000 */ uint8_t  field_015  : 8;  // +000+15bit | 8bit  | ? (默认 0x6A)
    /* +000 */ uint8_t  flag_027   : 1;  // +000+27bit | 1bit  | ?
    /* +000 */ uint8_t  flag_028   : 1;  // +000+28bit | 1bit  | ?
    /* +000 */ uint8_t  flag_029   : 1;  // +000+29bit | 1bit  | ?
    /* +000 */ uint8_t  field_030  : 2;  // +000+30bit | 2bit  | ?
    /* +000 */ uint8_t  field_032  : 6;  // +000+32bit | 6bit  | ? (默认 0x1A)
    /* +000 */ uint8_t  flag_038   : 1;  // +000+38bit | 1bit  | ?
    /* +000 */ uint8_t  flag_039   : 1;  // +000+39bit | 1bit  | ?
    /* +000 */ uint8_t  field_040  : 8;  // +000+40bit | 8bit  | ?
    // 注: 上面 48bit 跨字节打包; C++ 位域声明顺序从 LSB 开始与 GBA 一致。

    /* +008 */ ItemEx                  items[64];       // ItemEx[$40] 物品数组
    /* +108 */ HouseItemSlot           extra_slots[64]; // 64 个 2 字节槽位
    /* +188 */ uint8_t                 house_flags[4];  // 4 字节位域对象
    /* +18C */ ToolBox                 toolbox;         // ToolEx[$40] 工具盒
    /* +20C */ HouseExtraData          extra_data;      // 额外数据对象
} __attribute__((packed));

/**
 * 农场对象分组 A (+0x40C) — 0x1E0 字节
 * 位于 FarmObject+0x40C。
 * 构造地址: 0x0800C4C4
 */
struct FarmObjectGroupA {
    // 头部位域 (4 字节)
    //   bit  0 | 1bit  | ?
    //   bits 1-10 | 10bit | ?
    //   bit 11    | 1bit  | ?
    //   bits 12-19 | 8bit  | ?
    //   bit 20    | 1bit  | ?
    //   bits 21-31 | (未使用)
    // 此 32-bit 字段的 byte 3 (+003) 可单独读取
    /* +000 */ uint32_t header_000;         // 头部位域 (4 字节)

    /* +004 */ uint8_t  field_004 : 2;      // +004+00bit | 2bit | ?
    /* +004 */ uint8_t  _pad1     : 6;

    /* +008 */ uint8_t  byte_008;           // +008 | byte | ?
    /* +009 */ uint8_t  _pad2[15];          // +009 ~ +017 对齐填充

    // 数组: 8 个对象, 每个 0x30 字节
    /* +018 */ struct GroupAEntry {
        /* +00 */ uint8_t data[0x30];
    } entries_a[8];                       // +018 | array of 8 × $30

    // 数组: 8 个对象, 每个 8 字节
    /* +198 */ struct GroupBEntry {
        /* +00 */ uint8_t  raw[8];  // 位域布局: +00bit 10bit, +10bit 6bit,
                                     // +16bit 10bit, +26bit 6bit, +32bit 10bit,
                                     // +48bit 3bit (默认 0x23A, 0, 0, 0, 0, 0)
    } __attribute__((packed)) entries_b[8];  // +198 | array of 8 × $8

    // 数组: 2 个对象, 每个 4 字节
    /* +1D8 */ struct GroupCEntry {
        /* +00 */ uint8_t  field_0 : 2;  // +00bit | 2bit | ?
        /* +00 */ uint8_t  field_2 : 1;  // +02bit | 1bit | ?
        /* +00 */ uint8_t  _pad[3];
    } __attribute__((packed)) entries_c[2];  // +1D8 | array of 2 × $4
} __attribute__((packed));

/**
 * 农场对象分组 B (+0x5EC) — 0x3EC 字节
 * 位于 FarmObject+0x5EC。
 * 构造地址: 0x0800CE30
 */
struct FarmObjectGroupB {
    // 位域块 +00 (4 字节)
    //   bit 0     | 1bit  | ?
    //   bits 1-10 | 10bit | ?
    //   bit 11    | 1bit  | ?
    //   bit 12    | 1bit  | ?
    //   bits 13-28 | 16bit | ?
    //   bits 29-30 | 2bit  | ?
    //   bit 31    | 1bit  | ?
    /* +00 */ uint32_t flags_00;              // 位域块 (4 字节)

    // 字节 4-6 位域布局:
    //   byte 4 bits 4-7 + byte 5 bits 0-5 = 10-bit field
    //   byte 5 bits 6-7 + byte 6 bits 0-7 = 10-bit field
    /* +04 */ uint8_t  data_04_06[3];         // 字节 4-6 (位域)

    /* +07 */ uint8_t  byte_pair_07[2];       // +07 | byte[2] | ?
    /* +09 */ uint8_t  _pad_09[3];            // 填充至 +0C

    /* +0C */ uint8_t  byte_0C;               // +0C | byte    | ?
    /* +0D */ uint8_t  _pad_0D[0x0F];         // 填充至 +1C
    /* +1C */ uint8_t  byte_1C;               // +1C | byte    | ?
    /* +1D */ uint8_t  _pad_1D[0x0F];         // 填充至 +2C

    // 子数组: 16 个对象, 每个 0x3C 字节 (构造地址: 0x0800DA70)
    /* +2C */ struct GroupBSubEntry {
        /* +00 */ uint8_t  flag    : 1;   // +00bit | 1bit | ?
        /* +00 */ uint8_t  _pad[0x3B];    // 剩余 0x3B 字节未记录
    } __attribute__((packed)) sub_entries[16];  // +2C | array of 16 × $3C

    // 总大小: +2C + 16*0x3C = 0x3EC
} __attribute__((packed));

/**
 * 农场数组条目 — 4 字节
 * 位于 FarmObject+0x9D8, 共 1075 个条目。
 * 构造地址: 0x08009FFC
 */
struct FarmArrayEntry {
    /* +00 */ uint8_t  byte_00;           // +00 | byte | ?
    /* +00 */ uint8_t  field_08 : 4;      // +00+08bit | 4bit | ?
    /* +00 */ uint8_t  field_12 : 5;      // +00+12bit | 5bit | ?
    /* +00 */ uint8_t  field_17 : 3;      // +00+17bit | 3bit | ? (默认 1, 由 0x0800A084 设置)
} __attribute__((packed));

/**
 * 农场/角色数据对象 (FarmObject) — 0x1AA4 字节
 * 位于 GameData+0x0014。
 * 构造地址: 0x08009AB0
 */
struct FarmObject {
    /* +000 */ char     farm_name[0x0D];        // +000 | byte[$D] | cstring 农场名称
    /* +00D */ uint8_t  _pad_00D[3];            // 填充至 +010

    // 位域块 (+010, 10+1+1+1 = 13bit)
    /* +010 */ uint16_t field_010_0  : 10;      // +010+00bit | 10bit | ?
    /* +010 */ uint8_t  flag_010_10  : 1;       // +010+10bit | 1bit  | ?
    /* +010 */ uint8_t  flag_010_11  : 1;       // +010+11bit | 1bit  | ?
    /* +010 */ uint8_t  flag_010_12  : 1;       // +010+12bit | 1bit  | ?
    /* +010 */ uint8_t  _pad_bits    : 4;       // 未使用位

    /* +013 */ uint8_t  _pad_013[0x20];         // +013 ~ +032 未记录字段

    /* +033 */ uint8_t  value_033;              // +033 | byte | ? (位值, 参见 0x0800E9E0)

    /* +034 */ uint8_t  _pad_034[0x0C];         // +034 ~ +03F 填充至 +040

    /* +040 */ PlayerInventory inventory;        // 玩家背包 (0x1A0 字节)

    /* +1E0 */ PlayerHouse      house;          // 玩家房屋数据 (0x22C 字节)

    /* +40C */ FarmObjectGroupA group_a;        // 分组 A (0x1E0 字节)

    /* +5EC */ FarmObjectGroupB group_b;        // 分组 B (0x3EC 字节)

    /* +9D8 */ FarmArrayEntry   array_9D8[1075]; // 1075 个条目 (0x10CC 字节)
    // 总大小: 0x9D8 + 1075*4 = 0x9D8 + 0x10CC = 0x1AA4
} __attribute__((packed));

// ============================================================================
// 钱包数据 (WalletData) — 位于 GameData+0x1AB8, 大小 0x130 字节
// 构造地址: 0x0809FAE4, 0x0809FDD8
// ============================================================================

/**
 * 钱包/货币数据 (WalletData) — 0x130 字节
 */
struct WalletData {
    /* +000 */ uint16_t money;                     // +000 | word | 金钱 (默认 500)
    /* +002 */ uint8_t  _pad_002[2];              // 填充至 +004

    /* +004 */ uint8_t  flags_004;                // 位域: bit0=?, bit1=?
    /* +005 */ uint8_t  _pad_005[3];              // 填充至 +008

    /* +008 */ uint16_t field_008;                // +008 | word | ?
    /* +00A */ uint8_t  _pad_00A[2];              // 填充至 +00C

    /* +00C */ struct WalletEntry {
        uint8_t data[8];                          // 8 字节条目
    } entries[30];                                // 数组 (0xF0 字节, +00C ~ +0FB)

    /* +0FC */ uint16_t field_0FC;                // +0FC | word | ?
    /* +0FE */ uint8_t  _pad_0FE[0x22];           // 填充至 +120

    /* +120 */ uint16_t field_120;                // +120 | word | ?
    /* +122 */ uint8_t  _pad_122[2];              // 填充至 +124
    /* +124 */ uint16_t field_124;                // +124 | word | ?
    /* +126 */ uint8_t  _pad_126[2];              // 填充至 +128
    /* +128 */ uint16_t field_128;                // +128 | word | ?
    /* +12A */ uint8_t  _pad_12A[2];              // 填充至 +12C
    /* +12C */ uint16_t field_12C;                // +12C | word | ?
    /* +12E */ uint8_t  _pad_12E[2];              // 填充至 0x130 字节
} __attribute__((packed));

// ============================================================================
// 玩家数据 (PlayerData) — 位于 GameData+0x1BE8, 大小 0x98 字节
// ============================================================================

/**
 * 手持物品槽 — 4 字节
 * 类似 PlayerInventory 的头部格式。
 * 位于 PlayerData+0x54, 构造地址: 0x0800F24C
 */
struct HeldItemSlot {
    /* +00 */ uint8_t  type    : 3;  // +00+00bit | 3bit  | ? (同手持物品类型)
    /* +00 */ uint8_t  has     : 1;  // +00+03bit | 1bit  | ?
    /* +00 */ uint8_t  _pad[1];
    /* +02 */ int16_t  value;        // +02       | short | ?
} __attribute__((packed));

/**
 * 背包栏对象 — 位于 PlayerData+0x60, 大小 0x38 字节
 * 构造地址: 0x0800F650 (该函数可能处理"袋子"逻辑)
 */
struct BagObject {
    /* +00 */ uint16_t count_a;        // +00 | word | 数组 A 中的对象数量
    /* +02 */ uint8_t  _pad_02[2];     // 填充至 +04

    /* +04 */ struct BagSlot {
        /* +00 */ uint8_t  flag_0 : 1;  // +00+00bit | 1bit | ?
        /* +00 */ uint8_t  flag_1 : 1;  // +00+01bit | 1bit | ?
        /* +00 */ uint8_t  _bits  : 6;
        /* +01 */ uint8_t  default_AB;  // +01 | byte | ? (默认 0xAB)
        /* +02 */ uint8_t  _pad[2];     // 未记录字段
    } __attribute__((packed)) slots_a[8];  // +04 | array of 8 × $4

    /* +24 */ uint16_t count_b;        // +24 | word | 数组 B 中的对象数量
    /* +26 */ uint8_t  _pad_26[2];     // 填充至 +28

    /* +28 */ ToolEx tools[8];         // +28 | ToolEx[8] — 8 个工具槽
    // 总大小: 0x38 字节
} __attribute__((packed));

/**
 * 玩家数据 (PlayerData) — 0x98 字节
 * 位于 GameData+0x1BE8。
 */
struct PlayerData {
    /* +00 */ char          name[0x0D];          // +00 | byte[$D] | cstring 角色名
    /* +0D */ uint8_t       _pad_0D[3];          // 填充至 +10

    /* +10 */ uint8_t       byte_10;             // +10 | byte     | ?
    /* +11 */ uint8_t       _pad_11[0x0F];       // 填充至 +20

    /* +20 */ uint8_t       byte_20;             // +20 | byte     | ?
    /* +21 */ uint8_t       _pad_21[3];          // 填充至 +24

    /* +24 */ ActorLocation location;            // +24 | ActorLocation (8 字节)

    /* +2C */ struct PlayerDataArrayEntry {
        /* +00 */ uint16_t field_00 : 16;  // +00bit | 16bit | ?
        /* +00 */ uint8_t  field_16 : 3;   // +16bit | 3bit  | ?
        /* +00 */ uint8_t  field_19 : 3;   // +19bit | 3bit  | ?
    } __attribute__((packed)) array_2C[6];  // +2C | array of 6 × $4 (24 字节)

    // 位域块 +44 (4 字节, 32bit)
    /* +44 */ uint32_t flags_44;  // +44 位域:
        // bit  0-3  | 4bit  | ?
        // bit  4    | 1bit  | ?
        // bit  5    | 1bit  | ?
        // bit  6    | 1bit  | ?
        // bit  7-14 | 8bit  | ? (默认 150)
        // bit 15-22 | 8bit  | ?
        // bit 23-30 | 8bit  | ?
        // bit 31    | 1bit  | ? (与下一字段共享?)

    // 位域块 +48 (4 字节)
    /* +48 */ uint32_t flags_48;  // +48 位域:
        // bit  0-28 | 29bit | ?
        // bit 29-31 | 3bit  | ? (与下一字段共享?)

    // 位域块 +4C (4 字节)
    /* +4C */ uint32_t flags_4C;  // +4C 位域:
        // bit  0-6  | 7bit  | ?
        // bit  7-14 | 8bit  | ?
        // bit 15-31 | 17bit | ? (与下一字段共享?)

    // 位域块 +50 (2 字节)
    /* +50 */ uint16_t flags_50;  // +50 位域:
        // bit  0-12 | 13bit | ?
        // bit 13-15 | 3bit  | ? (与下一字段共享?)

    // 位域块 +52 (1 字节)
    /* +52 */ uint8_t  field_52_0  : 3;    // +52+00bit | 3bit  | ?
    /* +52 */ uint8_t  flag_52_3   : 1;    // +52+03bit | 1bit  | ?
    /* +52 */ uint8_t  _pad_52     : 4;

    /* +53 */ uint8_t  _pad_53;             // 填充至 +54

    /* +54 */ HeldItemSlot held_item;       // +54 | 手持物品槽 (4 字节)
    /* +58 */ uint8_t       _pad_58[4];     // 填充至 +5C

    /* +5C */ ToolEx       tool;            // +5C | ToolEx | 当前工具 (2 字节)
    /* +5E */ uint8_t       _pad_5E[2];     // 填充至 +60

    /* +60 */ BagObject    bag;             // 背包栏 (0x38 字节, 至 +98)
} __attribute__((packed));

// ============================================================================
// 未知对象 1C80 — 位于 GameData+0x1C80, 大小 0x30 字节
// ============================================================================

/**
 * 内部子对象 — 位于 Unknown1C80+0x00
 * 构造地址: 0x080A0298
 */
struct Inner1C80 {
    /* +00 */ struct CoreObject {
        /* +00 */ ActorLocation location;     // +00 | ActorLocation (默认 loc=2, x=62, y=36)
        /* +08 */ char         name[0x0D];    // +08 | byte[$D] | cstring (13 字节)
        /* +15 */ uint8_t      _pad_15[3];    // 填充至 +18
        // 位域块 (+18, 10+1+1+1+8 = 21bit)
        /* +18 */ uint16_t     field_18_0  : 10; // +18+00bit | 10bit | ? (默认 1)
        /* +18 */ uint8_t      flag_18_10  : 1;  // +18+10bit | 1bit  | ?
        /* +18 */ uint8_t      flag_18_11  : 1;  // +18+11bit | 1bit  | ?
        /* +18 */ uint8_t      flag_18_12  : 1;  // +18+12bit | 1bit  | ?
        /* +18 */ uint8_t      field_18_13 : 8;  // +18+13bit | 8bit  | ?
    } __attribute__((packed)) core;           // 嵌套核心对象

    /* +1C */ uint8_t  byte_1C;              // +1C | byte    | ?
    /* +1D */ uint8_t  flag_1D_0 : 1;        // +1D+00bit | 1bit | ?
    /* +1D */ uint8_t  flag_1D_1 : 1;        // +1D+01bit | 1bit | ?
    /* +1D */ uint8_t  _pad_1D  : 6;
    /* +1E */ uint8_t  _pad_1E[2];           // 填充
} __attribute__((packed));

/**
 * 未知对象 1C80 — 0x30 字节
 * 位于 GameData+0x1C80。
 */
struct Unknown1C80 {
    /* +00 */ Inner1C80 inner;           // 内部对象 (0x20 字节)
    /* +20 */ uint16_t  word_20;          // +20 | word  | ?
    /* +22 */ uint8_t   _pad_22[2];       // 填充至 +24
    /* +24 */ int16_t   short_24;         // +24 | short | ?
    /* +26 */ uint8_t   byte_26;          // +26 | byte  | ?
    /* +27 */ uint8_t   _pad_27[5];       // 填充至 +2C

    // 位域块 (+2C, 10+3+8 = 21bit)
    /* +2C */ uint16_t  field_2C_0 : 10;  // +2C+00bit | 10bit | ?
    /* +2C */ uint8_t   field_2C_10 : 3;  // +2C+10bit | 3bit  | ?
    /* +2C */ uint8_t   field_2C_13 : 8;  // +2C+13bit | 8bit  | ? (默认 10)
    /* +2F */ uint8_t   _pad_2F[1];
} __attribute__((packed));

// ============================================================================
// 未知对象 1CB0 — 位于 GameData+0x1CB0, 大小 0x2C 字节
// ============================================================================

/**
 * 未知对象 1CB0 — 0x2C 字节
 */
struct Unknown1CB0 {
    /* +00 */ uint16_t word_00;                // +00 | word | ?
    /* +02 */ uint8_t  _pad_02[0x22];          // 填充至 +24 (大量未记录字段)
    /* +24 */ EntityLocation default_location; // +24 | EntityLocation (默认 loc=0x23A, x=0, y=0)
    /* +2A */ uint8_t  _pad_2A[2];            // 填充至 0x2C 字节
} __attribute__((packed));

// ============================================================================
// 大型未知对象 (LargeObject1CE4) — 位于 GameData+0x1CE4, 大小 0x480 字节
// 构造地址: 0x080A407C
// ============================================================================

/**
 * 大型对象 — 0x480 字节
 * 包含大量未记录字段, 已知 CharacterData 位于 +0x09C。
 */
struct LargeObject1CE4 {
    /* +000 */ uint8_t unknown_000[0x09C];     // 未记录区域 (0x9C 字节)
    /* +09C */ CharacterData character_data;   // popuri 等人的角色数据
    /* +0B0 */ uint8_t unknown_0B0[0x3D0];     // 剩余未记录区域
    // 总大小: 0x09C + sizeof(CharacterData) + 0x3D0 = 0x480
} __attribute__((packed));

// ============================================================================
// 未知对象 2164 — 位于 GameData+0x2164, 大小 0xA0 字节
// ============================================================================

/**
 * 未知对象 2164 — 0xA0 字节
 * 包含大量位域字段。
 */
struct Unknown2164 {
    /* +00 */ uint16_t word_00;                // +00       | word  | ?
    /* +02 */ uint8_t  _pad_02[0x0A];          // 填充至 +0C

    /* +0C */ int16_t  short_0C;               // +0C       | short | ?
    /* +0E */ uint8_t  byte_0E;                // +0E       | byte  | ?
    /* +0F */ uint8_t  byte_0F;                // +0F       | byte  | ?

    // 大量位域 (从 +10 到约 +9C), 具体含义未完全记录
    // 已知布局 (地址 0x080A407C):
    //   +10+00bit | 1bit  | ?
    //   +10+01bit | 1bit  | ?
    //   +10+02bit | 2bit  | ?
    //   +10+04bit | 1bit  | ?
    //   +10+05bit | 1bit  | ?
    //   +10+06bit | 1bit  | ?
    //   +10+07bit | 2bit  | ?
    //   ... 持续至 +9C, 覆盖大量 1-2bit 字段
    /* +10 */ uint8_t  bitfield_block[0x90];   // +10 ~ +9F 位域数据块
} __attribute__((packed));

// ============================================================================
// 末尾未知对象 (GameData 尾部)
// ============================================================================

/**
 * 对象 2204 — 8 字节
 */
struct Unknown2204 {
    /* +00 */ uint16_t word_00;     // +00 | word | ? (默认 1)
    /* +04 */ uint16_t word_04;     // +04 | word | ?
    /* +06 */ uint8_t  _pad_06[2];  // 填充至 8 字节
} __attribute__((packed));

/**
 * 对象 224C — 4 字节
 * 构造地址: 0x080115D8
 */
struct Unknown224C {
    /* +00 */ uint8_t  flag_0   : 1;  // +00bit | 1bit | ? (默认 1)
    /* +00 */ uint8_t  flag_1   : 1;  // +01bit | 1bit | ? (默认 1)
    /* +00 */ uint8_t  flag_2   : 1;  // +02bit | 1bit | ? (默认 1)
    /* +00 */ uint8_t  flag_3   : 1;  // +03bit | 1bit | ? (默认 1)
    /* +00 */ uint8_t  _pad     : 4;
    /* +01 */ uint8_t  _pad2[3];
} __attribute__((packed));

// ============================================================================
// GameData 主结构体
// ============================================================================

/**
 * 游戏主数据对象 (GameData)
 *
 * 该对象保存了游戏运行时的全部状态:
 *   日期时间、农场数据、金钱、玩家角色、NPC、场景状态等。
 *
 * 引用关系:
 *   - [GameObject+1038] 指向此对象
 *   - [PlayerActor+38]  指向此对象
 *   - 0x08011730 构造函数创建此对象
 *
 * 当前总大小: 至少 0x2254 字节 (记录在 +2250 处中断)
 */
struct GameData {
    /* +0000 */ uint8_t     _unknown_0000[8];         // 未记录字段 (8 字节)

    /* +0008 */ struct DateTimeContainer {
        /* +00 */ uint8_t       _unknown[8];          // +00 ~ +07 未记录字段
        /* +08 */ GameDateTime  datetime;              // 游戏日期时间 (4 字节)
    } __attribute__((packed)) date_time;               // 总计 0x0C 字节

    /* +0014 */ FarmObject      farm;                  // 农场数据 (0x1AA4 字节)

    /* +1AB8 */ WalletData      wallet;                // 钱包数据 (0x130 字节)

    /* +1BE8 */ PlayerData      player;                // 玩家数据 (0x98 字节)

    /* +1C80 */ Unknown1C80     unk_1C80;              // 未知对象 (0x30 字节)

    /* +1CB0 */ Unknown1CB0     unk_1CB0;              // 未知对象 (0x2C 字节)

    /* +1CDC */ EntityLocation  entity_location;       // 实体位置 (6 字节)
    /* +1CE2 */ uint8_t         _pad_1CE2[2];          // 对齐填充

    /* +1CE4 */ LargeObject1CE4 large_obj;             // 大型未知对象 (0x480 字节)

    /* +2164 */ Unknown2164     unk_2164;              // 未知对象 (0xA0 字节)

    /* +2204 */ Unknown2204     unk_2204;              // 未知对象 (8 字节)

    /* +220C */ uint8_t         byte_array_220C[9];    // +220C | byte[9] | ?

    /* +2215 */ uint8_t         byte_array_2215[4];    // +2215 | byte[4] | ?

    /* +2219 */ uint8_t         _pad_2219[3];          // 填充至 +221C

    /* +221C */ uint8_t         byte_221C;             // +221C | byte | ?

    /* +221D */ uint8_t         _pad_221D[0x0F];       // 填充至 +222C

    /* +222C */ uint8_t         byte_222C;             // +222C | byte | ?

    /* +222D */ uint8_t         _pad_222D[0x0F];       // 填充至 +223C

    /* +223C */ uint8_t         byte_223C;             // +223C | byte | ?

    /* +223D */ uint8_t         _pad_223D[0x0F];       // 填充至 +224C

    /* +224C */ Unknown224C     unk_224C;              // 未知对象 (4 字节)

    /* +2250 */ uint8_t         unk_2250[];            // +2250 | 记录在此中断 (作者疲惫了)
} __attribute__((packed));

// ============================================================================
// 原笔记附录 — 非 GameData 内的独立结构体
// ============================================================================

/**
 * 注: types.hh 中已定义 Location / ActorLocation / GameDate / GameTime。
 * 上述 EntityLocation 和 ActorLocation 为本文件在 GameData 上下文中
 * 使用的版本, 与 types.hh 定义对应。
 */

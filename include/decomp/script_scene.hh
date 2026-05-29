// SPDX-License-Identifier: GPL-3.0-or-later
//
// 脚本引擎与场景系统 — 反编译笔记
// Script Engine & Scene System — reverse-engineering notes
//
// 来源:
//   /tmp/FOMT-DOC/EventScripts.txt  — RIFF 格式事件脚本虚拟机
//   /tmp/FOMT-DOC/Scenes.txt        — AbstractScene / GameScene 场景框架
//
// 注意: 所有地址均为 MFOMTU (美版) ROM 地址。
// 这些结构体基于反汇编笔记推导，部分字段含义仍不确定。
//

#pragma once

#include <cstdint>
#include <memory>

// ============================================================================
// 1. RIFF 脚本数据格式 (EventScripts.txt)
// ============================================================================

// RIFF 块头部 (Resource Interchange File Format)
// ROM 中 0x081014BC 处有一个指针数组，每个指针指向一个 RIFF "SCR " 数据块
struct RiffHeader {
    char     magic[4];      // "RIFF"
    uint32_t size;          // 文件大小 - 8
    char     type[4];       // "SCR " — 脚本类型标识
};

// RIFF 子块通用头部
struct RiffChunkHeader {
    char     magic[4];      // 子块标识: "CODE", "JUMP", "STR "
    uint32_t size;          // 子块数据大小
};

// CODE 子块 — 脚本字节码
struct ScriptCodeChunk {
    RiffChunkHeader header; // magic="CODE"
    uint16_t data_size;     // +00 | word | 后续数据大小 (与 header.size 冗余)
    uint8_t  data[];        // +04 | .... | 实际字节码数据
};

// JUMP 子块 — 跳转表 (不一定存在; 指令 24 (select) 使用)
struct ScriptJumpChunk {
    RiffChunkHeader header; // magic="JUMP"

    // 跳转子块数据结构 (解析自 +04 开始的数据):
    // +00 | word | 总数据大小?
    // +04 | ...  | select 指令偏移表: 每个 select imm 对应一个偏移量
    //         跳转数据条目 (被偏移表引用):
    //             +00 | word | case 数量
    //             +04 | word | 默认跳转偏移 (负数表示忽略)
    //             +08 | case[ case_count ] | 按匹配值排序的 case 表, 每个 8 字节
};

// 单个 case 条目 (select 指令的跳转目标)
struct ScriptSelectCase {
    uint16_t match_value;   // +00 | word | 匹配值
    uint16_t jump_offset;   // +04 | word | 代码内跳转偏移
};

// 单个 select 指令的完整跳转数据
struct ScriptSelectData {
    uint16_t case_count;             // +00 | word | case 数量
    int16_t  default_jump_offset;    // +04 | word | 默认跳转偏移 (负值忽略)
    ScriptSelectCase cases[];        // +08 | 按 match_value 升序排列的 case 数组
};

// STR 子块 — 字符串表
struct ScriptStringChunk {
    RiffChunkHeader header; // magic="STR "

    // +00 | word   | 字符串数量
    // +04 | word[] | 字符串偏移表: 每个值 = 字符串数据相对于 data 的偏移
    // +XX | byte[] | 实际字符串数据
    uint16_t string_count;          // +00 | word | 字符串条目数
    uint16_t offset_table[];        // +04 | word[] | 字符串偏移表
    // 之后是连续存储的以 null 结尾的字符串
};

// 完整的 RIFF 脚本数据块
struct ScriptRiffData {
    RiffHeader          riff;    // "RIFF" "SCR "
    ScriptCodeChunk     code;    // "CODE" 子块
    ScriptJumpChunk     jump;    // "JUMP" 子块 (可选)
    ScriptStringChunk   str;     // "STR " 子块
};

// ============================================================================
// 2. 脚本虚拟机状态 (EventScripts.txt)
// ============================================================================
//
// 结构体布局 (0803F0D8 处由脚本数据填充)
// 解释器入口: 0803F2CC
// 函数调用处理 (指令 21): 0803FAC8

struct ScriptState {
    /* +000 */ uint16_t initialized;          // 非零表示已正确初始化?
    /* +004 */ uint16_t script_code_addr;     // 脚本代码数据地址; 构造时若非零则失败
    /* +008 */ uint16_t current_offset;        // 当前在脚本数据中的偏移?
    /* +00C */ uint16_t code_size;             // 脚本代码数据大小?
    /* +010 */ uint16_t string_count;          // 字符串偏移表条目数
    /* +014 */ uint16_t string_offset_table;   // 字符串偏移表地址
    /* +018 */ uint16_t string_data;           // 字符串数据地址
    /* +01C */ uint16_t jump_first_word;       // "JUMP" 段第一个字 (若有)
    /* +020 */ uint16_t jump_data;             // "JUMP" 段 +04 地址

    /* +024 */ uint16_t stack[100];            // 栈 (向上增长)
    /* +1B4 */ uint16_t stack_ptr;             // 第一个空闲栈槽索引?

    /* +1B8 */ uint16_t memory[100];           // 随机访问内存 (变量存储)

    /* +348 */ uint16_t unk_348;               // 用途不明; 用于指令操作数偏移修正
    /* +34C */ void*    vtable;                // 虚函数表
};

// vtable 布局
struct ScriptStateVtable {
    void*     unk_00;                          // +00
    void*     unk_04;                          // +04
    void      (*destructor)(void*);            // +08 | 析构函数
    void*     unk_0c;                          // +0C
    int32_t   (*user_command)(int id);         // +10 | int usercommand(int id);
};

// ScriptState 子类扩展 (推测为实际使用的派生类)
struct ScriptStateEx {
    // 基类 ScriptState (0x350 字节)
    /* +000 */ ScriptState base;

    /* +350 */ uint16_t game_data_ptr;         // GameData 指针 (见 GameData.txt)
    /* +354 */ uint16_t obj_ptr;               // 指向某个对象

    // 通过 obj_ptr 访问的嵌套对象:
    //     +04 | word | 指向另一个对象
    //         +A8 | word | GameObject 指针 (见 Entities.txt)
    //         +9C | word | 用途不明 (由 080122B0 设置, 同时设置 +E4) (文本框相关?)
    //         +AC | word | auto_ptr<TextBoxHandle>
    //         +B0 | word | TextBoxCharExpander 指针
    //         +B4 | word | auto_ptr<某对象>
    //             +04 | word | vtable
    //         +B8 | word | auto_ptr<某对象>
    //             +04 | word | vtable
    //         +BC | MusicPlayer
    //         +D0 | word | MusicPlayer 范围起始指针
    //         +D4 | word | MusicPlayer 范围结束指针
    //         +E0 | short | 用途不明 (由 08012D38/scr func 37 设置, 同时将 +9C 设为 15)
    //         +E4 | word | Entity/Actor 指针
    //         +E8 | byte  |
};

// ============================================================================
// 3. 脚本虚拟机指令 (EventScripts.txt)
// ============================================================================
//
// 每条指令以字节开头:
//   bit [0..6] — 指令 ID (7 bit)
//   bit [7]    — 若为 1, 紧跟的立即数操作数将加上 [+348] (而非直接使用)
//
// 指令编码:
//   [07bit 指令ID | 1bit 标志] [操作数...]

enum ScriptInstruction : uint8_t {
    SCR_INS_NOP      = 0x00,   // nop — 空操作
    SCR_INS_EQU      = 0x01,   // equ — mem[-2] = [-1]; 从栈读取偏移, 写入 memory
    SCR_INS_ADDEQU   = 0x02,   // addequ — mem[-2] += [-1]
    SCR_INS_SUBEQU   = 0x03,   // subequ — mem[-2] -= [-1]
    SCR_INS_MULEQU   = 0x04,   // mulequ — mem[-2] *= [-1]
    SCR_INS_DIVEQU   = 0x05,   // divequ — mem[-2] /= [-1]
    SCR_INS_MODEQU   = 0x06,   // modequ — mem[-2] %= [-1]
    SCR_INS_ADD      = 0x07,   // add — [-2] + [-1], 结果入栈
    SCR_INS_SUB      = 0x08,   // sub — [-2] - [-1], 结果入栈
    SCR_INS_MUL      = 0x09,   // mul — [-2] * [-1], 结果入栈
    SCR_INS_DIV      = 0x0A,   // div — [-2] / [-1], 结果入栈
    SCR_INS_MOD      = 0x0B,   // mod — [-2] % [-1], 结果入栈
    SCR_INS_AND      = 0x0C,   // and — [-2] && [-1], 结果入栈
    SCR_INS_OR       = 0x0D,   // or — [-2] || [-1], 结果入栈
    SCR_INS_INC      = 0x0E,   // inc — [-1] + 1
    SCR_INS_DEC      = 0x0F,   // dec — [-1] - 1
    SCR_INS_NEG      = 0x10,   // neg — -[-1]
    SCR_INS_NOT      = 0x11,   // not — ![-1]
    SCR_INS_CMP      = 0x12,   // cmp — [-2] <=> [-1] (结果 -1 / 0 / +1)
    SCR_INS_PUSHM    = 0x13,   // pushm imm — 压入 mem[imm]
    SCR_INS_POPM     = 0x14,   // popm imm — 弹出到 mem[imm]
    SCR_INS_DUP      = 0x15,   // dup — 复制栈顶
    SCR_INS_POP      = 0x16,   // pop — 直接弹出丢弃
    SCR_INS_PUSH     = 0x17,   // push imm — 压入立即数
    SCR_INS_B        = 0x18,   // b imm — 无条件跳转到偏移 imm
    SCR_INS_BLT      = 0x19,   // blt imm — 小于则跳转
    SCR_INS_BLE      = 0x1A,   // ble imm — 小于等于则跳转
    SCR_INS_BEQ      = 0x1B,   // beq imm — 等于则跳转
    SCR_INS_BNE      = 0x1C,   // bne imm — 不等于则跳转
    SCR_INS_BGE      = 0x1D,   // bge imm — 大于等于则跳转
    SCR_INS_BGT      = 0x1E,   // bgt imm — 大于则跳转
    SCR_INS_BI       = 0x1F,   // bi — 间接跳转 (从未使用)
    SCR_INS_END      = 0x20,   // end — 脚本结束
    SCR_INS_CALL     = 0x21,   // call imm — 函数调用
    SCR_INS_PUSH16   = 0x22,   // push16 imm — 压入 16 位立即数
    SCR_INS_PUSH8    = 0x23,   // push8 imm — 压入 8 位立即数
    SCR_INS_SELECT   = 0x24,   // select imm — switch/jump table
};

// ============================================================================
// 4. 场景系统 (Scenes.txt)
// ============================================================================

// 抽象场景基类
// 虚函数表地址: 0x080EDF0C
struct AbstractScene {
    /* +00 */ void* vtable;        // 虚函数表指针 (0x080EDF0C)
};

// 场景运行结果包装 (Scene / NotScene 互相转换的循环)
//
// 伪代码描述:
//   struct Scene    { virtual ~Scene();    virtual std::auto_ptr<NotScene> run(); };
//   struct NotScene { virtual ~NotScene(); virtual std::auto_ptr<Scene>    run(); };
//
// 场景循环:
//   scene->run() 返回 NotScene,
//   notScene->run() 返回 Scene,
//   如此交替直到其中一个返回空指针。

// 主循环函数 (签名推测)
// void doMainLoop(std::auto_ptr<Scene> scene);
//
// 伪代码:
//     while (scene.get()) {
//         std::auto_ptr<NotScene> notScene(scene->run());
//         scene.reset();
//         if (!notScene.get())
//             break;
//         scene = notScene->run();
//     }

// GameScene 结构体布局
// 虚函数表地址: 0x080EE138
// 此场景管理其他场景: 其 run() 方法调用 doMainLoop()
struct GameScene {
    /* +000 */ AbstractScene base;          // 基类 (vtable: 0x080EE138)

    /* +004 */ uint16_t game_data_ptr;      // GameData 指针

    /* +008 */ struct ScriptContext {
        /* +000 */ uint16_t unk_00;                          // 用途不明
        /* +024 */ uint8_t  unk_024[0x190];                  // 未知数据块
        /* +1B4 */ uint16_t unk_1B4;                          // 用途不明
        /* +34C */ void*    vtable;                           // vtable (0x080EFD50 -> 0x080EFD64)
        /* +350 */ uint16_t game_data_ptr;                     // GameData 指针
        /* +354 */ uint16_t unk_354;                          // 用途不明
        /* +358 */ uint16_t unk_358;                          // 用途不明
    } script_ctx;                            // 脚本上下文对象 (似乎是 ScriptStateEx 的变体)

    /* +364 */ uint8_t  unk_364;             // 用途不明
    /* +368 */ uint16_t unk_368;             // 用途不明 (默认值: 0xAB)
    /* +36C */ uint8_t  unk_36C;             // 用途不明 (可能与下一字段组成结构体)
    /* +370 */ uint16_t unk_370;             // 用途不明 (默认值: 0x1D)

    /* +374 */ uint16_t flags_374;           // 位域
        // bit [0..4]  — 5bit, 用途不明 (默认值: 6)
        // bit [5..10] — 6bit, 用途不明

    /* +378 */ uint16_t unk_378;             // 用途不明
    /* +38C */ uint16_t unk_38C;             // 用途不明
    /* +4D0 */ uint16_t unk_4D0;             // 用途不明

    // 对象数组: 6 个条目, 每个 0xC 字节
    /* +4DC */ struct SceneObject6 {
        /* +00 */ uint16_t flags;            // bit [0..1] — 2bit, 用途不明
        /* +02 */ struct EntityLocation {    // 实体位置 (默认值: loc=0x23A, x=0, y=0)
            uint16_t location_id;
            int16_t  x;
            int16_t  y;
        } entity_loc;
    } obj_array_6[6];                        // +4DC | 6 个对象, 每个 0xC 字节

    // 对象数组: 4 个条目, 每个 0xC 字节
    /* +524 */ struct SceneObject4 {
        /* +00 */ struct EntityLocation {    // 实体位置 (默认值: loc=0x23A, x=0, y=0)
            uint16_t location_id;
            int16_t  x;
            int16_t  y;
        } entity_loc;
        /* +06 */ uint8_t  unk_06;           // 用途不明
        /* +08 */ int16_t  unk_08;           // 用途不明
        /* +0A */ int16_t  unk_0A;           // 用途不明
    } obj_array_4[4];                        // +524 | 4 个对象, 每个 0xC 字节
};

// 检查 GameScene 总大小是否匹配笔记中的布局:
// 最后一个字段在 +524 + 4*0xC = +524 + 48 = +554, 约 1364 字节

// ============================================================================
// 5. 已知脚本函数 (EventScripts.txt)
// ============================================================================
//
// 脚本中调用的函数 (指令 21) 参数均为 32 位整数:
//   var    — 通用变量
//   unk    — 用途未知
//   string — 字符串偏移表索引 (字符串 ID)
//   addr   — 变量槽 ID
//
// 详细文档见 tools/functions.mary
//
// 脚本文件:
//   01 — 怀孕事件
//   04 — 获得马事件
//
// ============================================================================
// 6. 已知 RAM 地址 (EventScripts.txt)
// ============================================================================
//
// 0x081014BC — 事件脚本数据指针数组 (指向 RIFF "SCR " 块)
// 0x0803F0D8 — ScriptState 构造函数 (从 RIFF 数据填充)
// 0x0803F2CC — 核心脚本解释器
// 0x0803FAC8 — 函数调用处理 (指令 21)
// 0x080EDF0C — AbstractScene vtable
// 0x080EE138 — GameScene vtable
// 0x080EFD50 — ScriptContext vtable (-> 0x080EFD64)
// 0x080E06A4 — 未知重要函数
// 0x080122B0 — 设置 +9C 和 +E4 的函数
// 0x08012D38 — 脚本功能 37 调用处, 设置 +9C=15 和 +E0
//

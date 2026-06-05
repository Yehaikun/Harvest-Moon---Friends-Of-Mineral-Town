// 🗺️ 地图系统函数 - from asm/code_809E804.s
// 逐步将地图相关函数从汇编迁移到 C++

#include "prelude.h"

// Forward declarations for functions still in assembly
extern "C" void func_080A5760(void *);

// Original: 0x080A6640 - 地图对象初始化
// 调用主调度函数并清零状态字段
// asm/code_809E804.s 中的 stub 通过 b 指令跳转到此
extern "C" void func_080A6640_impl(void *obj)
{
    func_080A5760(obj);
    ((u8 *)obj)[0xB4] = 0;
    ((u8 *)obj)[0xB5] = 0;
    ((u8 *)obj)[0xB8] = 0;
    ((u8 *)obj)[0xB9] = 0;
}

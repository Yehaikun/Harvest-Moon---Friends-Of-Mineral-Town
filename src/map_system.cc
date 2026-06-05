// 🗺️ 地图系统函数 - from asm/code_809E804.s
// 逐步将地图相关函数从汇编迁移到 C++

#include "prelude.h"

// Forward declarations for functions still in assembly
extern "C" void func_080A5760(void *);

// Original: 0x080A6640 - 地图对象初始化
// 调用主调度函数并清零状态字段
// 当前实现仍在 asm/code_809E804.s
// 迁移到 C++ 时需要处理链接脚本，将 map_system.o 加入 fomt.lds

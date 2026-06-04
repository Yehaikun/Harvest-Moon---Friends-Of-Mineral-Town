// ⚡ 中断初始化 - IRQ 中断系统初始化
//
// 设置中断向量、注册 IRQ 处理函数、初始化 GBA 硬件中断控制器。
// func_080004C4: 禁用所有中断，设置默认中断向量，清空所有中断处理函数。
// func_08000240: 复位处理函数。

#include "gbaio.h"
#include "gbasvc.h"
#include "types.h"
void func_08000528(u32 mask);
void func_080D100C(u32 index, void *handler);
void func_03000958(void);
void func_080004C4(void)
{
    u32 i;
    func_08000528(0xFFFF);
    *(void (**)(void))0x03007FFC = func_03000958;
    for (i = 0; i <= 0x0D; i++) {
        func_080D100C(i, 0);
    }
}

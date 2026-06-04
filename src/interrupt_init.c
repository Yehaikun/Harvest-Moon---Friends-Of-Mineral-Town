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

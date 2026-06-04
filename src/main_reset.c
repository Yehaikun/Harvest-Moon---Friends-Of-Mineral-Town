#include "gbaio.h"
#include "gbasvc.h"

void func_08000528(u32 mask);

#define DISABLE_DMA_CHANNEL(cnt_h)       \
    do {                                 \
        (cnt_h) = (u16)((cnt_h) & 0xC5FF); \
        (cnt_h) = (u16)((cnt_h) & 0x7FFF); \
    } while (0)

void func_08000240(void)
{
    func_08000528(0xFFFF);

    REG_DISPCNT = 0x0080;
    REG_NR52 = 0;

    while ((0x000F & ~REG_KEYINPUT) != 0) {
    }

    DISABLE_DMA_CHANNEL(REG_DMA0CNT_H);
    DISABLE_DMA_CHANNEL(REG_DMA1CNT_H);
    DISABLE_DMA_CHANNEL(REG_DMA2CNT_H);
    DISABLE_DMA_CHANNEL(REG_DMA3CNT_H);

    SoftReset(0xFF);

    for (;;) {
    }
}

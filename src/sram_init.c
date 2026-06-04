// 💾 SRAM 初始化 - 存档验证与写入
//
// 反编译自 asm/sram_proxy_1.s。提供存档数据的校验、初始化、标志操作。

#include "prelude.h"

extern u16 gUnk_03000400;
extern u8 gUnk_080E862C[];
extern u32 func_080006E4(void *arg0, u8 *buf, u32 sram_ofs, u32 size);
extern u32 func_080006A4(void *arg0, u32 arg1, const u8 *data, u32 size);

u32 func_080002E0(void *proxy)
{
    u8 buf[0x20];
    u32 val32;
    u32 result = 0;

    if (func_080006E4(proxy, buf, 0, 0x20) != 0) return 0;
    if (gUnk_03000400 != 0) return 0;

    val32 = 0;
    if (func_080006E4(proxy, (u8 *)&val32, 0x20, 4) != 0) return 0;
    if (gUnk_03000400 != 0) return 0;

    val32 = 0;
    if (func_080006E4(proxy, (u8 *)&val32, 0x24, 4) != 0) return 0;
    if (gUnk_03000400 != 0) return 0;

    if (__builtin_memcmp(buf, gUnk_080E862C, 0x20) != 0) return 0;
    if ((val32 & 3) != val32) return 0;
    if (val32 > 1) return 0;

    return 1;
}

void func_08000358(void *proxy)
{
    u32 val = 0;
    func_080006A4(proxy, 0, gUnk_080E862C, 0x20);
    if (gUnk_03000400 != 0) return;
    func_080006A4(proxy, 0x20, (u8 *)&val, 4);
    if (gUnk_03000400 != 0) return;
    func_080006A4(proxy, 0x24, (u8 *)&val, 4);
}

u32 func_080003A0(void *proxy)
{
    u32 val = 0;
    if (func_080002E0(proxy) != 0)
    {
        if (func_080006E4(proxy, (u8 *)&val, 0x20, 4) == 0 && gUnk_03000400 == 0)
            return val;
    }
    return 0;
}

u32 func_080003DC(u32 index)
{
    return 0x3FEC * index + 0x28;
}

void func_080003E8(void *proxy, u32 bit)
{
    u32 val = 0;
    func_080006E4(proxy, (u8 *)&val, 0x20, 4);
    if (gUnk_03000400 != 0) return;
    val |= (1 << bit);
    func_080006A4(proxy, 0x20, (u8 *)&val, 4);
}

void func_08000470(void *proxy, u32 value)
{
    func_080006A4(proxy, 0x24, (u8 *)&value, 4);
}

u32 func_08000488(void *proxy)
{
    u32 val = 0;
    if (func_080002E0(proxy) != 0)
    {
        if (func_080006E4(proxy, (u8 *)&val, 0x24, 4) == 0 && gUnk_03000400 == 0)
            return val;
    }
    return 0;
}

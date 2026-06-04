// 💾 SRAM 代理 - 存档读写代理
//
// 管理 SRAM 初始化、写入和读取操作。
// 本文件反编译自 asm/sram_proxy_2.s。

#include "prelude.h"
#include "gbaio.h"

// IWRAM 全局变量声明
extern u16 gUnk_03000400;
extern u8  gUnk_03000402;

// 外部 SRAM 读写函数
extern const u8 *func_080D38D4(const u8 *src, u8 *dst, u32 size);
extern void func_080D379C(const u8 *src, u8 *dst, u32 size);

// 前向声明
void func_08000728(u32 ctx, u32 flag);

void *func_08000640(void *proxy)
{
    if (gUnk_03000402 == 0)
    {
        gUnk_03000402 = 1;
        gUnk_03000400 = 0;
    }
    return proxy;
}

u32 func_080006A4(u32 arg0, u32 arg1, const u8 *data, u32 size)
{
    u32 sram_addr = 0x0E000000 | arg1;

    gUnk_03000400 = 0;

    if (size == 0)
        return 1;

    if (func_080D38D4(data, (u8 *)sram_addr, size) == 0)
    {
        func_08000728(arg0, 0x100);
        return 0;
    }
    return 1;
}

u32 func_080006E4(u32 arg0, u8 *buf, u32 sram_ofs, u32 size)
{
    u32 sram_addr = 0x0E000000 | sram_ofs;

    gUnk_03000400 = 0;

    if (size == 0)
        return 0;

    func_080D379C((const u8 *)sram_addr, buf, size);
    return 1;
}

void func_08000728(u32 ctx, u32 flag)
{
    u16 f = flag & 0xFFFF;
    u16 cur = gUnk_03000400;

    switch (f)
    {
        case 0x001: cur |= 0x001; break;
        case 0x002: cur |= 0x002; break;
        case 0x004: cur |= 0x004; break;
        case 0x008: cur |= 0x008; break;
        case 0x010: cur |= 0x010; break;
        case 0x020: cur |= 0x020; break;
        case 0x040: cur |= 0x040; break;
        case 0x080: cur |= 0x080; break;
        case 0x100: cur |= 0x100; break;
        case 0x200: cur |= 0x200; break;
        default: break;
    }

    gUnk_03000400 = cur;
}

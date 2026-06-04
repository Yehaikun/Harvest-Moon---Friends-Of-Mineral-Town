// 💾 SRAM 库 - SRAM 读写/校验（代码复制到栈上执行）
//
// SRAM 只能从 RAM 执行，所以 SRAM 读写函数会把关键代码段
// 复制到栈上再执行。反编译自 asm/code_lib_sram.s。

#include "prelude.h"
#include "gbaio.h"

/* func_080D3778: 逐字节复制（会被复制到栈上执行） */
NAKED void func_080D3778(const u8 *src, u8 *dst, u32 size)
{
    asm_unified("\tpush {r4, lr}\n"
        "\tadds r4, r0, #0\n"
        "\tsubs r3, r2, #1\n"
        "\tcmp r2, #0\n"
        "\tbeq .L080D3794\n"
        "\tmovs r2, #1\n"
        "\trsbs r2, r2, #0\n"
        ".L080D3786:\n"
        "\tldrb r0, [r4]\n"
        "\tstrb r0, [r1]\n"
        "\tadds r4, #1\n"
        "\tadds r1, #1\n"
        "\tsubs r3, #1\n"
        "\tcmp r3, r2\n"
        "\tbne .L080D3786\n"
        ".L080D3794:\n"
        "\tpop {r4}\n"
        "\tpop {r0}\n"
        "\tbx r0");
}

/* func_080D379C: 设置等待状态，将 func_080D3778 复制到栈执行读 SRAM */
NAKED void func_080D379C(const u8 *src, u8 *dst, u32 size)
{
    asm_unified("\tpush {r4, r5, r6, lr}\n"
        "\tsub sp, #0x80\n"
        "\tadds r4, r0, #0\n"
        "\tadds r5, r1, #0\n"
        "\tadds r6, r2, #0\n"
        "\tldr r2, =0x04000204\n"
        "\tldrh r0, [r2]\n"
        "\tldr r1, =0x0000FFFC\n"
        "\tands r0, r1\n"
        "\tmovs r1, #3\n"
        "\torrs r0, r1\n"
        "\tstrh r0, [r2]\n"
        "\tldr r3, =func_080D3778\n"
        "\tmovs r0, #1\n"
        "\tbics r3, r0\n"
        "\tmov r2, sp\n"
        "\tldr r0, =func_080D379C\n"
        "\tldr r1, =func_080D3778\n"
        "\tsubs r0, r0, r1\n"
        "\tlsls r0, r0, #0xf\n"
        ".L080D37E4:\n"
        "\tlsrs r1, r0, #0x10\n"
        "\tcmp r1, #0\n"
        "\tbne .L080D37D8\n"
        "\tb .L080D3808\n"
        ".L080D37D8:\n"
        "\tldrh r0, [r3]\n"
        "\tstrh r0, [r2]\n"
        "\tadds r3, #2\n"
        "\tadds r2, #2\n"
        "\tsubs r0, r1, #1\n"
        "\tlsls r0, r0, #0x10\n"
        "\tb .L080D37E4\n"
        ".L080D3808:\n"
        "\tmov r3, sp\n"
        "\tadds r3, #1\n"
        "\tadds r0, r4, #0\n"
        "\tadds r1, r5, #0\n"
        "\tadds r2, r6, #0\n"
        "\tbl _call_via_r3\n"
        "\tadd sp, #0x80\n"
        "\tpop {r4, r5, r6}\n"
        "\tpop {r0}\n"
        "\tbx r0\n"
        "\t.align 2, 0");
}

/* func_080D3800: 设置等待状态后逐字节写入 SRAM */
void func_080D3800(const u8 *src, u8 *dst, u32 size)
{
    REG_WAITCNT = (REG_WAITCNT & 0xFFFC) | 3;
    while (size > 0)
    {
        *dst++ = *src++;
        size--;
    }
}

/* func_080D3840: 逐字节比较（会被复制到栈上执行） */
NAKED const u8 *func_080D3840(const u8 *buf1, const u8 *buf2, u32 size)
{
    asm_unified("\tpush {r4, r5, lr}\n"
        "\tadds r5, r0, #0\n"
        "\tadds r3, r1, #0\n"
        "\tsubs r4, r2, #1\n"
        "\tcmp r2, #0\n"
        "\tbeq .L080D3866\n"
        "\tmovs r2, #1\n"
        "\trsbs r2, r2, #0\n"
        ".L080D3850:\n"
        "\tldrb r1, [r3]\n"
        "\tldrb r0, [r5]\n"
        "\tadds r5, #1\n"
        "\tadds r3, #1\n"
        "\tcmp r1, r0\n"
        "\tbeq .L080D3860\n"
        "\tsubs r0, r3, #1\n"
        "\tb .L080D3868\n"
        ".L080D3860:\n"
        "\tsubs r4, #1\n"
        "\tcmp r4, r2\n"
        "\tbne .L080D3850\n"
        ".L080D3866:\n"
        "\tmovs r0, #0\n"
        ".L080D3868:\n"
        "\tpop {r4, r5}\n"
        "\tpop {r1}\n"
        "\tbx r1");
}

/* func_080D3870: 设置等待状态，将 func_080D3840 复制到栈执行校验 */
NAKED const u8 *func_080D3870(const u8 *buf1, const u8 *buf2, u32 size)
{
    asm_unified("\tpush {r4, r5, r6, lr}\n"
        "\tsub sp, #0xc0\n"
        "\tadds r4, r0, #0\n"
        "\tadds r5, r1, #0\n"
        "\tadds r6, r2, #0\n"
        "\tldr r2, =0x04000204\n"
        "\tldrh r0, [r2]\n"
        "\tldr r1, =0x0000FFFC\n"
        "\tands r0, r1\n"
        "\tmovs r1, #3\n"
        "\torrs r0, r1\n"
        "\tstrh r0, [r2]\n"
        "\tldr r3, =func_080D3840\n"
        "\tmovs r0, #1\n"
        "\tbics r3, r0\n"
        "\tmov r2, sp\n"
        "\tldr r0, =func_080D3870\n"
        "\tldr r1, =func_080D3840\n"
        "\tsubs r0, r0, r1\n"
        "\tlsls r0, r0, #0xf\n"
        ".L080D38B8:\n"
        "\tlsrs r1, r0, #0x10\n"
        "\tcmp r1, #0\n"
        "\tbne .L080D38AC\n"
        "\tb .L080D38DC\n"
        ".L080D38AC:\n"
        "\tldrh r0, [r3]\n"
        "\tstrh r0, [r2]\n"
        "\tadds r3, #2\n"
        "\tadds r2, #2\n"
        "\tsubs r0, r1, #1\n"
        "\tlsls r0, r0, #0x10\n"
        "\tb .L080D38B8\n"
        ".L080D38DC:\n"
        "\tmov r3, sp\n"
        "\tadds r3, #1\n"
        "\tadds r0, r4, #0\n"
        "\tadds r1, r5, #0\n"
        "\tadds r2, r6, #0\n"
        "\tbl _call_via_r3\n"
        "\tadd sp, #0xc0\n"
        "\tpop {r4, r5, r6}\n"
        "\tpop {r1}\n"
        "\tbx r1\n"
        "\t.align 2, 0");
}

/* func_080D38D4: SRAM 写入 + 校验重试（最多 3 次） */
const u8 *func_080D38D4(const u8 *src, u8 *dst, u32 size)
{
    u32 retry;
    const u8 *result;

    for (retry = 0; retry <= 2; retry++)
    {
        func_080D3800(src, dst, size);
        result = func_080D3870(src, dst, size);
        if (result == 0)
            break;
    }
    return result;
}

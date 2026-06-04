// 📞 GBA BIOS 系统调用包装
// 反编译自 asm/code_lib_syscall.s
#include "prelude.h"

NAKED void ArcTan2(void)
{
    asm_unified("\tsvc #0xa\n\tbx lr");
}

NAKED void CpuFastSet(void)
{
    asm_unified("\tsvc #0xc\n\tbx lr");
}

NAKED void CpuSet(void)
{
    asm_unified("\tsvc #0xb\n\tbx lr");
}

NAKED void IntrWait(void)
{
    asm_unified("\tmovs r2, #0\n\tsvc #4\n\tbx lr");
}

NAKED void SoftReset(void)
{
    asm_unified("\tldr r3, .L080D376C\n"
                "\tmovs r2, #0\n"
                "\tstrb r2, [r3]\n"
                "\tldr r1, .L080D3770\n"
                "\tmov sp, r1\n"
                "\tsvc #1\n"
                "\tsvc #0\n"
                "\tmovs r0, r0\n"
                ".L080D376C:\n"
                "\t.4byte 0x04000208\n"
                ".L080D3770:\n"
                "\t.4byte 0x03007F00\n");
}

NAKED void Sqrt(void)
{
    asm_unified("\tsvc #8\n\tbx lr");
}

// 📦 更多物品 - rucksack_item 续
//
// 管理一个带有计数和位置信息的缓冲区结构。
// 反编译自 asm/more_items.s。
//
// 结构体布局:
//   +0x00: u32 count
//   +0x04: u8 data[30]
//   +0x24: Location (6 bytes, PACKED ALIGN(2))

#include "prelude.h"

static const u32 MAP_NONE = 0x234;


/* func_0800FF8C: 初始化结构体，清空计数并设置位置为 MAP_NONE */
EC void func_0800FF8C(void *self)
{
    u16 *loc = (u16 *)((u8 *)self + 0x24);

    *(u32 *)self = 0;
    loc[0] = (loc[0] & 0xFC00) | 0x234;
    ((u8 *)loc)[2] &= 3;
    loc[1] &= 0xFC00;
    ((u8 *)loc)[3] &= 3;
    loc[2] &= 0xFC00;
}

/* func_0800FFD0: 获取当前计数 */
EC u32 func_0800FFD0(void *self)
{
    return *(u32 *)self;
}

/* func_0800FFD4: 获取数据缓冲区指针 */
EC void *func_0800FFD4(void *self)
{
    return (u8 *)self + 4;
}

/* func_0800FFD8: 获取数据结束指针 (self + 4 + count) */
EC void *func_0800FFD8(void *self)
{
    return (u8 *)self + 4 + *(u32 *)self;
}

/* func_0800FFE0: 从 self+0x24 复制 6 字节到 dest */
EC void func_0800FFE0(void *self, void *dest)
{
    for (u32 i = 0; i < 6; i++)
        ((u8 *)dest)[i] = ((u8 *)self + 0x24)[i];
}

/* func_0800FFF4: 追加一个字节到缓冲区（不超过 30 个） */
EC void func_0800FFF4(void *self, u8 value)
{
    u32 count = *(u32 *)self;

    if (count <= 29)
    {
        u8 *pos = (u8 *)self + 4 + count;
        if (pos != 0)
            *pos = value;
        *(u32 *)self = count + 1;
    }
}

/* func_08010014: 从 src 复制 6 字节到 self+0x24 */
EC void func_08010014(void *self, void *src)
{
    for (u32 i = 0; i < 6; i++)
        ((u8 *)self + 0x24)[i] = ((u8 *)src)[i];
}

/* func_08010024: 清理——遍历所有数据项并重置计数为 0 */
EC void func_08010024(void *self)
{
    u8 *data_end = (u8 *)self + 4 + *(u32 *)self;
    u8 *data = (u8 *)self + 4;
    u32 old_count = *(u32 *)self;

    *(u32 *)self = old_count - (u32)(data_end - data);
}

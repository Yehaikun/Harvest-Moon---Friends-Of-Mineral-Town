// 💾 SRAM 代理 - 存档读写代理
//
// 负责在 SRAM 和内存之间传输存档数据。
// 将 data_080F0348 区域的预设表数据写入 SRAM 首次存档。
// func_08000640: SRAM 代理初始化

#include "types.h"
void func_0800063C(void)
{
    /* SRAM 代理初始化前的空钩子，原函数只立即返回。 */
}

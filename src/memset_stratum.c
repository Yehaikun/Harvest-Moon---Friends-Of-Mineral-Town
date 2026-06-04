// 📦 memset — 内存填充
#include "prelude.h"

void *memset(void *dest, int c, size_t n)
{
    unsigned char *d = (unsigned char *)dest;

    while (n--)
        *d++ = (unsigned char)c;

    return dest;
}

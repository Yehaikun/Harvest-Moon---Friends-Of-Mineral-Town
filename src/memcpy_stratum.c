// 📦 memcpy — 内存复制（非重叠）
#include "prelude.h"

void *memcpy(void *dest, const void *src, size_t n)
{
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    while (n--)
        *d++ = *s++;

    return dest;
}

// 📚 C 标准库函数 - memcmp/memcpy/memmove/memset/strcat/strcpy/strlen
//
// 简单的字节级实现。memmove 使用 u32 比较避免指针未定义行为。

#include "prelude.h"

int memcmp(const void *s1, const void *s2, size_t n)
{
    const u8 *p1 = (const u8 *)s1;
    const u8 *p2 = (const u8 *)s2;
    size_t i;
    for (i = 0; i < n; i++) {
        if (p1[i] != p2[i])
            return (int)p1[i] - (int)p2[i];
    }
    return 0;
}

void *memcpy(void *dest, const void *src, size_t n)
{
    u8 *d = (u8 *)dest;
    const u8 *s = (const u8 *)src;
    size_t i;
    for (i = 0; i < n; i++)
        d[i] = s[i];
    return dest;
}

void *memmove(void *dest, const void *src, size_t n)
{
    u8 *d = (u8 *)dest;
    const u8 *s = (const u8 *)src;
    size_t i;

    if ((u32)d < (u32)s) {
        for (i = 0; i < n; i++)
            d[i] = s[i];
    } else {
        for (i = n; i > 0; i--)
            d[i - 1] = s[i - 1];
    }
    return dest;
}

void *memset(void *s, int c, size_t n)
{
    u8 *p = (u8 *)s;
    size_t i;
    for (i = 0; i < n; i++)
        p[i] = (u8)c;
    return s;
}

char *strcat(char *dest, const char *src)
{
    char *d = dest;
    while (*d) d++;
    while ((*d++ = *src++));
    return dest;
}

char *strcpy(char *dest, const char *src)
{
    char *d = dest;
    while ((*d++ = *src++));
    return dest;
}

size_t strlen(const char *s)
{
    const char *p = s;
    while (*p) p++;
    return (size_t)(p - s);
}

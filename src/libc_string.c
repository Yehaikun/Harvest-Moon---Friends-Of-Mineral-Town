#include "prelude.h"
int memcmp(const void *s1, const void *s2, size_t n)
{
    const unsigned char *p1 = (const unsigned char *)s1;
    const unsigned char *p2 = (const unsigned char *)s2;
    size_t i;
    for (i = 0; i < n; i++) {
        if (p1[i] != p2[i])
            return (int)p1[i] - (int)p2[i];
    }
    return 0;
}
void *memcpy(void *dest, const void *src, size_t n)
{
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    size_t i;
    for (i = 0; i < n; i++) d[i] = s[i];
    return dest;
}
void *memmove(void *dest, const void *src, size_t n)
{
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    size_t i;
    if ((u32)d < (u32)s) {
        for (i = 0; i < n; i++) d[i] = s[i];
    } else {
        for (i = n; i > 0; i--) d[i-1] = s[i-1];
    }
    return dest;
}
void *memset(void *s, int c, size_t n)
{
    unsigned char *p = (unsigned char *)s;
    size_t i;
    for (i = 0; i < n; i++) p[i] = (unsigned char)c;
    return s;
}
char *strcat(char *dest, const char *src)
{
    size_t i = 0, j = 0;
    while (dest[i]) i++;
    while ((dest[i++] = src[j++]));
    return dest;
}
char *strcpy(char *dest, const char *src)
{
    size_t i = 0;
    while ((dest[i] = src[i])) i++;
    return dest;
}
size_t strlen(const char *s)
{
    const char *p = s;
    while (*p) p++;
    return (size_t)(p - s);
}

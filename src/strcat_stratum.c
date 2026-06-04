// 📝 strcat — C 标准库字符串拼接函数
#include "prelude.h"

char *strcpy(char *dest, const char *src);

char *strcat(char *dest, const char *src)
{
    char *p = dest;

    while (*p != '\0')
        p++;

    strcpy(p, src);
    return dest;
}

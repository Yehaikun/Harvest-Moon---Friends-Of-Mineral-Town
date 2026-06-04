// 📝 strcpy — C 标准库字符串复制函数
#include "prelude.h"

char *strcpy(char *dest, const char *src)
{
    char *p = dest;

    while ((*p++ = *src++) != '\0')
        ;

    return dest;
}

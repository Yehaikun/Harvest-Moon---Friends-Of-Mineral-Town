// 📏 strlen — C 标准库字符串长度函数
#include "prelude.h"

size_t strlen(const char *s)
{
    const char *p = s;
    while (*p != '\0')
        p++;
    return (size_t)(p - s);
}

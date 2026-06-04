// ⚠️ 纯虚函数陷阱 - 纯虚函数被调用时的处理
//
// 如果由于对象状态异常导致纯虚函数被调用（正常情况不应发生），
// 此函数会进入死循环，使问题在调试器中可见。

#include "types.h"
#include "prelude.h"
void __pure_virtual(void) {}

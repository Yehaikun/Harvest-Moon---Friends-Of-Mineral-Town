#include "prelude.h"
#include "entity.hh"

extern "C" {

void func_080168D4(void* context, u32 type) {
    if (type > 4) return;
    if (!context) return;
    
    void* sub = *(void**)((char*)context + 4);
    if (!sub) return;
    
    if (type == 0 || type == 4) {
        void* es = *(void**)((char*)sub + 0xA8);
        if (!es) return;
        
        // 只检查不操作
        return;
    }
    // 其他 case 先不做任何事
}

} // extern "C"

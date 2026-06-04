// 🎬 游戏场景 - func_0801004C
//
// 创建新场景对象并管理 SmartPtr 生命周期。
// 反编译自 asm/game_scene.s（分拆第一部分）。
// func_08010158 在 game_scene_func2.c，中间通过 LDS padding 对齐。

#include "prelude.h"

extern "C" void AScriptEngine_base_dtor(void *self, u32 flag)
    __asm__("_._13AScriptEngine");
extern "C" void AScene_base_dtor(void *self, void *arg)
    __asm__("_._6AScene");

struct GameScene
{
    /* +00 */ void *vtable;
    /* +04 */ void *field_04;
    /* +08 */ u8 script_engine[0x35C];
    /* +364 */ u8 unk_364;
    /* +365 */ u8 pad_365[0x13];
    /* +378 */ u32 field_378;
};

extern "C" {
    void func_08008980(void *ctx);
    void func_08008A68(void *ctx, u32 flag);
    void *__builtin_new(u32 size);
    void *func_08011DC4(void *wrapper, void *scene, void *stack);
    void func_0800082C(void *smartptr);
    void func_080D7E64(void *ptr, u32 flag);
    void func_080D4480(void *ptr, u32 flag);
    void func_080007EC(void *self, void *arg);
}
extern u32 vtable_unk_080E5BF8[];
extern void *gUnk_0300040C;

typedef void (*DtorFn)(void *, u32);

void func_0801004C(void *out, struct GameScene *scene)
{
    u32 ctx[7];
    u32 smartptr[2];

    func_08008980(ctx);

    ctx[1] = 0;
    smartptr[0] = (scene->unk_364 != 0) ? 0 : 1;

    void *scene_obj = __builtin_new(8);
    void *result = func_08011DC4(scene_obj, (void *)scene->field_04, (void *)smartptr);

    void *old = (void *)ctx[1];
    if (result != old && old != 0)
    {
        DtorFn *vtable = *(DtorFn **)old;
        vtable[2](old, 3);
    }
    ctx[1] = (u32)result;
    ctx[1] = 0;
    smartptr[0] = (u32)result;

    func_0800082C(&smartptr[0]);

    smartptr[0] = 0;
    ctx[5] = (u32)&smartptr[0];
    ((u32 *)ctx)[6] = 0;
    smartptr[0] = 0;
    *(void **)out = 0;

    if (smartptr[0] != 0)
    {
        DtorFn *vtable = *(DtorFn **)((void *)smartptr[0]);
        vtable[2]((void *)smartptr[0], 3);
    }
    if (ctx[1] != 0)
    {
        DtorFn *vtable = *(DtorFn **)((void *)ctx[1]);
        vtable[2]((void *)ctx[1], 3);
    }

    func_08008A68(ctx, 2);
}

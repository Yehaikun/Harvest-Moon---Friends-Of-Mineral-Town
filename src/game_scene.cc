// 🎬 游戏场景 - 场景初始化与销毁
//
// 管理 GameScene 对象的生命周期：创建、运行场景主循环、销毁。
// 反编译自 asm/game_scene.s。

#include "prelude.h"

// 使用 __asm__ 将 C++ 符号映射到汇编中的加点符号
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

    smartptr[0] = 0;
    smartptr[1] = (scene->unk_364 == 1) ? 0 : 1;

    void *scene_obj = __builtin_new(8);
    void *result = func_08011DC4(scene_obj, (void *)scene->field_04, (void *)smartptr);

    // SmartPtr transfer
    void *old = (void *)ctx[1];
    if (result != old && old != 0)
    {
        DtorFn *vtable = *(DtorFn **)old;
        vtable[2](old, 3);
    }
    ctx[1] = (u32)result;

    void *temp = (void *)ctx[1];
    ctx[1] = 0;
    smartptr[1] = (u32)temp;

    func_0800082C(&smartptr[1]);

    // Cleanup
    smartptr[1] = 0;
    ctx[5] = (u32)&smartptr[1];
    ((u32 *)ctx)[6] = 0;
    smartptr[0] = 0;

    if (temp != 0)
    {
        DtorFn *vtable = *(DtorFn **)temp;
        vtable[2](temp, 3);
    }
    if (ctx[1] != 0)
    {
        DtorFn *vtable = *(DtorFn **)((void *)ctx[1]);
        vtable[2]((void *)ctx[1], 3);
    }

    func_08008A68(ctx, 2);
    *(void **)out = 0;
}

void func_08010158(struct GameScene *self, void *arg)
{
    self->vtable = (void *)vtable_unk_080E5BF8;
    gUnk_0300040C = 0;

    func_080D7E64(&self->field_378, 2);
    AScriptEngine_base_dtor(&self->script_engine[0], 2);

    if (self->field_04 != 0)
        func_080D4480(self->field_04, 3);

    func_080007EC(self, arg);
}

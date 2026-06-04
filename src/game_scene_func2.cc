// 🎬 游戏场景 - func_08010158（场景初始化/销毁）
//
// 反编译自 asm/game_scene.s。func_0801004C 在 game_scene_func1.cc，
// 两个文件通过 fomt.lds 的 padding 保持 func_08010158 在原地址。

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
    void func_080D7E64(void *ptr, u32 flag);
    void func_080D4480(void *ptr, u32 flag);
    void func_080007EC(void *self, void *arg);
}
extern u32 vtable_unk_080E5BF8[];
extern void *gUnk_0300040C;

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

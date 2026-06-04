// 🎬 场景系统 - 场景生命周期管理（SceneMain 主循环）
//
// 场景游戏的核心机制：当前场景（AScene）通过 Run() 返回下一个要切换的场景，
// SceneMain 循环不断执行 Run() → 销毁旧场景 → 切换到新场景，直到返回 nullptr。

#include "scene.hh"

/**
 * AScene 析构函数
 * 所有场景类的基类析构函数。具体的场景清理逻辑由子类实现。
 */
AScene::~AScene() {}

/**
 * AUnk_0800080C 析构函数
 * 未知中间对象类的析构函数。该对象在场景切换时由 AScene::Run() 返回，
 * 用于携带切换信息并调用 vfunc_0C() 生成下一个场景。
 */
AUnk_0800080C::~AUnk_0800080C() {}

/**
 * func_080007EC — AScene 析构函数的别名
 * 供汇编代码通过此符号调用 ~AScene()。
 */
EC void func_080007EC() ALIAS(_._6AScene);

/**
 * func_0800080C — AUnk_0800080C 析构函数的别名
 * 供汇编代码通过此符号调用 ~AUnk_0800080C()。
 */
EC void func_0800080C() ALIAS(_._13AUnk_0800080C);

// SceneMain 当前由汇编提供（asm/scene.s），
// 注释掉的行是未来反编译为 C++ 的预留入口。
// void func_0800082C() ALIAS(_._13AUnk_0800080C);

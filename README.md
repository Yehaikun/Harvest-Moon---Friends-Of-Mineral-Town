# 牧场物语：矿石镇的伙伴们 — 反编译项目

基于 2003 年 GBA 游戏 **牧场物语：矿石镇的伙伴们**（美版）的反编译工程。

可编译出以下 ROM：

- **`fomt.gba`** `sha1: a2fc3574f0a65a4fcf7682fb274b9d7eebdef963`

## 当前进度

| 组件 | 进度 | 说明 |
|------|------|------|
| 核心引擎 | ~40% | 已反编译为 C++（`src/`） |
| 事件脚本 | 1328/1328 | 已全部反编译，可用 mary 工具编辑 |
| 场景切换 | ✅ 已反编译 | `func_080168D4` → `src/scene_transition.cc` |
| 地图数据 | ✅ 已分析 | 50 张地图的表结构已定位 |
| NPC 行为 | ❌ 汇编中 | `asm/code_entities.s`（31,812 行） |
| 脚本引擎 | ❌ 汇编中 | `asm/code_0803EE94.s`（179,483 行） |

## 构建方法

```bash
make
```

> 注意：因已修改源码，`make compare` 的 SHA1 校验会失败，但 `fomt.gba` 会正常生成。

详见 [INSTALL.md](./INSTALL.md)。

## 工具

- **mary** — 事件脚本编译/反编译工具，位于 `/tmp/stanhash_mary/target/release/mary`
- **agbcc** — GBA 专用 C++ 编译器，位于 `tools/agbcc/bin/`

## 致谢

本项目基于 [StanHash/fomt](https://github.com/StanHash/fomt) 的原始反编译工作。

## 许可证

仅供学习研究使用。游戏版权归原版权方所有。

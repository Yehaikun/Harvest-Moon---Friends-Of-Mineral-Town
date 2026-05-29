# 牧场物语：矿石镇的伙伴们 - 反编译项目

基于 [StanHash/fomt](https://github.com/StanHash/fomt) 的 GBA 游戏反编译项目。

## 当前状态

| 组件 | 进度 |
|------|------|
| 核心引擎 | 约 40% 已反编译为 C++ |
| 事件脚本 | 1328 个脚本已全部反编译（可使用 mary 工具编辑） |
| 地图数据表 | 50 张地图已定位并分析 |
| 场景切换 | `func_080168D4` 已反编译为 C++（`src/scene_transition.cc`） |
| 汇编待反编译 | 约 60% 仍在汇编中（主要分布在 `asm/` 目录） |

## 构建

```bash
# 要求：
# - arm-none-eabi 工具链
# - agbcc（C++ 版，已包含在 tools/ 目录）

# 编译
make

# 注意：由于已修改源码，make compare 会失败（SHA1 不同），
# 但 fomt.gba 会正常生成
```

## 目录结构

```
src/              - 已反编译的 C++ 源码
asm/              - 未反编译的汇编代码
include/          - 头文件
scripts/          - 反编译的游戏事件脚本（mary 格式）
mary_scripts/     - 自定义 mary 脚本
tools/            - agbcc 编译器及库
data/             - 游戏数据文件
```

## 场景切换系统

`func_080168D4` 实现了 5 种场景过渡：

| 类型 | 目标 | 说明 |
|------|------|------|
| 0 | 自宅 (map 2) 位置 (752,132) | 事件结束后回家 |
| 1 | 畜棚 (map 0x25) | 进入畜棚 |
| 2 | 畜棚 (map 0x25) | 同 1 |
| 3 | 鸡屋 (map 0x11) | 进入鸡屋 |
| 4 | 自宅 (map 2) 位置 (382,82) | 另一种回家 |

## 工具

- **mary** — 事件脚本编译/反编译工具（`/tmp/stanhash_mary/target/release/mary`）
- **agbcc** — GBA C++ 编译器（`tools/agbcc/bin/`）

## 许可证

本项目为 GBA 游戏《牧场物语：矿石镇的伙伴们》的逆向工程，仅供学习研究使用。

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

## 路线图

目标不是只把 ROM “翻成代码”，而是最终做到：

- 全量反编译核心逻辑
- 能修改对话、地图、NPC、事件、物品和数值
- 能把改动重新构建成可运行 ROM
- 尽量把零散数据整理成可维护的编辑工具

当前已经恢复 `mary` 工具链，后续路线优先从“能稳定改内容”开始，再逐步深入引擎反编译。

| 阶段 | 目标 | 交付物 | 验证标准 |
|------|------|--------|----------|
| 第 0 阶段 | 稳定基础构建 | `make fomt.gba`、`make check-mary` 可重复运行 | ✅ 全量 clean build 通过，ROM 已确认不白屏 |
| 第 1 阶段 | 脚本补丁可复现 | `tools/patch_script.py` 或 Makefile 规则，完成 `.mary -> binary -> derived ROM` | 不手动改 `baserom.gba`，修改 `script_167.mary` 后重新构建仍能进鸡屋传送到海边 |
| 第 2 阶段 | 脚本索引与触发链路 | 脚本 ID、ROM 偏移、slot 大小、`Proc016` 传送点、入口脚本索引 | 能快速回答“哪个入口/地图/NPC 触发哪个脚本” |
| 第 3 阶段 | 对白/事件修改规范 | 对话文本、事件脚本、分支条件、RAM 验证地址、脚本 ID 的对应关系文档化 | 能定位并修改指定 NPC 的指定对白，并能解释旧存档为什么触发或不触发 |
| 第 4 阶段 | 数据补丁器与校验工具 | 文本长度检查、指针/偏移检查、脚本编译输出大小检查、mary 坏脚本黑名单 | 修改失败时能在构建阶段报错，而不是进游戏白屏 |
| 第 5 阶段 | 地图与场景数据链路 | 地图 ID、出生点、传送点、地图块/碰撞线索、DataCrystal/论坛资料交叉表 | 能安全修改一个入口/出生点，并避免传到墙里或黑屏 |
| 第 6 阶段 | 文本与内容数据工具评估 | HMMT、DataCrystal ROM map、khadim 资料、CodeBreaker 地址的可用性测试文档 | 能确定哪些文本/物品/价格/NPC 数据适合工具改，哪些必须反编译 |
| 第 7 阶段 | 继续核心引擎反编译 | UI、场景、实体、脚本解释器关键函数逐步转为 C/C++ | 每次迁移后地址不漂移，ROM 不白屏 |
| 第 8 阶段 | 自定义内容支持 | 新对话、新事件、新 NPC/地图的可扩展数据结构 | 可以用文档化流程增加一段新内容 |

### 说明

- 这不是单纯“把汇编全删掉”，而是把关键逻辑逐步抽成可维护的 C/C++ 和数据表。
- 当前优先级是“内容改动可复现”高于“多反编译几个函数”；脚本和数据链路打通后，改对白、事件、NPC 才不会依赖临时 hex patch。
- 目前 `.mary` 文件还没有完全进入 ROM 构建链。鸡屋传送到海边已经验证有效，但它依赖本地 ROM 数据被补丁过；下一步必须把这个补丁过程写成受版本控制的工具。
- DataCrystal RAM map 已确认能帮助验证时间、天气、金钱、好感度等运行时条件。以后改 NPC 对话前，要先确认旧存档的 RAM 条件是否真的会进入目标分支。
- DataCrystal ROM map 主要给 TV 节目文本偏移。HMMT、khadim 论坛、CodeBreaker 表和 Boktai tilemap 资料目前先作为线索，必须经过本项目实测再纳入正式流程。
- 地图和人物这类内容，最终会尽量变成数据驱动，而不是继续硬编码在汇编里。
- 如果后续要做真正的编辑器，优先顺序通常是“数据表可编辑”先于“图形化编辑器”。

### 近期安排

1. 编写脚本 slot 检查器：输入脚本 ID，输出指针、ROM offset、下一个脚本 offset、可用字节数。
2. 编写受版本控制的脚本补丁器：把指定 `.mary` 编译为二进制，检查长度后插入派生 ROM，禁止直接手动改 `baserom.gba`。
3. 把 `script_167.mary` 的鸡屋传送改动作为第一个自动化回归用例：重新 clean build 后仍能反编译验证 `Proc016(1, 24, 280)`。
4. 扫描全部 `.mary`，生成 `Proc016` / `SetEntityPosition` 传送索引表，优先服务地图和入口改造。
5. 建立 RAM 观察表：日期、时间、天气、金钱、主要候选对象好感度，用于解释对话分支为什么触发或不触发。
6. 评估 HMMT Dumper/Inserter：先做“无修改提取再插入”的 round-trip 测试，确认是否会破坏文本格式。
7. 在每次内容改动或反编译迁移后执行 `make check-mary`、`make -j2 fomt.gba`，并用模拟器确认不白屏。

更多外部资料整理见 [docs/references/fomt_reverse_engineering_sources.md](./docs/references/fomt_reverse_engineering_sources.md)。

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

- **mary** — 事件脚本编译/反编译工具，源码仓库为 [StanHash/mary](https://github.com/StanHash/mary)。建议克隆并编译到稳定目录：

```bash
cd ..
git clone https://github.com/StanHash/mary.git stanhash_mary
cd stanhash_mary
cargo build --release
```

本项目默认使用：

```bash
../stanhash_mary/target/release/mary
```

可用下面命令验证 mary 工具链：

```bash
make check-mary
```

项目内 `.mary` 脚本必须引用仓库内的 `mary_scripts/lib_fomt.txt`，不要依赖 `/tmp/stanhash_mary` 这类临时路径。

当前脚本补丁流程已经接入 `make fomt.gba`。构建时 Makefile 会把 `SCRIPT_PATCHES`
列出的 `.mary` 脚本编译为 bytecode，检查原脚本 slot 大小后补丁到生成的 ROM。

常用命令：

```bash
# 查看脚本在 ROM 中的 slot
tools/script_slot.py fomt.gba --script-id 167

# 构建并自动应用 SCRIPT_PATCHES
make -j2 fomt.gba

# 验证当前脚本补丁是否真的写入 ROM
make check-script-patches

# 生成全脚本传送索引
make warp-index

# 生成 mary 脚本交叉引用候选
make script-xref-index

# 扫描 ROM 数据区里直接引用传送脚本 ID 的位置
make rom-warp-ref-index

# 解码当前已发现的 {pointer, script_id} 表
make script-table-index
```

当前回归补丁是 `script_167.mary`：进入农场鸡屋会传送到海边。这个目标用于证明
`.mary -> binary -> ROM` 的闭环是可复现的。

传送索引输出到 [docs/generated/warp_index.tsv](./docs/generated/warp_index.tsv)，
用于快速查找 `Proc016(map, x, y)` 和后续玩家位置设置。
当前更可信的鸡屋入口触发线索是
[docs/generated/script_table_080F1FC0.tsv](./docs/generated/script_table_080F1FC0.tsv)
中的第 `126` 项：它指向 script `167`。
- **agbcc** — GBA C++ 编译器（`tools/agbcc/bin/`）

## 许可证

本项目为 GBA 游戏《牧场物语：矿石镇的伙伴们》的逆向工程，仅供学习研究使用。

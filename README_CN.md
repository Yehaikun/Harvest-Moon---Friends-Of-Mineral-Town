# 牧场物语：矿石镇的伙伴们 - 反编译项目

基于 [StanHash/fomt](https://github.com/StanHash/fomt) 的 GBA 游戏反编译项目。

## ROM 输入与输出

- `baserom.gba`：本地提供的原版美版 ROM，作为构建输入和数据基准。
- `fomt.gba`：派生构建产物，已应用源码和脚本补丁。

`baserom.gba` 仍然必须保留在项目根目录，但不能提交到 git，也不能手动修改。它用于：

- 链接脚本中的 `.incbin` 原始数据来源。
- `pre-build-check` 的原始脚本 slot、指针表、坏脚本检查。
- 生成 `docs/generated/` 索引时作为原版数据参考。
- 对照 `fomt.gba` 是否因为源码或脚本补丁发生了预期变化。

原版美版 ROM 的 SHA1 应为：

```text
a2fc3574f0a65a4fcf7682fb274b9d7eebdef963  baserom.gba
```

## 当前状态

| 组件 | 进度 |
|------|------|
| 核心引擎 | 约 40% 已反编译为 C++；高风险路径保持 asm |
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
| 第 7 阶段 | 继续核心引擎反编译 | UI、场景、实体、脚本解释器关键函数逐步转为 C/C++ | 每次迁移后地址不漂移，ROM 不白屏；`game_scene` 已因白屏回滚 |
| 第 8 阶段 | 内容包与发布包 | 新对话、新事件、新 NPC/地图的可扩展数据结构 | 可以用可开关、可验证、可回滚的包增加内容 |
| 第 9 阶段 | 工具化编辑 | 面向脚本/地图/NPC 的小型命令行或图形编辑器 | 不直接改 ROM，生成可审查补丁 |

### 说明

- 这不是单纯“把汇编全删掉”，而是把关键逻辑逐步抽成可维护的 C/C++ 和数据表。任何反编译结果只要导致白屏，就先回滚到 asm，再拆小包重试。
- 当前优先级是“内容改动可复现”高于“多反编译几个函数”；脚本和数据链路打通后，改对白、事件、NPC 才不会依赖临时 hex patch。
- `.mary` 文件已经进入 ROM 构建链。`SCRIPT_PATCHES` 会在 `make fomt.gba` 后自动编译并写入派生 ROM，禁止直接手动改 `baserom.gba`。
- DataCrystal RAM map 已确认能帮助验证时间、天气、金钱、好感度等运行时条件。以后改 NPC 对话前，要先确认旧存档的 RAM 条件是否真的会进入目标分支。
- DataCrystal ROM map 主要给 TV 节目文本偏移。HMMT、khadim 论坛、CodeBreaker 表和 Boktai tilemap 资料目前先作为线索，必须经过本项目实测再纳入正式流程。
- 地图和人物这类内容，最终会尽量变成数据驱动，而不是继续硬编码在汇编里。
- 如果后续要做真正的编辑器，优先顺序通常是“数据表可编辑”先于“图形化编辑器”。

### 近期安排

后续不再按“反编译多少行”推进，而按可测试的包推进：

| 包 | 内容 | 打包方式 | 验证方式 |
|----|------|----------|----------|
| 稳定包 | 构建、mary、脚本表定位、mGBA 启动 | 只包含构建脚本、工具和最小回归补丁 | `make check-all` + mGBA 截图非白屏 |
| 脚本内容包 | `.mary` 对话、事件、传送点 | 修改 `scripts/script_*.mary`，加入 `SCRIPT_PATCHES` | slot fit、反编译 grep、游戏内触发 |
| 地图数据包 | 入口、出生点、碰撞、地图表 | 优先生成索引和文档，再做最小数据 patch | 进出地图、坐标不进墙、不黑屏 |
| NPC 行为包 | NPC 对话分支、日程、好感条件 | 先写 RAM/条件观察表，再改脚本或数据 | 新旧存档分别测试触发条件 |
| 反编译包 | 单函数或小函数组 asm → C/C++ | 一包一个风险点，保留 asm 回滚路径 | 地址不漂移、ROM 不白屏、截图对照 |
| 发布包 | 一组已验证玩法改动 | changelog + 测试记录 + ROM 构建说明 | clean build、check-all、人工通关点测试 |

近期优先事项：

1. 固定稳定包：当前 `game_scene` 保持原始 asm；之前导致白屏的 C++ 拆分不再作为基线。
2. 给每次构建保留测试记录：记录 commit、ROM SHA1、mGBA 截图结果、人工测试点。
3. 把脚本补丁继续扩展为可开关内容包，而不是默认把所有实验脚本混进主包。
4. 增加 RAM 观察表：日期、时间、天气、金钱、主要候选对象好感度，用于解释对话分支为什么触发或不触发。
5. 评估 HMMT Dumper/Inserter：先做“无修改提取再插入”的 round-trip 测试，确认是否会破坏文本格式。
6. 重新启动第 7 阶段时，从比 `game_scene` 更小、更独立的函数开始；每次只迁移一个函数，不能再一次迁移场景核心路径。
7. 建立内容包开关：将实验脚本和稳定脚本分组，避免未验证内容默认进入 `make fomt.gba`。

更多外部资料整理见 [docs/references/fomt_reverse_engineering_sources.md](./docs/references/fomt_reverse_engineering_sources.md)。

## 构建

### baserom.gba 使用规则

`baserom.gba` 是必需输入，不是输出：

- 必须放在仓库根目录。
- 必须保持原版 SHA1，不要手动 hex edit。
- 不提交到 git；`.gitignore` 已排除 `*.gba`。
- 需要修改游戏时，只改源码、`.mary`、工具或数据文件，让构建生成新的 `fomt.gba`。
- 如果怀疑 ROM 被污染，重新放入原版 `baserom.gba`，再跑 `make clean && make -j2 fomt.gba`。

### 每次打包的最低标准

每次准备提交或发布 ROM 前，必须执行：

```bash
make clean
make -j2 fomt.gba
make check-all
```

然后用 mGBA 做图形检查：

```bash
mgba-qt fomt.gba
```

判定标准：

- `fomt.gba` 必须是 8MB：`8388608` 字节。
- `make check-all` 必须通过。
- mGBA 窗口不能是纯白/纯黑，标题能进入正常游戏画面。
- 内容包还必须进入游戏触发目标事件，而不只是启动成功。

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

# 编译后 ROM 的脚本表可能不在原版 0x0F89D4，优先用 map 自动定位
tools/script_slot.py fomt.gba --map fomt.map --script-id 167

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

脚本补丁工具会优先从 `fomt.map` 读取 `gUnk_080F89D4` 的真实地址。不要在工具里写死
编译后 ROM 的脚本表偏移；源码布局变化后，脚本表位置可能相对原版发生移动。

传送索引输出到 [docs/generated/warp_index.tsv](./docs/generated/warp_index.tsv)，
用于快速查找 `Proc016(map, x, y)` 和后续玩家位置设置。
当前更可信的鸡屋入口触发线索是
[docs/generated/script_table_080F1FC0.tsv](./docs/generated/script_table_080F1FC0.tsv)
中的第 `126` 项：它指向 script `167`。
- **agbcc** — GBA C++ 编译器（`tools/agbcc/bin/`）

## Git 工作流

本项目用 Git 保护开发的基本原则：每个可验证包一个分支、一个主题、一个提交或一组小提交。

推荐流程：

```bash
# 1. 开始前确认干净
git status

# 2. 从稳定点开新分支
git switch main
git switch -c pkg/<short-name>

# 3. 小步修改，中途随时看差异
git diff
git diff --stat

# 4. 每个包至少通过构建和检查
make clean
make -j2 fomt.gba
make check-all

# 5. 图形测试确认不白屏后提交
git add -A
git commit -m "Short package description"

# 6. 推远程分支，不强推 main
git push origin HEAD
```

高风险操作规则：

- 不在 `main` 上直接做实验性反编译；用 `pkg/...`、`decomp/...`、`content/...` 分支。
- 不把内容脚本修改和核心反编译放在同一个提交。
- 不提交 `baserom.gba`、`fomt.gba`、模拟器存档、临时截图等产物。
- push `main` 被拒绝时，不要 `--force`；改推新分支并开 PR。
- 如果白屏，优先 `git switch` 回上一个正常提交验证，再用 `git diff` 缩小问题。
- 遇到临时探索但还不想提交，用 `git stash push -u -m "说明"`；修复完成后及时 `git stash drop` 清理。

建议分支命名：

| 类型 | 命名 | 示例 |
|------|------|------|
| 稳定修复 | `fix/...` | `fix/script-table-map-offset` |
| 内容包 | `content/...` | `content/karen-dialogue-test` |
| 地图包 | `map/...` | `map/chicken-coop-warp` |
| 反编译包 | `decomp/...` | `decomp/sram-proxy-small-step` |
| 文档包 | `docs/...` | `docs/package-roadmap` |

回滚策略：

```bash
# 查看最近提交
git log --oneline --decorate -10

# 临时回到某个提交测试，不改分支历史
git switch --detach <commit>

# 回到分支
git switch <branch>

# 已提交但要撤销，用 revert，避免改写共享历史
git revert <bad-commit>
```

## 许可证

本项目为 GBA 游戏《牧场物语：矿石镇的伙伴们》的逆向工程，仅供学习研究使用。

# 牧场物语：矿石镇的伙伴们 — 反编译项目

基于 2003 年 GBA 游戏 **牧场物语：矿石镇的伙伴们**（美版）的反编译工程。

可编译出以下 ROM：

- **`fomt.gba`**：派生构建产物，已应用源码和脚本补丁。
- **`baserom.gba`**：本地提供的原版美版 ROM，作为构建输入和数据基准。

`baserom.gba` 必须保留在项目根目录，但不能提交到 git，也不能手动修改。它用于：

- `objcopy` / 链接脚本中的 `.incbin` 原始数据来源。
- `pre-build-check` 的原始脚本 slot、指针表、坏脚本检查。
- 生成 `docs/generated/` 索引时作为原版数据参考。
- 对照 `fomt.gba` 是否因为源码或脚本补丁发生了预期变化。

原版美版 ROM 的 SHA1 应为：

```text
a2fc3574f0a65a4fcf7682fb274b9d7eebdef963  baserom.gba
```

## 当前进度

| 组件 | 进度 | 说明 |
|------|------|------|
| 核心引擎 | ~40% | 已反编译为 C++（`src/`）；高风险路径保持 asm |
| 事件脚本 | 1328/1328 | 已全部反编译，可用 mary 工具编辑 |
| 场景切换 | ✅ 已反编译 | `func_080168D4` → `src/scene_transition.cc` |
| 地图数据 | ✅ 已分析 | 50 张地图的表结构已定位；碰撞格式已解码（64x64 LZ77 网格，游戏内实测验证） |
| NPC 行为 | ❌ 汇编中 | `asm/code_entities.s`（31,812 行） |
| 脚本引擎 | ❌ 汇编中 | `asm/code_0803EE94.s`（179,483 行） |

## 路线图

目标不只是把 ROM 翻成源码，而是最终做到：

- 全量反编译剩余核心逻辑
- 让对话、地图、NPC、事件、物品、数值都能修改
- 修改后可重新构建出可运行 ROM
- 配套尽量轻量的编辑与校验工具

当前已经恢复 `mary` 工具链，后续路线优先从“能稳定改内容”开始，再逐步深入引擎反编译。

| 阶段 | 目标 | 交付物 | 验证标准 | 真实状态 |
|------|------|--------|----------|:---------:|
| 第 0 阶段 | 稳定基础构建 | `make fomt.gba`、`make check-mary` 可重复运行 | clean build 通过，ROM 不白屏 | ✅ |
| 第 1 阶段 | 脚本补丁可复现 | `.mary -> binary -> ROM` 闭环 | 鸡屋门传送可修改/验证 | ✅ |
| 第 2 阶段 | 脚本索引与触发链路 | slot 表、传送索引、实体脚本表、NPC 对话映射、触发链文档 | 能回答"哪个实体/脚本做啥" | ✅ |
| 第 3 阶段 | 对白/事件修改规范 | NPC 对话修改文档 + 实测 | 安的对白已改通 | ✅ |
| 第 4 阶段 | 校验工具 | slot 检查、指针检查、坏脚本黑名单 | 构建时拦截错误，不白屏 | ✅ |
| 第 5 阶段 | 地图与场景数据 | 地图 ID 表、传送点、碰撞格式解码、安全修改工作流 | 碰撞值含义已通过游戏内实测验证（可穿墙/河） | ✅ |
| 第 6 阶段 | 工具评估 | HMMT/CodeBreaker/khadim 可用性评估 | 8 种工具已评估 | 🔶 HMMT insert 未实测 |
| 第 7 阶段 | 核心引擎反编译 | asm → C/C++ 迁移包 | 每包都能构建、`check-all`、mGBA 不白屏 | 🔶 进行中：SRAM/lib_sram/more_items 已迁移，`code_libc_string` 暂保留 asm，`game_scene` 已因白屏回滚 |
| 第 8 阶段 | 内容包与发布包 | 新对话/事件/地图/NPC 的可复用 patch 包 | 可开关、可验证、可回滚 | ❌ 未开始 |
| 第 9 阶段 | 工具化编辑 | 面向脚本/地图/NPC 的小型命令行或图形编辑器 | 不直接改 ROM，生成可审查补丁 | ❌ 未开始 |

### 说明

- 目标不是立刻删掉全部汇编，而是把关键逻辑逐步抽成可维护的 C/C++ 和数据表。任何反编译结果只要导致白屏，就先回滚到 asm，再拆小包重试。
- 当前优先级是“内容改动可复现”高于“多反编译几个函数”；脚本和数据链路打通后，改对白、事件、NPC 才不会依赖临时 hex patch。
- `.mary` 文件已经进入 ROM 构建链。`SCRIPT_PATCHES` 会在 `make fomt.gba` 后自动编译并写入派生 ROM，禁止直接手动改 `baserom.gba`。
- DataCrystal RAM map 已确认能帮助验证时间、天气、金钱、好感度等运行时条件。以后改 NPC 对话前，要先确认旧存档的 RAM 条件是否真的会进入目标分支。
- DataCrystal ROM map 主要给 TV 节目文本偏移。HMMT、khadim 论坛、CodeBreaker 表和 Boktai tilemap 资料目前先作为线索，必须经过本项目实测再纳入正式流程。
- 地图和人物这类内容，优先做成数据驱动，而不是继续硬编码在汇编里。
- 如果后面做图形化编辑器，优先顺序通常是“数据表可编辑”先于“图形化界面”。

### 后续阶段安排

后续不再按“反编译多少行”推进，而按可测试的包推进。每个包都必须能独立回滚、独立验证。

| 包 | 内容 | 打包方式 | 验证方式 |
|----|------|----------|----------|
| 稳定包 | 构建、mary、脚本表定位、mGBA 启动 | 只包含构建脚本、工具和最小回归补丁 | `make check-all` + mGBA 截图非白屏 |
| 脚本内容包 | `.mary` 对话、事件、传送点 | 修改 `scripts/script_*.mary`，加入 `SCRIPT_PATCHES` | slot fit、反编译 grep、游戏内触发 |
| 地图数据包 | 入口、出生点、碰撞、地图表 | 优先生成索引和文档，再做最小数据 patch | 进出地图、坐标不进墙、不黑屏 |
| NPC 行为包 | NPC 对话分支、日程、好感条件 | 先写 RAM/条件观察表，再改脚本或数据 | 新旧存档分别测试触发条件 |
| 反编译包 | 单函数或小函数组 asm → C/C++ | 一包一个风险点，保留 asm 回滚路径 | 地址不漂移、ROM 不白屏、截图对照 |
| 发布包 | 一组已验证玩法改动 | changelog + 测试记录 + ROM 构建说明 | clean build、check-all、人工通关点测试 |

### 近期安排

1. 固定稳定包：当前 `game_scene` 保持原始 asm；之前导致白屏的 C++ 拆分不再作为基线。
2. 给每次构建保留测试记录：记录 commit、ROM SHA1、mGBA 截图结果、人工测试点。
3. 把脚本补丁继续扩展为可开关内容包，而不是默认把所有实验脚本混进主包。
4. 增加 RAM 观察表：日期、时间、天气、金钱、主要候选对象好感度，用于解释对话分支为什么触发或不触发。
5. 评估 HMMT Dumper/Inserter：先做“无修改提取再插入”的 round-trip 测试，确认是否会破坏文本格式。
6. 重新启动第 7 阶段时，从比 `game_scene` 更小、更独立的函数开始；每次只迁移一个函数，不能再一次迁移场景核心路径。
7. 建立内容包开关：将实验脚本和稳定脚本分组，避免未验证内容默认进入 `make fomt.gba`。

更多外部资料整理见 [docs/references/fomt_reverse_engineering_sources.md](./docs/references/fomt_reverse_engineering_sources.md)。

## 构建与验证流程

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

如果需要在终端辅助判断是否白屏，可以运行 SDL 版并截图检查像素：

```bash
SDL_AUDIODRIVER=dummy mgba fomt.gba
```

判定标准：

- `fomt.gba` 必须是 8MB：`8388608` 字节。
- `make check-all` 必须通过。
- mGBA 窗口不能是纯白/纯黑，标题能进入正常游戏画面。
- 内容包还必须进入游戏触发目标事件，而不只是启动成功。

### 完整构建（日常开发推荐）

```bash
make check-all          # 检查工具链 + slot 大小 + 索引完整性
make -j2 fomt.gba       # 编译 ROM
make check-script-patches  # 验证补丁已写入
```

### 快速构建（只改 C/ASM，不改脚本）

```bash
make -j2 fomt.gba
```

### 改了对白/事件脚本后

```bash
make pre-build-check    # 检查脚本是否超出 ROM slot
make -j2 fomt.gba
make check-script-patches
```

### 一键完成

```bash
make check-all && make -j2 fomt.gba && make check-script-patches
```

### ROM 位置

构建产物为 `fomt.gba`，用模拟器打开：

```bash
mgba-qt fomt.gba          # mGBA（推荐）
visualboyadvance-m fomt.gba  # VBA
```

> 注意：因已修改源码，`make compare` 的 SHA1 校验会失败，但 `fomt.gba` 会正常生成。

详见 [INSTALL.md](./INSTALL.md)。

## 反编译实践规范

为了最大限度避免修改后启动白屏，反编译时必须按下面流程执行：

1. 一次只迁移一个很小的函数，尤其是启动、IRQ、DMA、BIOS 调用、SRAM、显示寄存器、场景相关代码。
2. 迁移前记录当前函数地址、下一个函数地址、原函数长度。
3. 迁移后编译 `fomt.gba`，并检查 `fomt.map`，当前函数和下一个函数都必须保持原地址。
4. 如果 C/C++ 代码比原 asm 短，必须在 `fomt.lds` 中补齐空洞，例如 `. = . + 4;`，不能让后续函数前移。
5. 不要在当前 `.rom` 段里随意写 `. = 0x080002E0;` 这类绝对地址；本项目中这会导致链接地址计算错误。
6. 如果 C/C++ 代码比原 asm 长，不能硬挤覆盖后续函数；应简化代码、保留部分 asm，或换更小的函数。
7. 每次反编译操作后都要执行：

```bash
make -j2 fomt.gba
grep -n "当前函数名\|下一个函数名" fomt.map
file fomt.gba
visualboyadvance-m fomt.gba
```

8. 如果出现白屏，第一优先检查 `fomt.map` 里的地址漂移，再判断逻辑问题。
9. 每次迁移都必须能单独回滚；如果补齐地址后仍白屏，先回滚该函数，再继续下一步。
10. 场景、脚本引擎、SRAM、IRQ、DMA、启动流程属于高风险区域，必须优先保留 asm wrapper 或原始 asm，对照验证后再逐个替换。
11. 反编译包不要和内容包混在同一个提交里；否则白屏时无法判断是逻辑迁移还是脚本 patch 引入。

已验证案例：`func_08000240` 初次迁移到 C 后编译通过，但下一个函数 `func_080002E0` 从 `0x080002E0` 前移到 `0x080002DC`，导致白屏。补齐 4 字节后地址恢复，ROM 启动正常。

失败案例：`game_scene` 曾被拆成 C++ 函数和剩余 asm，地址和构建检查都能通过，但 mGBA 图形测试白屏。最终处理是回滚到原始 `asm/game_scene.s`，把该区域重新列为高风险反编译包，后续必须拆成更小函数并保留逐步对照。

## 非代码辅助资料

为了让后续改动可追踪，项目应继续补齐这些非代码资料：

| 文件/目录 | 用途 | 状态 |
|-----------|------|------|
| `docs/generated/` | 自动生成的脚本、传送、触发候选索引 | 已有 |
| `docs/references/` | 外部资料整理和实测结论 | 已有，持续补充 |
| `docs/ram_map.md` | 运行时 RAM 观察点 | 已有，需补候选对象和天气/时间测试流程 |
| `docs/references/npc_dialogue_guide.md` | NPC 对话修改流程 | 已有，需继续补旧存档条件判断 |
| `docs/references/map_data_guide.md` | 地图、入口、碰撞数据说明 | 已有，需补更多入口实测 |
| `docs/test_logs/` | 每次打包测试记录、截图结论、人工测试点 | 已添加模板 |
| `docs/release_checklist.md` | 发布/提交前检查清单 | 已添加 |

建议每个重要包都增加一条测试记录：commit、构建命令、ROM 大小、mGBA 是否白屏、人工进入的地图/事件、发现的问题。

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

当前回归补丁是 `script_167.mary`：进入农场鸡屋会传送到女神泉。这个目标用于证明
`.mary -> binary -> ROM` 的闭环是可复现的。

脚本补丁工具会优先从 `fomt.map` 读取 `gUnk_080F89D4` 的真实地址。不要在工具里写死
编译后 ROM 的脚本表偏移；源码布局变化后，脚本表位置可能相对原版发生移动。

传送索引输出到 [docs/generated/warp_index.tsv](./docs/generated/warp_index.tsv)，
用于快速查找 `Proc016(map, x, y)` 和后续玩家位置设置。
当前更可信的鸡屋入口触发线索是
[docs/generated/script_table_080F1FC0.tsv](./docs/generated/script_table_080F1FC0.tsv)
中的第 `126` 项：它指向 script `167`。
- **agbcc** — GBA 专用 C++ 编译器，位于 `tools/agbcc/bin/`

## 致谢

本项目基于 [StanHash/fomt](https://github.com/StanHash/fomt) 的原始反编译工作。

## 许可证

仅供学习研究使用。游戏版权归原版权方所有。

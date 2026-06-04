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

## 路线图

目标不只是把 ROM 翻成源码，而是最终做到：

- 全量反编译剩余核心逻辑
- 让对话、地图、NPC、事件、物品、数值都能修改
- 修改后可重新构建出可运行 ROM
- 配套尽量轻量的编辑与校验工具

当前已经恢复 `mary` 工具链，后续路线优先从“能稳定改内容”开始，再逐步深入引擎反编译。

| 阶段 | 目标 | 交付物 | 验证标准 |
|------|------|--------|----------|
| 第 0 阶段 | 稳定基础构建 | `make fomt.gba`、`make check-mary` 可重复运行 | ✅ 全量 clean build 通过，ROM 已确认不白屏 |
| 第 1 阶段 | 脚本补丁可复现 | `tools/patch_script.py` 或 Makefile 规则，完成 `.mary -> binary -> derived ROM` | 不手动改 `baserom.gba`，修改 `script_167.mary` 后重新构建仍能进鸡屋传送到海边 |
| 第 2 阶段 | 脚本索引与触发链路 | 脚本 ID、ROM 偏移、slot 大小、`Proc016` 传送点、实体脚本表、ROM 数据区引用 | 🔄 部分完成：实体→脚本映射已建立，地图坐标→实体映射延迟到第 5 阶段（见 `docs/generated/README.md`） |
| 第 3 阶段 | 对白/事件修改规范 | 对话文本、事件脚本、分支条件、RAM 验证地址、脚本 ID 的对应关系文档化（`docs/references/npc_dialogue_guide.md`） | ✅ 已完成：NPC → 脚本映射、对话分支条件、修改流程、RAM 验证地址均已文档化。事件标志（Func03E）到具体条件的映射待后续补充 |
| 第 4 阶段 | 数据补丁器与校验工具 | 文本长度检查、指针/偏移检查、脚本编译输出大小检查、mary 坏脚本黑名单（`tools/pre_build_checks.py`、`make check-all`） | ✅ 已完成：slot 大小检查、指针表完整性检查、`make check-all` 一键验证。错误在链接前报告，不进游戏白屏 |
| 第 5 阶段 | 地图与场景数据链路 | 地图 ID、出生点、传送点、地图块/碰撞线索、DataCrystal/论坛资料交叉表 | 能安全修改一个入口/出生点，并避免传到墙里或黑屏 |
| 第 6 阶段 | 文本与内容数据工具评估 | HMMT、DataCrystal ROM map、khadim 资料、CodeBreaker 地址的可用性测试文档 | 能确定哪些文本/物品/价格/NPC 数据适合工具改，哪些必须反编译 |
| 第 7 阶段 | 继续核心引擎反编译 | UI、场景、实体、脚本解释器关键函数逐步转为 C/C++ | 每次迁移后地址不漂移，ROM 不白屏 |
| 第 8 阶段 | 自定义内容支持 | 新对话、新事件、新 NPC/地图的可扩展数据结构 | 可以用文档化流程增加一段新内容 |

### 说明

- 目标不是立刻删掉全部汇编，而是把关键逻辑逐步抽成可维护的 C/C++ 和数据表。
- 当前优先级是“内容改动可复现”高于“多反编译几个函数”；脚本和数据链路打通后，改对白、事件、NPC 才不会依赖临时 hex patch。
- 目前 `.mary` 文件还没有完全进入 ROM 构建链。鸡屋传送到海边已经验证有效，但它依赖本地 ROM 数据被补丁过；下一步必须把这个补丁过程写成受版本控制的工具。
- DataCrystal RAM map 已确认能帮助验证时间、天气、金钱、好感度等运行时条件。以后改 NPC 对话前，要先确认旧存档的 RAM 条件是否真的会进入目标分支。
- DataCrystal ROM map 主要给 TV 节目文本偏移。HMMT、khadim 论坛、CodeBreaker 表和 Boktai tilemap 资料目前先作为线索，必须经过本项目实测再纳入正式流程。
- 地图和人物这类内容，优先做成数据驱动，而不是继续硬编码在汇编里。
- 如果后面做图形化编辑器，优先顺序通常是“数据表可编辑”先于“图形化界面”。

### 近期安排

1. 编写脚本 slot 检查器：输入脚本 ID，输出指针、ROM offset、下一个脚本 offset、可用字节数。
2. 编写受版本控制的脚本补丁器：把指定 `.mary` 编译为二进制，检查长度后插入派生 ROM，禁止直接手动改 `baserom.gba`。
3. 把 `script_167.mary` 的鸡屋传送改动作为第一个自动化回归用例：重新 clean build 后仍能反编译验证 `Proc016(1, 24, 280)`。
4. 扫描全部 `.mary`，生成 `Proc016` / `SetEntityPosition` 传送索引表，优先服务地图和入口改造。
5. 建立 RAM 观察表：日期、时间、天气、金钱、主要候选对象好感度，用于解释对话分支为什么触发或不触发。
6. 评估 HMMT Dumper/Inserter：先做“无修改提取再插入”的 round-trip 测试，确认是否会破坏文本格式。
7. 在每次内容改动或反编译迁移后执行 `make check-mary`、`make -j2 fomt.gba`，并用模拟器确认不白屏。

更多外部资料整理见 [docs/references/fomt_reverse_engineering_sources.md](./docs/references/fomt_reverse_engineering_sources.md)。

## 构建与验证流程

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

已验证案例：`func_08000240` 初次迁移到 C 后编译通过，但下一个函数 `func_080002E0` 从 `0x080002E0` 前移到 `0x080002DC`，导致白屏。补齐 4 字节后地址恢复，ROM 启动正常。

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
- **agbcc** — GBA 专用 C++ 编译器，位于 `tools/agbcc/bin/`

## 致谢

本项目基于 [StanHash/fomt](https://github.com/StanHash/fomt) 的原始反编译工作。

## 许可证

仅供学习研究使用。游戏版权归原版权方所有。

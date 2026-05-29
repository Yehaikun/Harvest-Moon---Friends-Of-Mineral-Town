// ═══════════════════════════════════════════════════════════════════════════════
// 【田地系统】Field
// ═══════════════════════════════════════════════════════════════════════════════
// 管理牧场的每一块田地格子（FieldPlot）的状态，包括：
//   · 是否已耕种
//   · 种了什么作物（以及生长阶段）
//   · 是否有杂草/石头/树枝
//   · 是否有肥料
//   · 每天的作物生长更新
//
// 每个格子包含以下状态位：
//   unk_00_00 (2bit): 土地状态 0=普通 1=耕好 2=已浇水 3=硬化
//   unk_00_02 (6bit): ★ 作物/物品类型 ID（0x00～0x26）
//   unk_00_08 (4bit): ★ 生长阶段（0～8，8=成熟/枯萎）
//   unk_00_0C (5bit): 生长计时器
//   unk_00_11 (3bit): 生长所需天数
// ═══════════════════════════════════════════════════════════════════════════════

#include "field.hh"
#include "rucksack_item.hh"

// ── 外部数据结构（定义在 .incbin 中）───────────────────────────────────

// 作物/物品的配置信息
struct Unk_080E93F8
{
    /* +00 */ Unk_Something const * unk_00;  // 调色板/颜色信息
    /* +04 */ u8 unk_04;   // 阶段2的颜色
    /* +05 */ u8 unk_05;   // 阶段3的颜色
    /* +06 */ u8 unk_06;   // 阶段4的颜色
    /* +07 */ u8 unk_07;   // 阶段5（成熟）的颜色
    /* +08 */ u8 unk_08;   // 阶段6（枯萎）的颜色
    /* +09 */ u8 unk_09;   //
    /* +0A */ u16 unk_0A;  // 收获时得到的物品 ID（0xFF=无收获）
};
extern Unk_080E93F8 const gUnk_080E93F8[];

// 作物的生长天数表 [作物ID][生长阶段] = 需要天数
extern u32 const gUnk_080E8D14[][21];

// 天气对田地的影响概率
struct Unk_080E8CC4
{
    /* +00 */ u8 unk_00;  // 木头变树桩概率
    /* +01 */ u8 unk_01;  // 耕地变普通概率（下雨时）
    /* +02 */ u8 unk_02;  // 长杂草概率（下雨时）
    /* +03 */ u8 unk_03;  // 长石头概率（下雨时）
    /* +04 */ u8 unk_04;  // 长杂草概率（普通时）
    /* +05 */ u8 unk_05;  // 长石头概率（普通时）
    /* +06 */ u8 unk_06;  // 长树枝概率（普通时）
    /* +07 */ u8 unk_07;  // 作物枯萎概率（暴雨时）
};
extern Unk_080E8CC4 const gUnk_080E8CC4[4][2];  // [季节][是否下雨]
extern Unk_080E8CC4 const gUnk_080E8D04;  // 台风天气参数
extern Unk_080E8CC4 const gUnk_080E8D0C;  // 暴雪天气参数

// ── 无参构造函数 ────────────────────────────────────────────────────────
// 创建一个空的田地格子
FieldPlot::FieldPlot()
    : unk_00_00(0), unk_00_02(0), unk_00_08(0), unk_00_0C(0),
      unk_00_11(method_0800A014())  // 初始化生长天数参照
{}

// ── 有参构造函数 ────────────────────────────────────────────────────────
FieldPlot::FieldPlot(u32 arg_1, u32 arg_2, u32 arg_3)
    : unk_00_00(arg_1), unk_00_02(arg_2), unk_00_08(arg_3), unk_00_0C(0),
      unk_00_11(method_0800A014())
{}

// ── 获取参照生长天数 ──────────────────────────────────────────────────
// 根据作物种类和状态，返回一个参考值（可能是成熟所需天数）
u32 FieldPlot::method_0800A014() const
{
    u32 result = 1;
    if (GetUnk8() != 0) {
        switch (unk_00_02) {
            case 0x1A:                          // 黄金木材
                result = 6; break;
            case 0x1B: case 0x1C: case 0x1D: case 0x1E:  // 各种草
                result = 6; break;
            case 0x23: case 0x24: case 0x25: case 0x26:  // 牧草
                result = 6; break;
            case 0x1F: case 0x20: case 0x21: case 0x22:  // 其他作物
                result = 3; break;
        }
    }
    return result;
}

// ── 是否是"需要清理"的状态 ──────────────────────────────────────────
// 判断格子上是否有杂草/石头/树枝等需要清理的东西
bool FieldPlot::method_0800A07C() const
{
    int val = unk_00_08;
    switch (val) {
        case 0: case 1: return false;  // 空地或耕地
        case 2: case 3: case 4: case 5: case 6: case 7: case 8:
            if (unk_00_02 != 0x14) return true;  // 不是草 → 需要清理
            return false;
    }
    return false;
}

// ── 获取收获/采集时的物品 ID ─────────────────────────────────────────
// 根据作物和生长阶段，返回对应的物品编号
u32 FieldPlot::method_0800A0A4() const
{
    int val = unk_00_08;
    switch (val) {
        case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
            return 0;
        case 8:
            // 不同作物成熟时产生不同物品
            switch (unk_00_02) {
                case 0x1B: case 0x1C: case 0x1D: case 0x1E:
                    return 0x3CC; // 某种草
                case 0x23: case 0x24: case 0x25: case 0x26:
                    return 0x3CB; // 牧草
                case 0x1F: case 0x20: case 0x21: case 0x22:
                    return 0x3CA; // 其他
            }
            return 0;
    }
    return 0;
}

// ── 状态设置 ────────────────────────────────────────────────────────────

// 设置土地状态（0=普通 1=耕好 2=已浇水 3=硬化）
void FieldPlot::method_0800A120(int arg_1) { unk_00_00 = arg_1; }

// ★ 设置作物类型和生长阶段（种地时调用）
void FieldPlot::method_0800A134(int id, int arg_2) {
    unk_00_02 = id;          // ★ 作物 ID
    unk_00_08 = arg_2;       // ★ 生长阶段
    unk_00_11 = method_0800A014();  // 更新生长天数参照
    if (arg_2 == 8 && GetUnk0() != 3)
        unk_00_00 = 0;
}

// ── 锄头翻地/清理 ─────────────────────────────────────────────────────
// 用锄头翻地时调用。arg_1=是否浇水
u32 FieldPlot::method_0800A190(bool arg_1) {
    u32 result = 0;
    u32 u0 = GetUnk0();
    if (u0 == 0) {
        if (GetUnk8() == 0) {
            unk_00_00 = arg_1 ? 1 : 2;  // 耕好/浇水
            unk_00_08 = 0;
            result = 1;
        }
        if (result == 1) {
            // 随机出现杂物
            u32 r = rand() & 0xFF;
            if (r < 10) {
                result = 2;           // 出现石头
            } else if ((r -= 10) < 3) {
                result = 4;           // 出现杂草
            } else if ((r -= 3) < 5) {
                result = 3;           // 出现树枝
            }
        }
    } else if (u0 == 1 || u0 == 2) {
        switch (GetUnk8()) {
            case 1: unk_00_08 = 0; result = 1; break;
            case 7: unk_00_00 = arg_1 ? 1 : 2; unk_00_08 = 0; result = 1; break;
            case 8: result = 0; break;
        }
    }
    return result;
}

// ── 作物生长更新（每天调用）────────────────────────────────────────
// ★ 想改生长速度就改这里的参数
u32 FieldPlot::method_0800A238(int arg_1) {
    if (GetUnk8() == 0) {
        if (GetUnk0() == 1 || GetUnk0() == 2)
            unk_00_00 = 0;
        return 1;
    }

    int r1, r4;
    switch (unk_00_02) {
        default: return 0;
        case 0x16: r1 = 0; r4 = 3; break;  // 石头
        case 0x18: r1 = 0; r4 = 5; break;  // 木材
        case 0x19: r1 = 0; r4 = 6; break;  // 树桩
        case 0x1A: r1 = 3; r4 = 4; break;  // 黄金木材
        case 0x1F: case 0x20: case 0x21: case 0x22:
            r1 = 1; r4 = 7; break;          // 牧草类
        case 0x23: case 0x24: case 0x25: case 0x26:
            r1 = 2; r4 = 8; break;          // 其他
    }

    if (arg_1 - r1 > 0) {
        arg_1 = arg_1 - r1;
        if (arg_1 >= GetUnk11()) {
            // 生长完成
            unk_00_11 = 0;
            unk_00_08 = 0;
            if (GetUnk0() != 3)
                unk_00_00 = 0;
            return r4;  // 返回成熟状态
        } else {
            unk_00_11 -= arg_1;  // 还在生长中
        }
    }
    return 2;
}

// ── 作物第1阶段生长 ──────────────────────────────────────────────────
u32 FieldPlot::method_0800A33C(int arg_1) {
    if (GetUnk8() == 0) return 0;
    int r1, r5;
    switch (GetUnk2()) {
        default: return 0;
        case 0x17: r1 = 0; r5 = 1; break;  // 树枝
        case 0x1B: case 0x1C: case 0x1D: case 0x1E:
            r1 = 1; r5 = 2; break;          // 草类
    }
    if (arg_1 - r1 > 0) {
        arg_1 = arg_1 - r1;
        if (arg_1 >= GetUnk11()) {
            unk_00_11 = 0; unk_00_08 = 0;
            if (GetUnk0() != 3) unk_00_00 = 0;
            return r5;
        } else {
            unk_00_11 -= arg_1;
        }
    }
    return 3;
}

// ── 收获判断 ──────────────────────────────────────────────────────────
u32 FieldPlot::method_0800A3C8() {
    if (GetUnk8() != 0) {
        if (GetUnk2() == 0x14) {  // 牧草
            if (GetUnk8() == 5) { unk_00_08 = 7; unk_00_0C = 0; return 1; }
        } else if (GetUnk2() != 0x15) {
            u32 u0 = GetUnk0();
            if (u0 == 1 || u0 == 2) {
                if (GetUnk8() == 6 || GetUnk8() == 2 || GetUnk8() == 3 || GetUnk8() == 4 || GetUnk8() == 5) {
                    unk_00_08 = 0; return 2;  // 收获完成，重置
                }
            }
        } else {
            unk_00_08 = 0; return 2;
        }
    }
    return 0;
}

// ── 土地硬化处理 ────────────────────────────────────────────────────
u32 FieldPlot::method_0800A438() {
    if (GetUnk0() == 1) { unk_00_00 = 2; return 1; }
    return 0;
}

// ── 播种 ──────────────────────────────────────────────────────────────
// ★ arg_1 = 作物 ID（参考 inventory.h 中的 FOOD_XXX 枚举）
void FieldPlot::method_0800A460(int arg_1) {
    u32 u0 = GetUnk0();
    if (u0 == 1 || u0 == 2) {
        if (GetUnk8() == 0) {
            unk_00_08 = 1;      // 生长阶段设为1（发芽）
            unk_00_02 = arg_1;   // ★ 设置作物类型
            unk_00_0C = 0;       // 重置生长计时器
        }
    }
}

// ── 收获物品 ──────────────────────────────────────────────────────────
RucksackItem FieldPlot::method_0800A4A4() {
    switch (GetUnk8()) {
        case 5:  // 成熟可收获
            switch (GetUnk2()) {
                case 0x2:  unk_00_08 = 2; unk_00_0C = 4; break;  // 萝卜
                case 0x3:  unk_00_08 = 3; unk_00_0C = 6; break;  // 土豆
                case 0x5:  unk_00_08 = 4; unk_00_0C = 6; break;  // 草莓
                case 0x6:  unk_00_08 = 4; unk_00_0C = 11; break; // 玉米
                case 0x9:  unk_00_08 = 4; unk_00_0C = 15; break; // 洋葱
                case 0xA:  unk_00_08 = 3; unk_00_0C = 6; break;  // 南瓜
                case 0xC:  unk_00_08 = 2; unk_00_0C = 3; break;  // 茄子
                case 0xE:  unk_00_08 = 4; unk_00_0C = 5; break;  // 菠菜
                case 0x14: return RucksackItem();  // 牧草（成熟后直接消失）
                default:   unk_00_08 = 0; unk_00_0C = 0; break;
            }
            break;
        case 8:  // 枯萎/可采集
            if (gUnk_080E93F8[unk_00_02].unk_0A != 0xFF) {
                unk_00_08 = 0; // 采集后消失
            }
            break;
        default: return RucksackItem();
    }

    fu16 id = gUnk_080E93F8[GetUnk2()].unk_0A;
    if (id == 0xFF) return RucksackItem();
    if (GetUnk2() < 0xF)
        return RucksackItem(Food(id));   // 食物类收获品
    else
        return RucksackItem(Article(id)); // 物品类收获品
}

// ── 能否放置物品（石头/木材等）────────────────────────────────────
bool FieldPlot::method_0800A6C8(Article const & article) const {
    if (GetUnk8() == 0) {
        switch (article.GetId()) {
            case ARTICLE_STONES:
            case ARTICLE_BRANCHES:
            case ARTICLE_LUMBER:
            case ARTICLE_GOLDEN_LUMBER:
                return true;  // 可以放石头/树枝/木材/黄金木材
        }
    }
    return false;
}

// ── 放置物品到地上 ──────────────────────────────────────────────────
void FieldPlot::method_0800A6F4(Article const & article) {
    if (method_0800A6C8(article)) {
        switch (article.GetId()) {
            case ARTICLE_STONES:       unk_00_02 = 0x16; break;
            case ARTICLE_LUMBER:       unk_00_02 = 0x18; break;
            case ARTICLE_GOLDEN_LUMBER: unk_00_02 = 0x1A; break;
            case ARTICLE_BRANCHES:     unk_00_02 = 0x17; break;
            default: return;
        }
        unk_00_08 = 8;
        if (GetUnk0() != 3) unk_00_00 = 0;
        unk_00_11 = method_0800A014();
    }
}

// ── 检查格子是否被占用（种了东西/有杂物）──────────────────────────
bool FieldPlot::method_0800A78C() const {
    if (GetUnk8() != 0) {
        switch (GetUnk2()) {
            case 0x1B: case 0x1C: case 0x1D: case 0x1E:
            case 0x1F: case 0x20: case 0x21: case 0x22:
            case 0x23: case 0x24: case 0x25: case 0x26:
                return true;  // 草类/牧草占用的格子
            default: return false;
        }
    }
    return false;
}

// ═══════════════════════════════════════════════════════════════════════════════
//  每日更新（核心）
// ═══════════════════════════════════════════════════════════════════════════════
// ★ 每天结束时调用，控制作物生长、杂草石头出现等
//    weather: 0=晴天 1=雨天 2=雪天 3=台风 4=暴雪
//    date: 当前日期（包含季节信息）
// ═══════════════════════════════════════════════════════════════════════════════

void FieldPlot::DayUpdate(int weather, GameDate const & date)
{
    // ── 季节作物枯萎 ─────────────────────────────────────────────────
    // 非当季的作物在阶段1之后会枯萎
    if (GetUnk8() == 1) {
        switch (GetUnk2()) {
            case 0x00: case 0x01: case 0x02: case 0x03:
            case 0x04: case 0x0F: case 0x13:
                if (date.season != 0) unk_00_08 = 0; break;  // 春作物 → 非春枯萎
            case 0x05: case 0x06: case 0x07: case 0x08:
            case 0x09: case 0x10:
                if (date.season != 1) unk_00_08 = 0; break;  // 夏作物
            case 0x0A: case 0x0B: case 0x0C: case 0x0D:
            case 0x0E: case 0x11: case 0x12:
                if (date.season != 2) unk_00_08 = 0; break;  // 秋作物
        }
    }

    // ── 生长阶段推进 ─────────────────────────────────────────────
    if (GetUnk8() != 0) {
        switch (GetUnk2()) {
            case 0x00: case 0x01: case 0x02: case 0x03:
            case 0x04: case 0x0F: case 0x13: case 0x05:
            case 0x06: case 0x07: case 0x08: case 0x09:
            case 0x10: case 0x0A: case 0x0B: case 0x0C:
            case 0x0D: case 0x0E: case 0x11: case 0x12:
                switch (GetUnk8()) {
                    case 4: case 3: case 2: case 1:
                        if (GetUnk0() == 2) {
                            unk_00_0C = unk_00_0C + 1;  // 生长天数+1
                            int r3 = GetUnk8();
                            if (r3 != gUnk_080E8D14[unk_00_02][unk_00_0C])
                                unk_00_08 = gUnk_080E8D14[unk_00_02][unk_00_0C]; // 升阶段
                        }
                        break;
                    case 5: break;  // 成熟状态，不变
                }
                break;

            case 0x14:  // 牧草特殊处理
                if (date.season != 3 && GetUnk8() != 5) {
                    unk_00_0C = unk_00_0C + 1;
                    int r3 = GetUnk8();
                    if (r3 == 7) r3 = 1;
                    if (r3 != gUnk_080E8D14[unk_00_02][unk_00_0C])
                        unk_00_08 = gUnk_080E8D14[unk_00_02][unk_00_0C];
                }
                break;

            // 石头/木材/树枝等不生长
            case 0x15: case 0x16: case 0x17: case 0x18:
            case 0x19: case 0x1A: case 0x1B: case 0x1C:
            case 0x1D: case 0x1E: case 0x1F: case 0x20:
            case 0x21: case 0x22: case 0x23: case 0x24:
            case 0x25: case 0x26:
                break;
        }
    }

    // ── 浇水状态更新 ─────────────────────────────────────────────
    // 已浇水(2) → 第二天变耕好(1)
    if (GetUnk0() == 2) unk_00_00 = 1;

    // ── 随机事件（杂草/石头出现、作物枯萎等）────────────────────
    Unk_080E8CC4 const * unk;
    switch (weather) {
        case 0: case 1: case 2: default:
            unk = &gUnk_080E8CC4[date.season][weather == 0];
            break;
        case 3: unk = &gUnk_080E8D04; break;  // 台风
        case 4: unk = &gUnk_080E8D0C; break;  // 暴雪
    }

    if (GetUnk8() != 0) {
        if (GetUnk8() == 1) {
            // 发芽阶段的作物可能枯萎
            u32 r1 = (rand() >> 3) & 0xFF;
            if (r1 < unk->unk_07)
                unk_00_08 = 0;  // 枯萎
        } else if (GetUnk2() == 0x18) {
            // 木材可能变成树桩
            u32 r1 = (rand() >> 3) & 0xFF;
            if (r1 < unk->unk_00)
                method_0800A134(0x19, 8);
        }
    } else if (GetUnk0() == 0 || GetUnk0() == 3) {
        // 空地可能长杂草/石头/树枝
        int r1 = (rand() >> 3) & 0xFF;
        if (r1 < unk->unk_04)
            method_0800A134(0x15, 8);       // 长杂草
        else if (r1 < unk->unk_05 + unk->unk_04)
            method_0800A134(0x16, 8);       // 长石头
        else if (r1 < unk->unk_06 + unk->unk_05 + unk->unk_04)
            method_0800A134(0x17, 8);       // 长树枝
    } else if (GetUnk0() == 1) {
        // 耕好的地可能恢复普通状态
        int r1 = (rand() >> 3) & 0xFF;
        if (r1 < unk->unk_01)
            method_0800A120(0);             // 恢复普通
        else if (r1 < unk->unk_02 + unk->unk_01)
            method_0800A134(0x15, 8);       // 长杂草
        else if (r1 < unk->unk_03 + unk->unk_02 + unk->unk_01)
            method_0800A134(0x16, 8);       // 长石头
    }

    // ── 浇水判定 ─────────────────────────────────────────────────
    // 下雨→自动浇水，晴天→耕好的地变干
    if (weather == 0) {
        if (GetUnk0() == 2) method_0800A120(1);  // 晴天：浇水状态变耕好
    } else {
        if (GetUnk0() == 1) method_0800A120(2);  // 下雨：自动浇水
    }
}

// ═══════════════════════════════════════════════════════════════════════════════
//  换季处理
// ═══════════════════════════════════════════════════════════════════════════════
// 季节变更时调用，清除过季作物
void FieldPlot::method_0800AB08(Season season)
{
    switch (season) {
        case 0:  // ── 春季到来 ─────────────────────────────────────
            method_0800A120(0);
            if (GetUnk8() != 0) {
                switch (unk_00_02) {
                    case 0x14: // 牧草重新生长
                        unk_00_08 = 7; unk_00_00 = 1; unk_00_0C = 0; break;
                    case 0x00: case 0x01: case 0x02: case 0x03:
                    case 0x04: case 0x05: case 0x06: case 0x07:
                    case 0x08: case 0x09: case 0x0A: case 0x0B:
                    case 0x0C: case 0x0D: case 0x0E: case 0x0F:
                    case 0x10: case 0x11: case 0x12: case 0x13:
                    case 0x15:
                        unk_00_08 = 0; break;  // 非春季作物死亡
                    case 0x16: case 0x17: case 0x18: case 0x19:
                    case 0x1A: case 0x1B: case 0x1C: case 0x1D:
                    case 0x1E: case 0x1F: case 0x20: case 0x21:
                    case 0x22: case 0x23: case 0x24: case 0x25:
                    case 0x26: break;  // 永久物（石头/木材等）保留
                }
            }
            if (unk_00_00 == 0 && unk_00_08 == 0) {
                if (((rand() >> 3) & 0xFF) < 10)
                    method_0800A134(0x15, 8);  // 长杂草
            }
            break;

        case 1:  // ── 夏季到来 ─────────────────────────────────────
            if (GetUnk8() != 0) {
                switch (unk_00_02) {
                    // 春作物枯萎
                    case 0x00: case 0x01: case 0x02: case 0x03:
                    case 0x04: case 0x0F: case 0x13:
                        if (GetUnk8() == 1) unk_00_08 = 0;
                        else unk_00_08 = 6;
                        unk_00_00 = 1; break;
                    // 夏作物保留
                    case 0x05: case 0x06: case 0x07: case 0x08:
                    case 0x09: case 0x0A: case 0x0B: case 0x0C:
                    case 0x0D: case 0x0E: case 0x10: case 0x11:
                    case 0x12: unk_00_08 = 0; unk_00_00 = 1; break;
                    // 永久物保留
                    case 0x14: case 0x15: case 0x16: case 0x17:
                    case 0x18: case 0x19: case 0x1A: case 0x1B:
                    case 0x1C: case 0x1D: case 0x1E: case 0x1F:
                    case 0x20: case 0x21: case 0x22: case 0x23:
                    case 0x24: case 0x25: case 0x26: break;
                }
            }
            break;

        case 2:  // ── 秋季到来 ─────────────────────────────────────
            if (GetUnk8() != 0) {
                switch (unk_00_02) {
                    case 0x05: case 0x06: case 0x07: case 0x08:
                    case 0x09: case 0x10:
                        if (GetUnk8() == 1) unk_00_08 = 0;
                        else unk_00_08 = 6;
                        unk_00_00 = 1; break;
                    case 0x00: case 0x01: case 0x02: case 0x03:
                    case 0x04: case 0x0F: case 0x0A: case 0x0B:
                    case 0x0C: case 0x0D: case 0x0E: case 0x11:
                    case 0x12: case 0x13:
                        unk_00_08 = 0; unk_00_00 = 1; break;
                    case 0x14: case 0x15: case 0x16: case 0x17:
                    case 0x18: case 0x19: case 0x1A: case 0x1B:
                    case 0x1C: case 0x1D: case 0x1E: case 0x1F:
                    case 0x20: case 0x21: case 0x22: case 0x23:
                    case 0x24: case 0x25: case 0x26: break;
                }
            }
            break;

        case 3:  // ── 冬季到来 ─────────────────────────────────────
            unk_00_00 = 3;  // 土地硬化（冬天不能耕种）
            if (GetUnk8() != 0) {
                switch (unk_00_02) {
                    case 0x14: // 牧草变枯萎
                        unk_00_08 = 7; unk_00_0C = 0; break;
                    case 0x00: case 0x0F: case 0x05: case 0x0A:
                    case 0x01: case 0x02: case 0x03: case 0x04:
                    case 0x06: case 0x07: case 0x08: case 0x09:
                    case 0x0B: case 0x0C: case 0x0D: case 0x0E:
                    case 0x10: case 0x11: case 0x12: case 0x13:
                    case 0x15: unk_00_08 = 0; break;  // 所有作物死亡
                    case 0x16: case 0x17: case 0x18: case 0x19:
                    case 0x1A: case 0x1B: case 0x1C: case 0x1D:
                    case 0x1E: case 0x1F: case 0x20: case 0x21:
                    case 0x22: case 0x23: case 0x24: case 0x25:
                    case 0x26: break;  // 永久物保留
                }
            }
            break;
    }
}

// ── 获取当前生长阶段对应的图形数据 ──────────────────────────────────
void const * FieldPlot::method_0800AF20() const {
    switch (GetUnk0_2()) {
        case 0: return gUnk_086D6518;  // 普通
        case 1: return gUnk_086D6520;  // 耕好
        case 2: return gUnk_086D6528;  // 已浇水
        case 3: return nullptr;         // 硬化（无图形）
        default: return nullptr;
    }
}

// ── 获取调色板/颜色数据 ────────────────────────────────────────────
Unk_Something const * FieldPlot::method_0800AF5C(
    FieldPlot const * arg_1, FieldPlot const * arg_2) const
{
    Unk_Something const * ip = gUnk_080E93F8[GetUnk2()].unk_00;
    fu8 r4 = UINT8_MAX;

    if (GetUnk8() == 0) return &gUnk_086D6458;
    if (GetUnk8() == 1) return &gUnk_086D6608;

    if (GetUnk2() != 0x14) {
        switch (GetUnk8()) {
            case 2: r4 = gUnk_080E93F8[GetUnk2()].unk_04; break;
            case 3: r4 = gUnk_080E93F8[GetUnk2()].unk_05; break;
            case 4: r4 = gUnk_080E93F8[GetUnk2()].unk_06; break;
            case 5: r4 = gUnk_080E93F8[GetUnk2()].unk_07; break;
            case 6: r4 = gUnk_080E93F8[GetUnk2()].unk_08; break;
            case 8: r4 = (GetUnk0() != 3) ? 0 : 1; break;
        }
    } else if (GetUnk8() == 0x07) {
        r4 = 0x0C;
    } else {
        switch (GetUnk8()) {
            case 0x03: r4 = 0; break;
            case 0x04: r4 = 4; break;
            case 0x05: r4 = 8; break;
        }
        // 邻居状态影响颜色选择
        if (arg_1 == nullptr || arg_1->GetUnk2() != 0x14 ||
            arg_1->GetUnk8() == 7 || arg_1->GetUnk8() < GetUnk8()) {
            if (!(arg_2 == nullptr || arg_2->GetUnk2() != 0x14 ||
                  arg_2->GetUnk8() == 7 || arg_2->GetUnk8() < GetUnk8()))
                r4 = r4 + 1;
        } else {
            if (arg_2 == nullptr || arg_2->GetUnk2() != 0x14 ||
                arg_2->GetUnk8() == 7 || arg_2->GetUnk8() < GetUnk8())
                r4 = r4 + 2;
            else
                r4 = r4 + 3;
        }
    }
    return ip + r4;
}

// ═══════════════════════════════════════════════════════════════════════════════
// 【出货箱系统】ShippingBin
// ═══════════════════════════════════════════════════════════════════════════════
// 管理出货箱的累计金额、出货统计、图鉴解锁。
// 游戏会记录每种物品的总出货量，并用于解锁"全部出货"的成就。
//
// ★ 想改出货价格 → 去改 data/item/product.def
// ★ 想改初始显示的物品（图鉴默认开启的）→ 改下面的 sStartingDisplayedProductList
// ═══════════════════════════════════════════════════════════════════════════════

#include "shipping_bin.hh"
#include "unknown_inlines.hh"

// ── 初始显示的出货图鉴 ───────────────────────────────────────────────────
// 游戏开始时，这些物品的出货图鉴是默认开启的（不需要出货一次才显示）
static u8 const sStartingDisplayedProductList[] =
{
    // 【蔬菜作物】初始显示 13 种
    PRODUCT_TURNIP,           // 萝卜
    PRODUCT_POTATO,           // 土豆
    PRODUCT_CUCUMBER,         // 黄瓜
    PRODUCT_CABBAGE,          // 卷心菜
    PRODUCT_TOMATO,           // 番茄
    PRODUCT_CORN,             // 玉米
    PRODUCT_ONION,            // 洋葱
    PRODUCT_PINEAPPLE,        // 菠萝
    PRODUCT_EGGPLANT,         // 茄子
    PRODUCT_CARROT,           // 胡萝卜
    PRODUCT_SWEET_POTATO,     // 红薯
    PRODUCT_GREEN_PEPPER,     // 青椒

    // 【鸡蛋品质】3 种
    PRODUCT_REGULAR_QUALITY_EGG,  // 普通蛋
    PRODUCT_GOOD_QUALITY_EGG,     // 优质蛋
    PRODUCT_HIGH_QUALITY_EGG,     // 高级蛋

    // 【牛奶品质】3 种
    PRODUCT_MILK_S,   // S 型牛奶
    PRODUCT_MILK_M,   // M 型牛奶
    PRODUCT_MILK_L,   // L 型牛奶

    // 【羊毛品质】3 种
    PRODUCT_WOOL_S,   // S 型羊毛
    PRODUCT_WOOL_M,   // M 型羊毛
    PRODUCT_WOOL_L,   // L 型羊毛

    PRODUCT_CHOCOLATE,  // 巧克力
};

// ── 作物列表（用于判断"全部作物出货"成就）────────────────────────────
static u8 const sCropProductList[] =
{
    PRODUCT_TURNIP,       // 萝卜
    PRODUCT_POTATO,       // 土豆
    PRODUCT_CUCUMBER,     // 黄瓜
    PRODUCT_CABBAGE,      // 卷心菜
    PRODUCT_STRAWBERRY,   // 草莓
    PRODUCT_TOMATO,       // 番茄
    PRODUCT_CORN,         // 玉米
    PRODUCT_ONION,        // 洋葱
    PRODUCT_PINEAPPLE,    // 菠萝
    PRODUCT_PUMPKIN,      // 南瓜
    PRODUCT_EGGPLANT,     // 茄子
    PRODUCT_CARROT,       // 胡萝卜
    PRODUCT_SWEET_POTATO, // 红薯
    PRODUCT_GREEN_PEPPER, // 青椒
    PRODUCT_SPINACH,      // 菠菜
};

// ── 矿石列表（用于判断"全部矿石出货"成就）────────────────────────────
static u8 const sMineralProductList[] =
{
    PRODUCT_JUNK_ORE,      // 废矿石
    PRODUCT_COPPER,        // 铜
    PRODUCT_SILVER,        // 银
    PRODUCT_GOLD,          // 金
    PRODUCT_MYSTRILE,      // 秘银
    PRODUCT_ORICHALC,      // 奥利哈刚
    PRODUCT_ADAMANTITE,    // 金刚石
    PRODUCT_MYTHIC_STONE,  // 贤者之石
    PRODUCT_PINK_DIAMOND,  // 粉红钻石
    PRODUCT_ALEXANDRITE,   // 亚历山大石
    PRODUCT_MOON_STONE,    // 月亮石
    PRODUCT_SAND_ROSE,     // 沙漠玫瑰
    PRODUCT_DIAMOND,       // 钻石
    PRODUCT_EMERALD,       // 祖母绿
    PRODUCT_RUBY,          // 红宝石
    PRODUCT_TOPAZ,         // 黄玉
    PRODUCT_PERIDOT,       // 橄榄石
    PRODUCT_FLUORITE,      // 萤石
    PRODUCT_AGATE,         // 玛瑙
    PRODUCT_AMETHYST,      // 紫水晶
};

// ── 构造函数 ─────────────────────────────────────────────────────────────
// 初始化出货箱，解锁初始显示的图鉴物品
ShippingBin::ShippingBin()
    : value_shipped(0)    // ★ 累计出货金额（只增不减）
{
    // 开启初始图鉴
    for (u32 i = 0; i < ARRAY_COUNT(sStartingDisplayedProductList); ++i)
        product_stats[sStartingDisplayedProductList[i]].ForceEnableDisplay();
}

// ── 获取累计出货金额 ──────────────────────────────────────────────────
u32 ShippingBin::GetValueShipped() const { return value_shipped; }

// ── 查询物品的出货图鉴是否已解锁 ────────────────────────────────────
bool ShippingBin::IsDisplayEnabled(int product_id) const {
    if (product_id < NUM_PRODUCTS)
        return product_stats[product_id].IsDisplayEnabled();
    return false;
}

// ── 查询某物品的总出货量 ─────────────────────────────────────────────
u32 ShippingBin::GetAmountShipped(int product_id) const {
    if (product_id < NUM_PRODUCTS)
        return product_stats[product_id].GetAmountShipped();
    return 0;
}

// ── 判断是否每种物品都出货过至少一个 ───────────────────────────────
bool ShippingBin::HasShippedOneOfEachProduct() const {
    for (u32 i = 0; i < NUM_PRODUCTS; ++i) {
        if (!product_stats[i].IsDisplayEnabled() || product_stats[i].GetAmountShipped() == 0)
            return false;
    }
    return true;
}

// ── 判断是否每种作物都出货过至少一个 ───────────────────────────────
bool ShippingBin::HasShippedOneOfEachCrop() const {
    for (u32 i = 0; i < ARRAY_COUNT(sCropProductList); ++i) {
        u32 product_id = sCropProductList[i];
        if (!product_stats[product_id].IsDisplayEnabled() || product_stats[product_id].GetAmountShipped() == 0)
            return false;
    }
    return true;
}

// ── 判断是否每种矿石都出货过至少一个 ───────────────────────────────
bool ShippingBin::HasShippedOneOfEachMineral() const {
    for (u32 i = 0; i < ARRAY_COUNT(sMineralProductList); ++i) {
        u32 product_id = sMineralProductList[i];
        if (!product_stats[product_id].IsDisplayEnabled() || product_stats[product_id].GetAmountShipped() == 0)
            return false;
    }
    return true;
}

// ── 出货动作 ────────────────────────────────────────────────────────────
// 每天出货箱结算时调用，将物品卖出并累加金额
void ShippingBin::Ship(Product const & slot) {
    u32 price = slot.GetPrice();   // ★ 价格从 product.def 读取

    if (price > 0) {
        product_stats[slot.GetId()].ShipOne();  // 记录出货次数

        // 累加金额（上限 MAX_VALUE_TRACKED）
        u32 old_value_shipped = GetValueShippedInl(*this);
        value_shipped = old_value_shipped + min_inl<u32>(MAX_VALUE_TRACKED - old_value_shipped, price);
    }
}

void ShippingBin::ResetValueShipped() { value_shipped = 0; }

// 强制解锁某个物品的出货图鉴
void ShippingBin::ForceEnableDisplay(int product_id) {
    if (product_id < NUM_PRODUCTS)
        product_stats[product_id].ForceEnableDisplay();
}

// ═══════════════════════════════════════════════════════════════════════════════
//  出货统计条目 StatEnt（每种物品一个）
// ═══════════════════════════════════════════════════════════════════════════════

ShippingBin::StatEnt::StatEnt() {
    amount_shipped = 0;     // 出货数量
    display_enabled = false; // 图鉴是否解锁
}

bool ShippingBin::StatEnt::IsDisplayEnabled() const { return display_enabled; }

u32 ShippingBin::StatEnt::GetAmountShipped() const {
    if (display_enabled) return amount_shipped;
    return 0;
}

void ShippingBin::StatEnt::ShipOne() {
    if (!display_enabled) display_enabled = true;
    if (amount_shipped < MAX_AMOUNT_TRACKED) amount_shipped++;
}

void ShippingBin::StatEnt::ForceEnableDisplay() {
    if (!display_enabled) display_enabled = true;
}

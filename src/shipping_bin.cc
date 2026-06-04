// 📦 出货箱 - 出货箱逻辑
//
// 管理出货记录：每种物品的出货数量、显示状态、总营业额。
// 出货箱位于农场、畜棚、鸡舍各有一个，共享同一套统计数据。
// 扎克每天下午来收货，按出货价格结算金钱。

#include "shipping_bin.hh"

#include "unknown_inlines.hh"

// clang-format off

/**
 * sStartingDisplayedProductList — 初始显示的物品列表
 * 新游戏开始时，出货箱中默认显示这些物品的出货记录（即使还没出货过）。
 * 主要是初期的农作物和基本的畜产品。
 */
static u8 const sStartingDisplayedProductList[] =
{
    PRODUCT_TURNIP,
    PRODUCT_POTATO,
    PRODUCT_CUCUMBER,
    PRODUCT_CABBAGE,
    PRODUCT_TOMATO,
    PRODUCT_CORN,
    PRODUCT_ONION,
    PRODUCT_PINEAPPLE,
    PRODUCT_EGGPLANT,
    PRODUCT_CARROT,
    PRODUCT_SWEET_POTATO,
    PRODUCT_GREEN_PEPPER,
    PRODUCT_REGULAR_QUALITY_EGG,
    PRODUCT_GOOD_QUALITY_EGG,
    PRODUCT_HIGH_QUALITY_EGG,
    PRODUCT_MILK_S,
    PRODUCT_MILK_M,
    PRODUCT_MILK_L,
    PRODUCT_WOOL_S,
    PRODUCT_WOOL_M,
    PRODUCT_WOOL_L,
    PRODUCT_CHOCOLATE,
};

/**
 * sCropProductList — 农作物列表
 * 检查"全部作物出货"成就时使用的物品列表。
 */
static u8 const sCropProductList[] =
{
    PRODUCT_TURNIP,
    PRODUCT_POTATO,
    PRODUCT_CUCUMBER,
    PRODUCT_CABBAGE,
    PRODUCT_STRAWBERRY,
    PRODUCT_TOMATO,
    PRODUCT_CORN,
    PRODUCT_ONION,
    PRODUCT_PINEAPPLE,
    PRODUCT_PUMPKIN,
    PRODUCT_EGGPLANT,
    PRODUCT_CARROT,
    PRODUCT_SWEET_POTATO,
    PRODUCT_GREEN_PEPPER,
    PRODUCT_SPINACH,
};

/**
 * sMineralProductList — 矿物列表
 * 检查"全部矿物出货"成就时使用的物品列表。
 */
static u8 const sMineralProductList[] =
{
    PRODUCT_JUNK_ORE,
    PRODUCT_COPPER,
    PRODUCT_SILVER,
    PRODUCT_GOLD,
    PRODUCT_MYSTRILE,
    PRODUCT_ORICHALC,
    PRODUCT_ADAMANTITE,
    PRODUCT_MYTHIC_STONE,
    PRODUCT_PINK_DIAMOND,
    PRODUCT_ALEXANDRITE,
    PRODUCT_MOON_STONE,
    PRODUCT_SAND_ROSE,
    PRODUCT_DIAMOND,
    PRODUCT_EMERALD,
    PRODUCT_RUBY,
    PRODUCT_TOPAZ,
    PRODUCT_PERIDOT,
    PRODUCT_FLUORITE,
    PRODUCT_AGATE,
    PRODUCT_AMETHYST,
};

// clang-format on

/**
 * ShippingBin 构造函数
 * 初始化总营业额为 0，并设置初始显示的物品列表。
 */
ShippingBin::ShippingBin()
    : value_shipped(0)
{
    for (u32 i = 0; i < ARRAY_COUNT(sStartingDisplayedProductList); ++i)
        product_stats[sStartingDisplayedProductList[i]].ForceEnableDisplay();
}

/**
 * GetValueShipped — 获取总营业额
 * @return 从游戏开始到目前为止的累计出货金额
 */
u32 ShippingBin::GetValueShipped() const
{
    return value_shipped;
}

/**
 * IsDisplayEnabled — 检查指定物品的出货记录是否可见
 * @param product_id 物品 ID
 * @return true 表示该物品已在出货列表中显示
 */
bool ShippingBin::IsDisplayEnabled(int product_id) const
{
    if (product_id < NUM_PRODUCTS)
        return product_stats[product_id].IsDisplayEnabled();

    return false;
}

/**
 * GetAmountShipped — 获取指定物品的累计出货数量
 * @param product_id 物品 ID
 * @return 出货数量（仅当该物品的显示已启用时有效）
 */
u32 ShippingBin::GetAmountShipped(int product_id) const
{
    if (product_id < NUM_PRODUCTS)
        return product_stats[product_id].GetAmountShipped();

    return 0;
}

/**
 * HasShippedOneOfEachProduct — 是否每种物品至少出货过一个
 * 用于成就/奖杯判定：全部出货。
 * @return true 表示已达成"全物品出货"
 */
bool ShippingBin::HasShippedOneOfEachProduct() const
{
    for (u32 i = 0; i < NUM_PRODUCTS; ++i)
    {
        if (!product_stats[i].IsDisplayEnabled() || product_stats[i].GetAmountShipped() == 0)
            return false;
    }

    return true;
}

/**
 * HasShippedOneOfEachCrop — 是否每种农作物至少出货过一个
 * @return true 表示已达成"全作物出货"
 */
bool ShippingBin::HasShippedOneOfEachCrop() const
{
    for (u32 i = 0; i < ARRAY_COUNT(sCropProductList); ++i)
    {
        u32 product_id = sCropProductList[i];

        if (!product_stats[product_id].IsDisplayEnabled() || product_stats[product_id].GetAmountShipped() == 0)
            return false;
    }

    return true;
}

/**
 * HasShippedOneOfEachMineral — 是否每种矿物至少出货过一个
 * @return true 表示已达成"全矿物出货"
 */
bool ShippingBin::HasShippedOneOfEachMineral() const
{
    for (u32 i = 0; i < ARRAY_COUNT(sMineralProductList); ++i)
    {
        u32 product_id = sMineralProductList[i];

        if (!product_stats[product_id].IsDisplayEnabled() || product_stats[product_id].GetAmountShipped() == 0)
            return false;
    }

    return true;
}

// 用于确保 ShippingBin::Ship 的编译匹配
// 可以用 GetValueShipped 替代
static inline u32 GetValueShippedInl(ShippingBin const & self)
{
    return self.value_shipped;
}

/**
 * Ship — 将一个物品放入出货箱
 *
 * 获取物品价格，累加到总营业额中。
 * 总营业额上限为 MAX_VALUE_TRACKED（防止溢出）。
 * @param slot 要出货的物品引用
 */
void ShippingBin::Ship(Product const & slot)
{
    u32 price = slot.GetPrice();

    if (price > 0)
    {
        product_stats[slot.GetId()].ShipOne();

        u32 old_value_shipped = GetValueShippedInl(*this);
        value_shipped = old_value_shipped + min_inl<u32>(MAX_VALUE_TRACKED - old_value_shipped, price);
    }
}

/**
 * ResetValueShipped — 重置总营业额
 * 用于新游戏或读档时初始化。
 */
void ShippingBin::ResetValueShipped()
{
    value_shipped = 0;
}

/**
 * ForceEnableDisplay — 强制显示指定物品的出货记录
 *
 * 在补丁或调试时使用，让原本未解锁的物品记录提前显示。
 * @param product_id 物品 ID
 */
void ShippingBin::ForceEnableDisplay(int product_id)
{
    if (product_id < NUM_PRODUCTS)
        product_stats[product_id].ForceEnableDisplay();
}

/**
 * StatEnt 构造函数
 * 初始化出货数量为 0，显示状态为关闭。
 */
ShippingBin::StatEnt::StatEnt()
{
    amount_shipped = 0;
    display_enabled = false;
}

/**
 * IsDisplayEnabled — 检查该出货记录是否已解锁显示
 * @return true 表示在出货列表中可见
 */
bool ShippingBin::StatEnt::IsDisplayEnabled() const
{
    return display_enabled;
}

/**
 * GetAmountShipped — 获取该物品的出货次数
 * @return 出货次数（仅当显示已启用时返回实际值，否则返回 0）
 */
u32 ShippingBin::StatEnt::GetAmountShipped() const
{
    if (display_enabled)
        return amount_shipped;

    return 0;
}

/**
 * ShipOne — 记录一次出货
 *
 * 第一次出货时自动解锁显示，并在不超过上限的情况下累加出货次数。
 */
void ShippingBin::StatEnt::ShipOne()
{
    if (!display_enabled)
        display_enabled = true;

    if (amount_shipped < MAX_AMOUNT_TRACKED)
        amount_shipped++;
}

/**
 * ForceEnableDisplay — 强制解锁显示该出货记录
 */
void ShippingBin::StatEnt::ForceEnableDisplay()
{
    if (!display_enabled)
        display_enabled = true;
}

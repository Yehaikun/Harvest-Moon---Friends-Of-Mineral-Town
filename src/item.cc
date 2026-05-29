// ═══════════════════════════════════════════════════════════════════════════════
// 【物品系统】Item
// ═══════════════════════════════════════════════════════════════════════════════
// 管理游戏中的所有物品：工具、食物（食材/料理）、装饰品（花/矿石/家具）、
// 出货品。物品的实际数据定义在 data/item/ 目录下的 .def 文件中。
//
// ★ 想改物品价格 → 修改 data/item/product.def
// ★ 想改物品回复体力 → 修改 data/item/food.def
// ★ 想改物品名字 → 修改对应的 .def 文件
// ═══════════════════════════════════════════════════════════════════════════════

#include "item.hh"
#include <algorithm>

// ── 内在数据结构 ─────────────────────────────────────────────────────────

// 【工具信息】（如镰刀、锄头、洒水壶等）
struct ToolInfo
{
    /* +00 */ char const * name;       // 工具名称
    /* +04 */ u16 icon_id;             // 图标 ID
    /* +08 */ char const * desc;       // 描述文字
};

// 【食物信息】（如鸡蛋、牛奶、料理等）
struct FoodInfo
{
    /* +00 */ char const * name;       // 名称
    /* +04 */ bool is_drink : 1;       // 是否为饮品（使用动作不同）
    /* +05 */ i8 stamina;              // ★ 回复体力值（负=消耗）
    /* +06 */ i8 fatigue;              // ★ 回复疲劳值（负=减少疲劳）
    /* +08 */ u16 icon_id;             // 图标 ID
    /* +0C */ char const * desc;       // 描述
};

// 【装饰品信息】（花、矿石、家具等）
struct ArticleInfo
{
    /* +00 */ char const * name;
    /* +04 */ u16 icon_id;
    /* +08 */ char const * desc;
};

// 【出货品信息】（决定了卖出价格）
struct ProductInfo
{
    enum Kind
    {
        KIND_FOOD,      // 食品类（对应 Food 枚举）
        KIND_ARTICLE,   // 物品类（对应 Article 枚举）
    };

    /* +00 */ u32 price : 15;   // ★ 卖出价格（上限 32767）
    /* +01 */ u32 kind : 1;     // 种类（食品/物品）
    /* +02 */ u32 item : 8;     // 对应的 Food/Article ID
};

// 实际数据定义在 data/item/ 目录下
// ★ 想改价格就去改 data/item/product.def
extern ToolInfo const gToolInfo[];
extern FoodInfo const gFoodInfo[];
extern ArticleInfo const gArticleInfo[];
extern ProductInfo const gProductInfo[];

// ── ID 合法性检查 ─────────────────────────────────────────────────────────
static inline bool IsValidToolId(u8 id)    { return id < NUM_TOOLS; }
static inline bool IsValidFoodId(u8 id)    { return id < NUM_FOODS; }
static inline bool IsValidArticleId(u8 id) { return id < NUM_ARTICLES; }
static inline bool IsValidProductId(u8 id) { return id < NUM_PRODUCTS; }

// ═══════════════════════════════════════════════════════════════════════════════
//  工具系统 Tool
// ═══════════════════════════════════════════════════════════════════════════════

Tool::Tool(u32 a_id) { id = a_id; }
int Tool::GetId() const { return id; }

char const * Tool::GetName() const {
    if (IsValidToolId(id)) return gToolInfo[id].name;
    return "Broken Tool";
}

u16 Tool::GetIconId() const {
    if (IsValidToolId(id)) return gToolInfo[id].icon_id;
    return 457; // Turnip（默认图标）
}

static inline char const * GetToolDescById(u32 id) {
    if (gToolInfo[id].desc != nullptr) return gToolInfo[id].desc;
    return "No Explanation";
}

char const * Tool::GetDesc() const {
    if (IsValidToolId(id)) return GetToolDescById(id);
    return "No Explanation";
}

// ═══════════════════════════════════════════════════════════════════════════════
//  工具堆叠 ToolStack
// ═══════════════════════════════════════════════════════════════════════════════

ToolStack::ToolStack() : Tool(TOOL_NONE) { amount = 0; }

ToolStack::ToolStack(Tool kind, u32 a_amount) : Tool(kind) {
    if (a_amount != 0) {
        amount = *(u8 *)&std::min<u32>(MAX_AMOUNT, a_amount);
    } else {
        amount = 1;
    }
}

Tool ToolStack::GetTool() const {
    if (amount != 0) return *this;
    return Tool(TOOL_NONE);
}

bool ToolStack::IsEmpty() const { return amount == 0; }

u32 ToolStack::GetAmount() const {
    if (amount != 0) return amount;
    return 0;
}

void ToolStack::AddAmount(u32 a_amount) {
    if (amount != 0)
        amount = std::min<u32>(MAX_AMOUNT, amount + a_amount);
}

void ToolStack::SubtractAmount(u32 a_amount) {
    if (amount != 0) {
        if (amount <= a_amount) amount = 0;
        else amount -= a_amount;
    }
}

// ═══════════════════════════════════════════════════════════════════════════════
//  食物系统 Food
// ═══════════════════════════════════════════════════════════════════════════════

Food::Food(u32 a_id) {
    id = a_id;
    stamina_bonus = 0;   // 额外体力加成（可从料理获得）
    fatigue_bonus = 0;   // 额外疲劳减少
}

int Food::GetId() const { return id; }

char const * Food::GetName() const {
    if (IsValidFoodId(id)) return gFoodInfo[id].name;
    return "Broken Food";
}

u16 Food::GetIconId() const {
    if (IsValidFoodId(id)) return gFoodInfo[id].icon_id;
    return 428; // Stones（默认图标）
}

// ★ 改这里影响吃食物回复的体力值
int Food::GetStaminaGain() const {
    if (IsValidFoodId(id)) return gFoodInfo[id].stamina + stamina_bonus;
    return -100;   // 不能吃的东西扣 100 体力
}

int Food::GetFatigueGain() const {
    if (IsValidFoodId(id)) return gFoodInfo[id].fatigue + fatigue_bonus;
    return +100;   // 不能吃的东西加 100 疲劳
}

int Food::GetStaminaBonus() const {
    if (IsValidFoodId(id)) return stamina_bonus;
    return -100;
}

int Food::GetFatigueBonus() const {
    if (IsValidFoodId(id)) return fatigue_bonus;
    return +100;
}

bool Food::IsDrink() const {
    if (IsValidFoodId(id)) return gFoodInfo[id].is_drink;
    return false;
}

char const * Food::GetDesc() const {
    if (IsValidFoodId(id)) {
        if (gFoodInfo[id].desc != nullptr) return gFoodInfo[id].desc;
    }
    return "No Explanation";
}

// 给食物添加额外属性（用于料理加成）
void Food::AddBonuses(i8 stamina_amount, i8 fatigue_amount) {
    int total;
    if (IsValidFoodId(id)) {
        total = stamina_bonus + stamina_amount;
        if (total < -128) total = -128;
        else if (total > 127) total = 127;
        stamina_bonus = total;

        total = fatigue_bonus + fatigue_amount;
        if (total < -128) total = -128;
        else if (total > 127) total = 127;
        fatigue_bonus = total;
    }
}

// ═══════════════════════════════════════════════════════════════════════════════
//  食物堆叠 FoodStack
// ═══════════════════════════════════════════════════════════════════════════════

FoodStack::FoodStack() : Food(FOOD_NONE) { amount = 0; }

FoodStack::FoodStack(Food food, u32 a_amount) : Food(food) {
    if (a_amount != 0) {
        amount = *(u8 *)&std::min<u32>(MAX_AMOUNT, a_amount);
    } else {
        amount = 1;
    }
}

Food FoodStack::GetFood() const {
    if (amount > 0) return *this;
    return Food(FOOD_NONE);
}

bool FoodStack::IsEmpty() const { return amount == 0; }
u32 FoodStack::GetAmount() const { return (amount > 0) ? amount : 0; }

void FoodStack::AddAmount(u32 a_amount) {
    if (amount != 0)
        amount = std::min<u32>(MAX_AMOUNT, amount + a_amount);
}

void FoodStack::SubtractAmount(u32 a_amount) {
    if (amount != 0) {
        if (amount <= a_amount) amount = 0;
        else amount -= a_amount;
    }
}

// ═══════════════════════════════════════════════════════════════════════════════
//  装饰品系统 Article（花、矿石、家具、信件等）
// ═══════════════════════════════════════════════════════════════════════════════

Article::Article(u32 a_id) { id = a_id; }
int Article::GetId() const { return id; }

char const * Article::GetName() const {
    if (IsValidArticleId(id)) return gArticleInfo[id].name;
    return "Broken Article";
}

u16 Article::GetIconId() const {
    if (IsValidArticleId(id)) return gArticleInfo[id].icon_id;
    return 457;
}

// ★ 以下物品不能被丢弃（剧情关键物品）
bool Article::CanBeDiscarded() const {
    switch (id) {
        default:
            return true;

        case ARTICLE_HARVEST_GODDESS_JEWEL:  // 女神之玉
        case ARTICLE_KAPPA_JEWEL:             // 河童之玉
        case ARTICLE_JEWEL_OF_TRUTH:          // 真实之玉
        case ARTICLE_KARENS_WINE:             // 卡莲的酒
        case ARTICLE_POPURIS_MUD_BALL:        // 珀布莉的泥团
        case ARTICLE_ANNS_MUSIC_BOX:          // 安的音乐盒
        case ARTICLE_MARYS_GREAT_BOOK:        // 玛丽的大书
        case ARTICLE_ELLIS_PRESSED_FLOWER:    // 艾利的压花
        case ARTICLE_FRISBEE:                 // 飞盘
            return false;
    }
}

char const * Article::GetDesc() const {
    if (IsValidArticleId(id) && gArticleInfo[id].desc != nullptr)
        return gArticleInfo[id].desc;
    return "No Explanation";
}

// ═══════════════════════════════════════════════════════════════════════════════
//  装饰品堆叠 ArticleStack
// ═══════════════════════════════════════════════════════════════════════════════

ArticleStack::ArticleStack() : Article(ARTICLE_NONE) { amount = 0; }
ArticleStack::ArticleStack(Article article, u32 a_amount) : Article(article) {
    if (a_amount != 0) {
        amount = *(u8 *)&std::min<u32>(MAX_AMOUNT, a_amount);
    } else {
        amount = 1;
    }
}

Article ArticleStack::GetArticle() const {
    if (amount != 0) return *this;
    return Article(ARTICLE_NONE);
}

bool ArticleStack::IsEmpty() const { return amount == 0; }
u32 ArticleStack::GetAmount() const { return (amount != 0) ? amount : 0; }

void ArticleStack::AddAmount(u32 a_amount) {
    if (amount != 0)
        amount = std::min<u32>(MAX_AMOUNT, amount + a_amount);
}

void ArticleStack::SubtractAmount(u32 a_amount) {
    if (amount != 0) {
        if (amount <= a_amount) amount = 0;
        else amount -= a_amount;
    }
}

// ═══════════════════════════════════════════════════════════════════════════════
//  出货品系统 Product
// ═══════════════════════════════════════════════════════════════════════════════
// Product 是"可以被放进出货箱卖出"的东西。一个 Food 或 Article 在出货表里
// 有对应的 Product 条目时才能出货，价格在 product.def 中定义。

Product::Product()                  { id = PRODUCT_NONE; }
Product::Product(u32 a_id)         { id = a_id; }

// ★ 通过 Food 查找对应的 Product（用来查出货价）
Product::Product(Food food) {
    id = PRODUCT_NONE;
    u32 food_id = food.GetId();
    for (int i = 0; i < PRODUCT_NONE; i++) {
        ProductInfo const * info = gProductInfo + i;
        if (info->kind == ProductInfo::KIND_FOOD && info->item == food_id) {
            id = i;
            break;
        }
    }
}

Product::Product(Article article) {
    id = PRODUCT_NONE;
    u32 article_id = article.GetId();
    for (int i = 0; i < PRODUCT_NONE; ++i) {
        ProductInfo const * info = gProductInfo + i;
        if (info->kind == ProductInfo::KIND_ARTICLE && info->item == article_id) {
            id = i;
            break;
        }
    }
}

int Product::GetId() const { return id; }

// ★ 获取出货价格——改 data/item/product.def 就改这里
u32 Product::GetPrice() const {
    if (IsValidProductId(id)) return gProductInfo[id].price;
    return 0;
}

char const * Product::GetName() const {
    if (IsValidProductId(id)) {
        ProductInfo const * info = gProductInfo + id;
        if (info->kind == ProductInfo::KIND_FOOD)
            return Food(info->item).GetName();
        else
            return Article(info->item).GetName();
    }
    return "Broken Shipment";
}

u16 Product::GetIconId() const {
    if (IsValidProductId(id)) {
        ProductInfo const * info = gProductInfo + id;
        if (info->kind == ProductInfo::KIND_FOOD)
            return Food(info->item).GetIconId();
        else
            return Article(info->item).GetIconId();
    }
    return 0;
}

// ═══════════════════════════════════════════════════════════════════════════════
//  物品变体 ItemVariant（用于背包中未知类型的物品槽）
// ═══════════════════════════════════════════════════════════════════════════════

Tool ItemVariant::AsTool() const {
    return (kind == KIND_TOOL) ? Tool(id) : Tool(TOOL_NONE);
}

Food ItemVariant::AsFood() const {
    return (kind == KIND_FOOD) ? Food(id) : Food(FOOD_NONE);
}

Article ItemVariant::AsArticle() const {
    return (kind == KIND_ARTICLE) ? Article(id) : Article(ARTICLE_NONE);
}

// ═══════════════════════════════════════════════════════════════════════════════
//  物品的实际数据定义
// ═══════════════════════════════════════════════════════════════════════════════
// ★ 想改价格 → data/item/product.def
// ★ 想改回复量 → data/item/food.def
// ★ 想改名称/图标 → data/item/tool.def / food.def / article.def
// ═══════════════════════════════════════════════════════════════════════════════

ToolInfo const gToolInfo[] = {
#define o(tag, icon, name, desc) { (name), (icon), (desc) },
#include "data/item/tool.def"
#undef o
};

FoodInfo const gFoodInfo[] = {
#define o(tag, is_drink, stamina, fatigue, icon, name, desc) \
    { (name), (is_drink), (stamina), (fatigue), (icon), (desc) },
#include "data/item/food.def"
#undef o
};

ArticleInfo const gArticleInfo[] = {
#define o(tag, icon, name, desc) { (name), (icon), (desc) },
#include "data/item/article.def"
#undef o
};

ProductInfo const gProductInfo[] = {
#define o(tag, kind, price) { (price), (ProductInfo::KIND_##kind), (kind##_##tag) },
#include "data/item/product.def"
#undef o
};

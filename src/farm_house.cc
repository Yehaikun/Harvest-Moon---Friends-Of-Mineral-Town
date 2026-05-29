// ═══════════════════════════════════════════════════════════════════════════════
// 【自宅系统】FarmHouse
// ═══════════════════════════════════════════════════════════════════════════════
// 管理主角自宅的升级状态和所有家具。
//
// 自宅等级：
//   0 = 初始小木屋（只有床和电视）
//   1 = 扩建一次（增厨房、冰箱、收纳柜）
//   2 = 扩建两次（增浴室、大床、壁炉、可换窗户样式）
//
// ★ 想改升级条件 → 改 UpgradeHouseLevel() 和 AddBathroom() 等的 if 判断
// ★ 想开局就有大房子 → 改构造函数的 upgrade_level 初始值
// ═══════════════════════════════════════════════════════════════════════════════

#include "farm_house.hh"
#include <stdlib.h>

// ── 构造函数 ─────────────────────────────────────────────────────────────
// 游戏开始时自宅的默认状态
FarmHouse::FarmHouse()
    : upgrade_level(0),      // ★ 自宅等级（0=小 1=中 2=大）
      window_style(0),       // 窗户样式（升级后可选）
      mailbox_style(0),      // 信箱样式
      doghouse_style(0),     // 狗屋样式
      has_bathroom(false),   // 是否有浴室（等级2才有）
      has_fridge(false),     // ★ 是否有冰箱（等级1以上才有）
      has_shelf(false),      // ★ 是否有收纳柜（等级1以上才有）
      has_record_player(false), // 是否有唱片机
      has_large_bed(false),  // ★ 是否有大床（等级2才有，结婚后需要）
      has_carpet(false),     // 是否有地毯（等级1以上才有）
      has_vase(false),       // 是否有花瓶
      vase_article_id(ARTICLE_NONE), // 花瓶里插的花
      has_mirror(false),     // 是否有镜子
      has_clock(false),      // 是否有钟
      has_stocking(false),   // 是否有圣诞袜
      stocking_article_id(ARTICLE_NONE), // 圣诞袜里的礼物
      fireplace_lighted(false), // 壁炉是否点燃（冬季用）
      has_kitchen(false),        // ★ 是否有厨房
      has_kitchen_knife(false),      // 厨房菜刀
      has_kitchen_frying_pan(false), // 厨房平底锅
      has_kitchen_pot(false),        // 厨房锅
      has_kitchen_mixer(false),      // 厨房搅拌机
      has_kitchen_whisk(false),      // 厨房打蛋器
      has_kitchen_rolling_pin(false),// 厨房擀面杖
      has_kitchen_oven(false),       // 厨房烤箱
      has_kitchen_seasoning_set(false) // 厨房调味料
{
}

// ═══════════════════════════════════════════════════════════════════════════════
//  状态查询
// ═══════════════════════════════════════════════════════════════════════════════

u32   FarmHouse::GetUpgradeLevel() const     { return upgrade_level; }
u32   FarmHouse::GetWindowStyle() const      { return window_style; }
u32   FarmHouse::GetMailboxStyle() const     { return mailbox_style; }
u32   FarmHouse::GetDoghouseStyle() const    { return doghouse_style; }
bool  FarmHouse::HasBathroom() const         { return has_bathroom; }
bool  FarmHouse::HasLargeBed() const         { return has_large_bed; }
bool  FarmHouse::HasCarpet() const           { return has_carpet; }
bool  FarmHouse::HasVase() const             { return has_vase; }
u32   FarmHouse::GetVaseArticleId() const    { return vase_article_id; }
bool  FarmHouse::HasMirror() const           { return has_mirror; }
bool  FarmHouse::HasClock() const            { return has_clock; }
bool  FarmHouse::HasStocking() const         { return has_stocking; }
bool  FarmHouse::IsFireplaceLighted() const  { return fireplace_lighted; }
bool  FarmHouse::HasKitchen() const          { return has_kitchen; }
bool  FarmHouse::HasKitchenKnife() const     { return has_kitchen_knife; }
bool  FarmHouse::HasKitchenFryingPan() const { return has_kitchen_frying_pan; }
bool  FarmHouse::HasKitchenPot() const       { return has_kitchen_pot; }
bool  FarmHouse::HasKitchenMixer() const     { return has_kitchen_mixer; }
bool  FarmHouse::HasKitchenWhisk() const     { return has_kitchen_whisk; }
bool  FarmHouse::HasKitchenRollingPin() const { return has_kitchen_rolling_pin; }
bool  FarmHouse::HasKitchenOven() const      { return has_kitchen_oven; }
bool  FarmHouse::HasKitchenSeasoningSet() const { return has_kitchen_seasoning_set; }
u32   FarmHouse::GetStockingArticleId() const { return stocking_article_id; }

// 获取各容器的指针（如果没买则返回 nullptr）
Fridge const * FarmHouse::GetFridge() const {
    return !has_fridge ? nullptr : &fridge;
}
Shelf const * FarmHouse::GetShelf() const {
    return !has_shelf ? nullptr : &shelf;
}
RecordPlayer const * FarmHouse::GetRecordPlayer() const {
    return !has_record_player ? nullptr : &record_player;
}

Fridge * FarmHouse::GetFridge() {
    return !has_fridge ? nullptr : &fridge;
}
Shelf * FarmHouse::GetShelf() {
    return !has_shelf ? nullptr : &shelf;
}
RecordPlayer * FarmHouse::GetRecordPlayer() {
    return !has_record_player ? nullptr : &record_player;
}

// ═══════════════════════════════════════════════════════════════════════════════
//  升级和相关操作
// ═══════════════════════════════════════════════════════════════════════════════

// ★ 升级自宅等级（0→1→2，分别对应木匠的三次扩建）
void FarmHouse::UpgradeHouseLevel() {
    if (upgrade_level < 2) upgrade_level++;
}

// ── 添加各类家具（大部分有等级要求）────────────────────────────────

// ★ 浴室（需要等级2才能加）
void FarmHouse::AddBathroom() {
    if (upgrade_level == 2) has_bathroom = true;
}

// ★ 冰箱（需要等级1以上）
void FarmHouse::AddFridge() {
    if (upgrade_level != 0) has_fridge = true;
}

// ★ 收纳柜（需要等级1以上）
void FarmHouse::AddShelf() {
    if (upgrade_level != 0) has_shelf = true;
}

void FarmHouse::AddRecordPlayer() { has_record_player = true; }

// ★ 大床（需要等级2，结婚后可用）
void FarmHouse::AddLargeBed() {
    if (upgrade_level > 1) has_large_bed = true;
}

// 地毯（需要等级1以上）
void FarmHouse::AddCarpet() {
    if (upgrade_level != 0) has_carpet = true;
}

void FarmHouse::AddVase() { has_vase = true; }

// ★ 花瓶放花，并设置花的枯萎天数
void FarmHouse::SetVaseArticleId(u32 article_id) {
    vase_article_id = article_id;
    switch (vase_article_id) {
        default:                            vase_article_lifespan = 0;  break;
        case ARTICLE_MOON_DROP_GRASS:       vase_article_lifespan = 7;  break;  // 7天枯萎
        case ARTICLE_BLUE_MAGIC_GRASS:      vase_article_lifespan = 10; break;  // 10天枯萎
        case ARTICLE_PINK_CAT_GRASS:
        case ARTICLE_RED_MAGIC_GRASS:
        case ARTICLE_TOY_FLOWER:            vase_article_lifespan = 5;  break;  // 5天枯萎
    }
}

void FarmHouse::AddMirror() { has_mirror = true; }
void FarmHouse::AddClock()  { has_clock = true; }
void FarmHouse::AddStocking()      { has_stocking = true; }
void FarmHouse::RemoveStocking()   { has_stocking = false; }

// 点燃壁炉（冬季用，需要等级2以上）
void FarmHouse::LightFireplace() {
    if (upgrade_level > 1 && !fireplace_lighted)
        fireplace_lighted = true;
}

// ★ 厨房（需要等级1以上 + 冰箱）
void FarmHouse::AddKitchen() {
    if (upgrade_level != 0 && GetFridge() != nullptr)
        has_kitchen = true;
}

// 以下厨房工具都需要先有厨房才能加
void FarmHouse::AddKitchenKnife()       { if (has_kitchen) has_kitchen_knife = true; }
void FarmHouse::AddKitchenFryingPan()   { if (has_kitchen) has_kitchen_frying_pan = true; }
void FarmHouse::AddKitchenPot()         { if (has_kitchen) has_kitchen_pot = true; }
void FarmHouse::AddKitchenMixer()       { if (has_kitchen) has_kitchen_mixer = true; }
void FarmHouse::AddKitchenWhisk()       { if (has_kitchen) has_kitchen_whisk = true; }
void FarmHouse::KitchenRollingPin()     { if (has_kitchen) has_kitchen_rolling_pin = true; }
void FarmHouse::AddKitchenOven()        { if (has_kitchen) has_kitchen_oven = true; }
void FarmHouse::AddKitchenSeasoningSet(){ if (has_kitchen) has_kitchen_seasoning_set = true; }

// ── 外观样式设置（需要等级2）────────────────────────────────────
void FarmHouse::SetWindowStyle(u32 style_id)  { if (upgrade_level > 1) window_style = style_id; }
void FarmHouse::SetMailboxStyle(u32 style_id) { if (upgrade_level > 1) mailbox_style = style_id; }
void FarmHouse::SetDoghouseStyle(u32 style_id){ if (upgrade_level > 1) doghouse_style = style_id; }

void FarmHouse::SetStockingArticleId(u32 article_id) {
    stocking_article_id = article_id;
}

// ═══════════════════════════════════════════════════════════════════════════════
//  每日更新（花瓶的花枯萎判定）
// ═══════════════════════════════════════════════════════════════════════════════

void FarmHouse::DayUpdate(Season season) {
    // 每天重置壁炉状态（玩家需要每天重新点燃）
    fireplace_lighted = false;

    if (!has_vase || (u8)vase_article_id == ARTICLE_NONE)
        return;

    // 花瓶中的花寿命-1
    if (vase_article_lifespan)
        vase_article_lifespan--;

    // 不是当季的花也会枯萎
    switch (vase_article_id) {
        case ARTICLE_MOON_DROP_GRASS:
        case ARTICLE_TOY_FLOWER:
            if (season != SEASON_SPRING) vase_article_id = ARTICLE_NONE;
            break;
        case ARTICLE_PINK_CAT_GRASS:
            if (season != SEASON_SUMMER) vase_article_id = ARTICLE_NONE;
            break;
        case ARTICLE_BLUE_MAGIC_GRASS:
        case ARTICLE_RED_MAGIC_GRASS:
            if (season != SEASON_AUTUMN) vase_article_id = ARTICLE_NONE;
            break;
    }

    // 寿命到后 10% 概率每天枯萎
    if (vase_article_lifespan == 0 && (rand() & 0xFF) <= 100)
        vase_article_id = ARTICLE_NONE;
}

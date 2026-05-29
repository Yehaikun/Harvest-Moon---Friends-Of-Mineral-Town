// ═══════════════════════════════════════════════════════════════════════════════
// 【可嫁角色好感度系统】Bachelorette
// ═══════════════════════════════════════════════════════════════════════════════
// 控制所有可结婚对象（卡莲、珀布莉、玛丽、艾利、兰）的好感度、恋爱事件、
// 情敌事件等。
//
// 好感度倍率关系：
//  黑心  0～9,999
//  紫心  10,000～19,999
//  蓝心  20,000～29,999
//  绿心  30,000～39,999
//  黄心  40,000～49,999
//  红心  50,000～65,535（可求婚）
//
// 好感度增减规则：
//  · 每天第一次说话 +200
//  · 送喜欢的礼物 +800（参考 item.cc 的喜好表）
//  · 长时间不理 → 每天 -200
//  · 婚后不对话 → 每天 -1000（10%概率）
// ═══════════════════════════════════════════════════════════════════════════════

#include "bachelorette.hh"
#include <stdlib.h> // rand()

// ── 构造函数 ─────────────────────────────────────────────────────────────
// 游戏开始时：好感度=0（黑心），恋爱事件=0，情敌事件=0
// ★ 想开局满好感就改这里的 love = 0 → love = 60000
Bachelorette::Bachelorette(ActorLocation const & location)
    : Npc(location)
{
    love = 0;             // ★ 好感度（0～65535，60000=红心）
    player_events = 0;    // ★ 玩家的恋爱事件进度（0～6，6=全部看完）
    days_since_player_event = 0;  // 距上次恋爱事件的天数
    rival_events = 0;             // 情敌事件进度（0～5）
    days_since_rival_event = 0;   // 距上次情敌事件的天数
    unk_17_4 = 0;                 // 未知计数器
}

// ── 好感度获取 ──────────────────────────────────────────────────────────
u32 Bachelorette::GetLove() const    { return love; }
u32 Bachelorette::GetPlayerEventCount() const        { return player_events; }
u32 Bachelorette::GetDaysSincePlayerEvent_bugged() const { return days_since_rival_event; } // ← 疑似bug：返回了情敌天数
u32 Bachelorette::GetRivalEventCount() const         { return rival_events; }
u32 Bachelorette::GetDaysSinceRivalEvent() const     { return days_since_rival_event; }
u32 Bachelorette::method_0809E4BC() const            { return unk_17_4; }

// ── 好感度增减 ★ 想改一次加多少好感就改这里 ──────────────────────────
void Bachelorette::AddLove(int amount)
{
    u32 total = love + amount;

    // 限制在 0～65535 之间
    if ((int)total < 0)
        total = 0;
    else if (0xFFFF < total)
        total = 0xFFFF;

    love = total;
}

void Bachelorette::SubtractLove(int amount)
{
    AddLove(-amount);  // 减好感 = 加负数
}

void Bachelorette::SetLove(int amount)
{
    love = amount;
}

// ── 玩家的恋爱事件推进 ─────────────────────────────────────────────
// player_events 范围 0～6，对应 6 个恋爱事件（黑/紫/蓝/绿/黄/红心事件）
// 达到 6 后不再增加
void Bachelorette::PlayerEventUpdate()
{
    if (player_events < 6) {
        player_events++;
        days_since_player_event = 0;  // 重置天数
    }
}

// ── 情敌事件推进 ─────────────────────────────────────────────────────
// rival_events 范围 0～5，对应 5 个情敌事件
void Bachelorette::RivalEventUpdate()
{
    if (rival_events < 5) {
        rival_events++;
        days_since_rival_event = 0;
    }
}

void Bachelorette::method_0809E550()
{
    if (unk_17_4 < 5)
        unk_17_4++;
}

// ── 每天的自动好感变化 ───────────────────────────────────────────────
// 每晚自动调用，效果：
//  · 今天说过话 → +200
//  · 超过 1 天没说话 → -200
//  · 好感衰减（婚后更严重）
//  · 距上次事件天数 +1
void Bachelorette::DayUpdate(bool decay_love, u32 arg_01)
{
    // 今天说过话 → 加好感
    if (HasBeenSpokenToToday())
        AddLove(200);

    Npc::DayUpdate(arg_01);

    // 超过 1 天没说话 → 减好感
    if (GetDaysSinceLastSpoken() != 0 && arg_01 < 10)
        SubtractLove(200);

    // 好感自然衰减
    if (decay_love)
    {
        if (player_events > 5)
        {
            // 婚后：超过 5 天没说话 → 10%概率 -1000
            if (4 < GetDaysSinceLastSpoken() && (rand() % 100) < 10)
                SubtractLove(1000);
        }
        else
        {
            // 婚前：每天 -100
            SubtractLove(100);
        }
    }

    // 距上次事件天数递增（上限 7 天）
    if (days_since_player_event < 7)
        days_since_player_event++;

    if (days_since_rival_event < 7)
        days_since_rival_event++;
}

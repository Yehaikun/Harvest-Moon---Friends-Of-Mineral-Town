// ✋ 手持物品 - 玩家手持物品管理

#include "held_item.hh"

HeldItem::HeldItem()
{
    kind = HeldItem::KIND_5;
    wrapped = 0;
    inner.unk_k5_02 = UINT16_MAX;
}

EC bool func_0800F190(HeldItem const * self)
{
    switch (self->kind)
    {
        default:
            return true;

        case HeldItem::KIND_FOOD:
            return self->inner.food.id >= FOOD_NONE;

        case HeldItem::KIND_ARTICLE:
            return self->inner.article.id >= ARTICLE_NONE;

        case HeldItem::KIND_2:
            return false;

        case HeldItem::KIND_3:
            return self->inner.unk_k3.id >= 8;

        case HeldItem::KIND_4:
            return false;

        case HeldItem::KIND_5:
            return self->inner.unk_k5_02 == 0xFFFF;
    }
}

EC HeldItem::Kind func_0800F204(HeldItem const * self)
{
    return self->kind;
}

EC Food func_0800F20C(HeldItem const * self)
{
    if (self->kind == HeldItem::KIND_FOOD && self->inner.food.id < FOOD_NONE)
    {
        Food food(self->inner.food.id);

        food.AddBonuses(self->inner.food.stamina_bonus, self->inner.food.fatigue_bonus);

        return food;
    }

    return Food(FOOD_NONE);
}

EC Article func_0800F258(HeldItem const * self)
{
    if (self->kind == HeldItem::KIND_ARTICLE && self->inner.article.id < ARTICLE_NONE)
    {
        return Article(self->inner.article.id);
    }

    return Article(ARTICLE_NONE);
}

EC RucksackItem func_0800F294(HeldItem const * self)
{
    if (self->kind == HeldItem::KIND_FOOD && self->inner.food.id < FOOD_NONE)
    {
        Food food(self->inner.food.id);

        food.AddBonuses(self->inner.food.stamina_bonus, self->inner.food.fatigue_bonus);

        RucksackItem rucksack_item(food);

        if (self->wrapped)
        {
            rucksack_item.TryWrap();
        }

        return rucksack_item;
    }

    if (self->kind == HeldItem::KIND_ARTICLE && self->inner.food.id < ARTICLE_NONE)
    {
        Article article(self->inner.article.id);

        RucksackItem rucksack_item(article);

        if (self->wrapped)
        {
            rucksack_item.TryWrap();
        }

        return rucksack_item;
    }

    return RucksackItem();
}

EC int func_0800F344(HeldItem const * self)
{
    if (self->kind == HeldItem::KIND_3 && self->inner.unk_k3.id < 8)
        return self->inner.unk_k3.id;

    return -1;
}

EC int func_0800F360(HeldItem const * self)
{
    if (self->kind == HeldItem::KIND_5 && self->inner.unk_k5_02 < 0xFFFF)
        return self->inner.unk_k5_02;

    return -1;
}

EC bool func_0800F388(HeldItem const * self)
{
    return self->wrapped;
}

EC void func_0800F390(HeldItem * self)
{
    self->kind = HeldItem::KIND_5;
    self->wrapped = 0;
    self->inner.unk_k5_02 = UINT16_MAX;
}

EC void func_0800F3B0(HeldItem * self, Food food)
{
    self->kind = HeldItem::KIND_FOOD;
    self->wrapped = 0;
    self->inner.food.id = food.GetId();
    self->inner.food.stamina_bonus = food.GetStaminaBonus();
    self->inner.food.fatigue_bonus = food.GetFatigueBonus();
}

EC void func_0800F3E8(HeldItem * self, Article article)
{
    self->kind = HeldItem::KIND_ARTICLE;
    self->wrapped = 0;
    self->inner.food.id = article.GetId();
}

EC void func_0800F418(HeldItem * self, RucksackItem rucksack_item)
{
    switch (rucksack_item.GetKind())
    {
        default:
            self->wrapped = false;
            break;

        case RucksackItem::KIND_FOOD:
        {
            self->kind = HeldItem::KIND_FOOD;
            self->wrapped = rucksack_item.IsWrapped();
            Food food = rucksack_item.GetFood();
            self->inner.food.id = food.GetId();
            self->inner.food.stamina_bonus = food.GetStaminaBonus();
            self->inner.food.fatigue_bonus = food.GetFatigueBonus();
            break;
        }

        case RucksackItem::KIND_ARTICLE:
        {
            self->kind = HeldItem::KIND_ARTICLE;
            self->wrapped = rucksack_item.IsWrapped();
            Article article = rucksack_item.GetArticle();
            self->inner.food.id = article.GetId();
            break;
        }
    }
}

EC void func_0800F4C0(HeldItem * self)
{
    self->kind = HeldItem::KIND_2;
    self->wrapped = 0;
}

EC void func_0800F4D8(HeldItem * self)
{
    self->kind = HeldItem::KIND_4;
    self->wrapped = 0;
}

EC void func_0800F4F0(HeldItem * self, fu8 arg_1)
{
    self->kind = HeldItem::KIND_3;
    self->wrapped = 0;
    self->inner.unk_k3.id = arg_1 % 8;
}

EC void func_0800F510(HeldItem * self, int arg_1)
{
    self->kind = HeldItem::KIND_5;
    self->wrapped = 0;
    self->inner.unk_k5_02 = arg_1;
}

EC bool func_0800F528(HeldItem * self)
{
    bool can_be_wrapped = false;

    switch (self->kind)
    {
        case HeldItem::KIND_FOOD:
            can_be_wrapped = true;
            break;

        case HeldItem::KIND_ARTICLE:
            can_be_wrapped = Article(self->inner.article.id).CanBeDiscarded();
            break;

        default:
            break;
    }

    self->wrapped = can_be_wrapped;
    return can_be_wrapped;
}

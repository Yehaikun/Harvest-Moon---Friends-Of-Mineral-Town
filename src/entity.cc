// 👤 实体基类 - 所有游戏实体的抽象基类
//
// AEntity 是所有游戏内对象的基类，包括玩家、NPC、动物、物品等。
// 每个实体有：关联的 Game 对象、所在地图 ID、位置坐标（Q16 定点数）、以及一个
// 可选的子对象指针（unk_10，指向一个智能指针管理的对象）。
//
// 布局: { +00: game_object_ptr, +04: map_id, +06: is_active,
//          +08: x_q16, +0C: y_q16, +10: display_obj_ptr }
// 总大小: 0x18 (24 字节)

#include "entity.hh"

/**
 * AEntity 构造函数
 * @param game_object 指向全局 Game 对象的指针
 * @param location    初始位置（含 map_id, x, y）
 */
AEntity::AEntity(GameObject * game_object, Location const & location)
    : game_object(game_object), location_map(location.map), unk_06(false), x_q16(location.x << 16), y_q16(location.y << 16)
{
}

/**
 * vfunc_10 — 虚函数 #10：刷新子对象（unk_10）
 *
 * 当实体所在的地图发生变化时，重新创建子对象。
 * 如果当前地图与 Game 对象记录的不一致，则跳过。
 * 否则调用 vfunc_30() 创建新的子对象并赋值给 unk_10。
 */
void AEntity::vfunc_10()
{
    unk_10 = nullptr;

    if (game_object->vfunc_14() != location_map)
        return;

    unk_10 = vfunc_30();
}

/**
 * vfunc_14 — 虚函数 #14：清除子对象
 *
 * 将 unk_10 置空，销毁当前子对象（通过智能指针的析构函数）。
 */
void AEntity::vfunc_14()
{
    unk_10 = nullptr;
}

/**
 * vfunc_1C — 虚函数 #1C：将参数转发给子对象的 vfunc_10
 *
 * 如果当前有子对象（unk_10），则将参数 dummy 传递给它处理。
 * @param dummy 透传参数（用途由子类定义）
 */
void AEntity::vfunc_1C(u32 dummy)
{
    if (unk_10.Get() != nullptr)
        unk_10->vfunc_10(dummy);
}

/**
 * vfunc_2C — 虚函数 #2C：通知子对象执行 vfunc_0C
 *
 * 如果当前有子对象，调用其 vfunc_0C()。
 * @param dummy 保留参数，未使用
 */
void AEntity::vfunc_2C(u32 dummy)
{
    if (unk_10.Get() != nullptr)
        unk_10->vfunc_0C();
}

/**
 * SetLocation — 设置实体位置
 *
 * 同时更新地图 ID 和 XY 坐标。坐标以 Q16 格式存储（整数部分左移 16 位）。
 * @param map 目标地图 ID
 * @param x   X 坐标（游戏单位）
 * @param y   Y 坐标（游戏单位）
 */
void AEntity::SetLocation(u32 map, i32 x, i32 y)
{
    SetMap(map);
    x_q16 = x << 16;
    y_q16 = y << 16;
}

/**
 * GetLocation — 获取实体当前位置
 *
 * 将 Q16 定点数右移 16 位还原为游戏单位坐标。
 * @return Location 结构体（map_id, x, y）
 */
Location AEntity::GetLocation() const
{
    return Location(location_map, x_q16 >> 16, y_q16 >> 16);
}

/**
 * GetBox — 获取实体的碰撞盒
 *
 * 以当前位置为基准，返回一个单位大小的碰撞盒。
 * @return Box 结构体（x, y）
 */
Box AEntity::GetBox() const
{
    return Box(x_q16 >> 16, y_q16 >> 16);
}

/**
 * SetMap — 设置实体所在的地图
 *
 * 如果地图发生变化，则调用 vfunc_10() 刷新子对象。
 * @param map 目标地图 ID
 */
void AEntity::SetMap(u32 map)
{
    if (location_map != map)
    {
        location_map = map;
        vfunc_10();
    }
}

/**
 * vfunc_18 — 虚函数 #18：通知子对象执行 vfunc_0C
 *
 * 独立于 vfunc_2C 的调用路径，用途相同。
 */
void AEntity::vfunc_18()
{
    if (unk_10.Get() != nullptr)
        unk_10->vfunc_0C();
}

/**
 * vfunc_28 — 虚函数 #28：检查实体的活跃标志
 *
 * @return true 表示实体正在执行特殊操作/动画
 */
bool AEntity::vfunc_28() const
{
    return unk_06;
}

/**
 * vfunc_24 — 虚函数 #24：清除活跃标志
 *
 * 标记实体不再处于特殊操作状态。
 */
void AEntity::vfunc_24()
{
    unk_06 = false;
}

/**
 * vfunc_20 — 虚函数 #20：设置活跃标志
 *
 * 标记实体正在执行特殊操作/动画。
 */
void AEntity::vfunc_20()
{
    unk_06 = true;
}

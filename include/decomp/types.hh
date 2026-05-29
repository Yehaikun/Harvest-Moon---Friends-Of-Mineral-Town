// ═══════════════════════════════════════════════════════════════════════════════
// 反编译笔记：游戏基础类型定义
// 来源: FOMT-DOC (StanHash)
// ═══════════════════════════════════════════════════════════════════════════════
// 这些结构体定义来自 StanHash 的逆向工程笔记，用于帮助理解汇编代码。
// 注意：这些只是反编译笔记，不是编译所需的正式头文件。
// ═══════════════════════════════════════════════════════════════════════════════

#ifndef DECOMP_TYPES_HH
#define DECOMP_TYPES_HH

// GBA 基础类型
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed char    s8;
typedef signed int     s32;

// 游戏中常用的 Location 结构（实体位置）
// 共 6 字节：10位地图ID + 16位X坐标 + 16位Y坐标
struct Location {
    u32 map : 10;  // 地图 ID (0～1023)
    i32 x   : 16;  // X 坐标（像素）
    i32 y   : 16;  // Y 坐标（像素）
};

// ActorLocation = Location + 朝向
struct ActorLocation : Location {
    u8 facing;  // 0=下 1=上 2=左 3=右
};

// 四季枚举
enum Season {
    SEASON_SPRING,  // 春
    SEASON_SUMMER,  // 夏
    SEASON_AUTUMN,  // 秋
    SEASON_WINTER,  // 冬
};

// 日期结构（2 字节：2位季节 + 5位日）
struct GameDate {
    Season season : 2;
    u8 day        : 5;
};

// 时间结构（2 字节：5位小时 + 6位分钟）
struct GameTime {
    u16 hour   : 5;
    u16 minute : 6;
};

#endif // DECOMP_TYPES_HH

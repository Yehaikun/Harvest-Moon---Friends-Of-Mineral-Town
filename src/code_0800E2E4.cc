// 🔧 辅助函数 0x0800E2E4 - 场景相关

#include "prelude.h"

#include "unknown_types.hh" // for GameDate and Time

#if 0

char const gUnk_080F04EE[4][7] = { "Spring", "Summer", "Fall  ", "Winter" };
char const gUnk_080F050C[] = "\x96\xB3";
char const gUnk_080F050F[7][5] = { "Sun.", "Mon.", "Tue.", "Wed.", "Thu.", "Fri.", "Sat." };

#else

extern char const gUnk_080F04EE[][7];
extern char const gUnk_080F050C[];
extern char const gUnk_080F050F[][5];

#endif

EC char const * func_0800E2E4(Season season)
{
    if (season < NUM_SEASONS)
    {
        return gUnk_080F04EE[season];
    }

    return gUnk_080F050C;
}

EC char const * func_0800E304(unsigned int week_day)
{
    if (week_day < 7)
    {
        return gUnk_080F050F[week_day];
    }

    return gUnk_080F050C;
}

struct Unk_0800E324
{
    u8 unk_00; /* year? */
    GameDate date;
    GameTime time;
};

EC u32 func_0800E324(Unk_0800E324 const & arg_0)
{
    GameDate const & date = arg_0.date;
    GameTime const & time = arg_0.time;

    if (date.GetDay() == 0 && time.GetHour() < 6)
    {
        /* get previous season
         * TODO: inline GetPreviousSeason(season)? */
        return (date.GetSeason() % NUM_SEASONS - 1u) % NUM_SEASONS;
    }

    return date.GetSeason();
}

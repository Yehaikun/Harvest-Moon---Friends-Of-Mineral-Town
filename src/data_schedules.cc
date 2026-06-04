// 📅 计划表数据 - NPC 日程安排数据

#include "prelude.h"

#include "schedule_info.hh"

/*
 * this is experimental dump of first schedule structure, to get an idea of the format
 * ~~this should probably be in data/ and included by actual source files~~
 * there's "bad_alloc" strings inbetween schedules: it suggests that each schedule should be in its own .cc file
 */

/*
 * see also:
 * - tools/scripts/dump_schedule.py
 * - tools/scripts/schedule_to_c.py
 */

extern "C" u32 func_0803DA24(void const *);

extern ScheduleInfo const ScheduleInfo_Unk_080F1A80;
extern Schedule const * const Unk_080F1A80_Schedules[5];
extern Schedule const Unk_080F1A80_Schedule_1;
extern Schedule const Unk_080F1A80_Schedule_2;
extern Schedule const Unk_080F1A80_Schedule_3;
extern Schedule const Unk_080F1A80_Schedule_4;
extern ScheduleEntry const Unk_080F1A80_Schedule_1_Entries[17];
extern ScheduleEntry const Unk_080F1A80_Schedule_2_Entries[9];
extern ScheduleEntry const Unk_080F1A80_Schedule_3_Entries[17];
extern ScheduleEntry const Unk_080F1A80_Schedule_4_Entries[1];
extern PathInfo const Unk_080F1A80_0_Path;
extern PathInfo const Unk_080F1A80_1_Path;
extern PathInfo const Unk_080F1A80_2_Path;
extern PathInfo const Unk_080F1A80_3_Path;
extern PathInfo const Unk_080F1A80_4_Path;
extern PathInfo const Unk_080F1A80_5_Path;
extern PathInfo const Unk_080F1A80_6_Path;
extern PathInfo const Unk_080F1A80_7_Path;
extern PathInfo const Unk_080F1A80_8_Path;
extern PathInfo const Unk_080F1A80_9_Path;
extern PathInfo const Unk_080F1A80_10_Path;
extern PathInfo const Unk_080F1A80_11_Path;
extern PathInfo const Unk_080F1A80_12_Path;
extern PathInfo const Unk_080F1A80_13_Path;
extern PathInfo const Unk_080F1A80_14_Path;
extern PathInfo const Unk_080F1A80_15_Path;
extern PathInfo const Unk_080F1A80_16_Path;
extern PathInfo const Unk_080F1A80_17_Path;
extern PathInfo const Unk_080F1A80_18_Path;
extern PathInfo const Unk_080F1A80_19_Path;
extern PathInfo const Unk_080F1A80_20_Path;
extern PathInfo const Unk_080F1A80_21_Path;
extern PathInfo const Unk_080F1A80_22_Path;
extern PathPointA const Unk_080F1A80_2_Path_Points[5];
extern PathPointA const Unk_080F1A80_4_Path_Points[5];
extern PathPointA const Unk_080F1A80_5_Path_Points[5];
extern PathPointA const Unk_080F1A80_6_Path_Points[7];
extern PathPointA const Unk_080F1A80_7_Path_Points[3];
extern PathPointA const Unk_080F1A80_9_Path_Points[3];
extern PathPointA const Unk_080F1A80_10_Path_Points[7];
extern PathPointA const Unk_080F1A80_11_Path_Points[2];
extern PathPointB const Unk_080F1A80_12_Path_Points[2];
extern PathPointA const Unk_080F1A80_13_Path_Points[2];
extern PathPointA const Unk_080F1A80_14_Path_Points[7];
extern PathPointA const Unk_080F1A80_15_Path_Points[5];
extern PathPointA const Unk_080F1A80_17_Path_Points[5];
extern PathPointA const Unk_080F1A80_18_Path_Points[3];
extern PathPointB const Unk_080F1A80_19_Path_Points[4];
extern PathPointA const Unk_080F1A80_20_Path_Points[3];
extern PathPointA const Unk_080F1A80_21_Path_Points[5];
extern PathPointA const Unk_080F1A80_22_Path_Points[7];

ScheduleInfo const ScheduleInfo_Unk_080F1A80 = { func_0803DA24, 5, Unk_080F1A80_Schedules };

Schedule const * const Unk_080F1A80_Schedules[5] = {
    nullptr, &Unk_080F1A80_Schedule_1, &Unk_080F1A80_Schedule_2, &Unk_080F1A80_Schedule_3, &Unk_080F1A80_Schedule_4,
};

Schedule const Unk_080F1A80_Schedule_1 = { 17, Unk_080F1A80_Schedule_1_Entries };

Schedule const Unk_080F1A80_Schedule_2 = { 9, Unk_080F1A80_Schedule_2_Entries };

Schedule const Unk_080F1A80_Schedule_3 = { 17, Unk_080F1A80_Schedule_3_Entries };

Schedule const Unk_080F1A80_Schedule_4 = { 1, Unk_080F1A80_Schedule_4_Entries };

ScheduleEntry const Unk_080F1A80_Schedule_1_Entries[17] = {
    { 0, &Unk_080F1A80_19_Path },    /* 06:00 */
    { 60, &Unk_080F1A80_21_Path },   /* 07:00 */
    { 91, &Unk_080F1A80_2_Path },    /* 07:31 */
    { 139, &Unk_080F1A80_3_Path },   /* 08:19 */
    { 242, &Unk_080F1A80_4_Path },   /* 10:02 */
    { 291, &Unk_080F1A80_5_Path },   /* 10:51 */
    { 321, &Unk_080F1A80_1_Path },   /* 11:21 */
    { 423, &Unk_080F1A80_18_Path },  /* 13:03 */
    { 430, &Unk_080F1A80_19_Path },  /* 13:10 */
    { 600, &Unk_080F1A80_20_Path },  /* 16:00 */
    { 607, &Unk_080F1A80_1_Path },   /* 16:07 */
    { 780, &Unk_080F1A80_6_Path },   /* 19:00 */
    { 827, &Unk_080F1A80_7_Path },   /* 19:47 */
    { 861, &Unk_080F1A80_8_Path },   /* 20:21 */
    { 972, &Unk_080F1A80_9_Path },   /* 22:12 */
    { 1007, &Unk_080F1A80_10_Path }, /* 22:47 */
    { 1054, &Unk_080F1A80_0_Path },  /* 23:34 */
};

ScheduleEntry const Unk_080F1A80_Schedule_2_Entries[9] = {
    { 0, &Unk_080F1A80_19_Path },    /* 06:00 */
    { 60, &Unk_080F1A80_20_Path },   /* 07:00 */
    { 67, &Unk_080F1A80_0_Path },    /* 07:07 */
    { 780, &Unk_080F1A80_6_Path },   /* 19:00 */
    { 827, &Unk_080F1A80_7_Path },   /* 19:47 */
    { 861, &Unk_080F1A80_8_Path },   /* 20:21 */
    { 972, &Unk_080F1A80_9_Path },   /* 22:12 */
    { 1007, &Unk_080F1A80_10_Path }, /* 22:47 */
    { 1054, &Unk_080F1A80_0_Path },  /* 23:34 */
};

ScheduleEntry const Unk_080F1A80_Schedule_3_Entries[17] = {
    { 0, &Unk_080F1A80_19_Path },    /* 06:00 */
    { 60, &Unk_080F1A80_22_Path },   /* 07:00 */
    { 108, &Unk_080F1A80_11_Path },  /* 07:48 */
    { 117, &Unk_080F1A80_12_Path },  /* 07:57 */
    { 240, &Unk_080F1A80_13_Path },  /* 10:00 */
    { 250, &Unk_080F1A80_14_Path },  /* 10:10 */
    { 297, &Unk_080F1A80_1_Path },   /* 10:57 */
    { 420, &Unk_080F1A80_15_Path },  /* 13:00 */
    { 438, &Unk_080F1A80_16_Path },  /* 13:18 */
    { 600, &Unk_080F1A80_17_Path },  /* 16:00 */
    { 618, &Unk_080F1A80_1_Path },   /* 16:18 */
    { 780, &Unk_080F1A80_6_Path },   /* 19:00 */
    { 827, &Unk_080F1A80_7_Path },   /* 19:47 */
    { 861, &Unk_080F1A80_8_Path },   /* 20:21 */
    { 972, &Unk_080F1A80_9_Path },   /* 22:12 */
    { 1007, &Unk_080F1A80_10_Path }, /* 22:47 */
    { 1054, &Unk_080F1A80_0_Path },  /* 23:34 */
};

ScheduleEntry const Unk_080F1A80_Schedule_4_Entries[1] = {
    { 0, &Unk_080F1A80_0_Path }, /* 06:00 */
};

PathInfo const Unk_080F1A80_0_Path = {
    nullptr, /* points */
    0,       /* num_points */
    72,      /* x_start */
    80,      /* y_start */
    11,      /* location_start */
    0,       /* facing_start */
    0,       /* point_type_select */
};

PathInfo const Unk_080F1A80_1_Path = {
    nullptr, /* points */
    0,       /* num_points */
    64,      /* x_start */
    83,      /* y_start */
    10,      /* location_start */
    1,       /* facing_start */
    0,       /* point_type_select */
};

PathInfo const Unk_080F1A80_2_Path = {
    (void const *)Unk_080F1A80_2_Path_Points, /* points */
    5,                                        /* num_points */
    104,                                      /* x_start */
    704,                                      /* y_start */
    5,                                        /* location_start */
    0,                                        /* facing_start */
    0,                                        /* point_type_select */
};

PathInfo const Unk_080F1A80_3_Path = {
    nullptr, /* points */
    0,       /* num_points */
    776,     /* x_start */
    184,     /* y_start */
    5,       /* location_start */
    0,       /* facing_start */
    0,       /* point_type_select */
};

PathInfo const Unk_080F1A80_4_Path = {
    (void const *)Unk_080F1A80_4_Path_Points, /* points */
    5,                                        /* num_points */
    776,                                      /* x_start */
    184,                                      /* y_start */
    5,                                        /* location_start */
    0,                                        /* facing_start */
    0,                                        /* point_type_select */
};

PathInfo const Unk_080F1A80_5_Path = {
    (void const *)Unk_080F1A80_5_Path_Points, /* points */
    5,                                        /* num_points */
    104,                                      /* x_start */
    0,                                        /* y_start */
    7,                                        /* location_start */
    0,                                        /* facing_start */
    0,                                        /* point_type_select */
};

PathInfo const Unk_080F1A80_6_Path = {
    (void const *)Unk_080F1A80_6_Path_Points, /* points */
    7,                                        /* num_points */
    572,                                      /* x_start */
    227,                                      /* y_start */
    7,                                        /* location_start */
    0,                                        /* facing_start */
    0,                                        /* point_type_select */
};

PathInfo const Unk_080F1A80_7_Path = {
    (void const *)Unk_080F1A80_7_Path_Points, /* points */
    3,                                        /* num_points */
    1260,                                     /* x_start */
    704,                                      /* y_start */
    5,                                        /* location_start */
    0,                                        /* facing_start */
    0,                                        /* point_type_select */
};

PathInfo const Unk_080F1A80_8_Path = {
    nullptr, /* points */
    0,       /* num_points */
    232,     /* x_start */
    120,     /* y_start */
    21,      /* location_start */
    1,       /* facing_start */
    0,       /* point_type_select */
};

PathInfo const Unk_080F1A80_9_Path = {
    (void const *)Unk_080F1A80_9_Path_Points, /* points */
    3,                                        /* num_points */
    632,                                      /* x_start */
    488,                                      /* y_start */
    5,                                        /* location_start */
    0,                                        /* facing_start */
    0,                                        /* point_type_select */
};

PathInfo const Unk_080F1A80_10_Path = {
    (void const *)Unk_080F1A80_10_Path_Points, /* points */
    7,                                         /* num_points */
    1272,                                      /* x_start */
    0,                                         /* y_start */
    7,                                         /* location_start */
    0,                                         /* facing_start */
    0,                                         /* point_type_select */
};

PathInfo const Unk_080F1A80_11_Path = {
    (void const *)Unk_080F1A80_11_Path_Points, /* points */
    2,                                         /* num_points */
    220,                                       /* x_start */
    448,                                       /* y_start */
    6,                                         /* location_start */
    0,                                         /* facing_start */
    0,                                         /* point_type_select */
};

PathInfo const Unk_080F1A80_12_Path = {
    (void const *)Unk_080F1A80_12_Path_Points, /* points */
    2,                                         /* num_points */
    376,                                       /* x_start */
    384,                                       /* y_start */
    6,                                         /* location_start */
    0,                                         /* facing_start */
    1,                                         /* point_type_select */
};

PathInfo const Unk_080F1A80_13_Path = {
    (void const *)Unk_080F1A80_13_Path_Points, /* points */
    2,                                         /* num_points */
    376,                                       /* x_start */
    384,                                       /* y_start */
    6,                                         /* location_start */
    0,                                         /* facing_start */
    0,                                         /* point_type_select */
};

PathInfo const Unk_080F1A80_14_Path = {
    (void const *)Unk_080F1A80_14_Path_Points, /* points */
    7,                                         /* num_points */
    1272,                                      /* x_start */
    0,                                         /* y_start */
    7,                                         /* location_start */
    0,                                         /* facing_start */
    0,                                         /* point_type_select */
};

PathInfo const Unk_080F1A80_15_Path = {
    (void const *)Unk_080F1A80_15_Path_Points, /* points */
    5,                                         /* num_points */
    572,                                       /* x_start */
    227,                                       /* y_start */
    7,                                         /* location_start */
    0,                                         /* facing_start */
    0,                                         /* point_type_select */
};

PathInfo const Unk_080F1A80_16_Path = {
    nullptr, /* points */
    0,       /* num_points */
    88,      /* x_start */
    88,      /* y_start */
    38,      /* location_start */
    0,       /* facing_start */
    0,       /* point_type_select */
};

PathInfo const Unk_080F1A80_17_Path = {
    (void const *)Unk_080F1A80_17_Path_Points, /* points */
    5,                                         /* num_points */
    296,                                       /* x_start */
    116,                                       /* y_start */
    7,                                         /* location_start */
    0,                                         /* facing_start */
    0,                                         /* point_type_select */
};

PathInfo const Unk_080F1A80_18_Path = {
    (void const *)Unk_080F1A80_18_Path_Points, /* points */
    3,                                         /* num_points */
    572,                                       /* x_start */
    227,                                       /* y_start */
    7,                                         /* location_start */
    0,                                         /* facing_start */
    0,                                         /* point_type_select */
};

PathInfo const Unk_080F1A80_19_Path = {
    (void const *)Unk_080F1A80_19_Path_Points, /* points */
    4,                                         /* num_points */
    520,                                       /* x_start */
    352,                                       /* y_start */
    7,                                         /* location_start */
    0,                                         /* facing_start */
    1,                                         /* point_type_select */
};

PathInfo const Unk_080F1A80_20_Path = {
    (void const *)Unk_080F1A80_20_Path_Points, /* points */
    3,                                         /* num_points */
    520,                                       /* x_start */
    352,                                       /* y_start */
    7,                                         /* location_start */
    0,                                         /* facing_start */
    0,                                         /* point_type_select */
};

PathInfo const Unk_080F1A80_21_Path = {
    (void const *)Unk_080F1A80_21_Path_Points, /* points */
    5,                                         /* num_points */
    520,                                       /* x_start */
    352,                                       /* y_start */
    7,                                         /* location_start */
    0,                                         /* facing_start */
    0,                                         /* point_type_select */
};

PathInfo const Unk_080F1A80_22_Path = {
    (void const *)Unk_080F1A80_22_Path_Points, /* points */
    7,                                         /* num_points */
    520,                                       /* x_start */
    352,                                       /* y_start */
    7,                                         /* location_start */
    0,                                         /* facing_start */
    0,                                         /* point_type_select */
};

PathPointA const Unk_080F1A80_2_Path_Points[5] = {
    { 19, 240, 1 }, { 21, 144, 0 }, { 22, 216, 1 }, { 47, 776, 0 }, { 48, 184, 1 },
};

PathPointA const Unk_080F1A80_4_Path_Points[5] = {
    { 1, 216, 1 }, { 26, 144, 0 }, { 27, 240, 1 }, { 29, 104, 0 }, { 49, 736, 1 },
};

PathPointA const Unk_080F1A80_5_Path_Points[5] = {
    { 6, 152, 1 }, { 21, 472, 0 }, { 25, 248, 1 }, { 29, 572, 0 }, { 30, 227, 1 },
};

PathPointA const Unk_080F1A80_6_Path_Points[7] = {
    { 1, 248, 1 }, { 5, 472, 0 }, { 9, 152, 1 }, { 40, 1248, 0 }, { 41, 128, 1 }, { 42, 1272, 0 }, { 47, 0, 1 },
};

PathPointA const Unk_080F1A80_7_Path_Points[3] = {
    { 7, 536, 1 },
    { 32, 632, 0 },
    { 34, 488, 1 },
};

PathPointA const Unk_080F1A80_9_Path_Points[3] = {
    { 2, 536, 1 },
    { 27, 1260, 0 },
    { 35, 736, 1 },
};

PathPointA const Unk_080F1A80_10_Path_Points[7] = {
    { 5, 128, 1 }, { 6, 1248, 0 }, { 7, 152, 1 }, { 38, 472, 0 }, { 42, 248, 1 }, { 46, 572, 0 }, { 47, 227, 1 },
};

PathPointA const Unk_080F1A80_11_Path_Points[2] = {
    { 3, 384, 1 },
    { 9, 376, 0 },
};

PathPointB const Unk_080F1A80_12_Path_Points[2] = {
    { 304, 2, 120, 0, 1 },
    { 384, 2, 120, 1, 1 },
};

PathPointA const Unk_080F1A80_13_Path_Points[2] = {
    { 6, 220, 0 },
    { 10, 480, 1 },
};

PathPointA const Unk_080F1A80_14_Path_Points[7] = {
    { 5, 128, 1 }, { 6, 1248, 0 }, { 7, 152, 1 }, { 38, 472, 0 }, { 42, 248, 1 }, { 46, 572, 0 }, { 47, 227, 1 },
};

PathPointA const Unk_080F1A80_15_Path_Points[5] = {
    { 1, 248, 1 }, { 5, 472, 0 }, { 9, 152, 1 }, { 16, 296, 0 }, { 18, 116, 1 },
};

PathPointA const Unk_080F1A80_17_Path_Points[5] = {
    { 2, 152, 1 }, { 9, 472, 0 }, { 13, 248, 1 }, { 17, 572, 0 }, { 18, 227, 1 },
};

PathPointA const Unk_080F1A80_18_Path_Points[3] = {
    { 1, 248, 1 },
    { 3, 520, 0 },
    { 7, 352, 1 },
};

PathPointB const Unk_080F1A80_19_Path_Points[4] = {
    { 440, 2, 0, 0, 0 },
    { 256, 2, 120, 2, 1 },
    { 352, 2, 0, 0, 1 },
    { 520, 2, 120, 3, 0 },
};

PathPointA const Unk_080F1A80_20_Path_Points[3] = {
    { 4, 248, 1 },
    { 6, 572, 0 },
    { 7, 227, 1 },
};

PathPointA const Unk_080F1A80_21_Path_Points[5] = {
    { 4, 248, 1 }, { 6, 472, 0 }, { 10, 152, 1 }, { 25, 104, 0 }, { 31, 0, 1 },
};

PathPointA const Unk_080F1A80_22_Path_Points[7] = {
    { 4, 248, 1 }, { 6, 472, 0 }, { 10, 152, 1 }, { 41, 1248, 0 }, { 42, 128, 1 }, { 43, 1272, 0 }, { 48, 0, 1 },
};

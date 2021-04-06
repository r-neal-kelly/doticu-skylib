/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_day.h"

namespace doticu_skylib {

    class Package_Schedule_t    // PackageSchedule
    {
    public:
        s8      month;                  // 0
        Day_e   day;                    // 1
        s8      date;                   // 2
        s8      hour;                   // 3
        s8      minute;                 // 4
        u8      pad_05;                 // 5
        u8      pad_06;                 // 6
        u8      pad_07;                 // 7
        s32     duration_in_minutes;    // 8
    };
    STATIC_ASSERT(sizeof(Package_Schedule_t) == 0x0C);

}

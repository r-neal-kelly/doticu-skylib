/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/calendar_date_day.h"
#include "doticu_skylib/calendar_date_month.h"
#include "doticu_skylib/calendar_time_hour_24.h"
#include "doticu_skylib/calendar_time_minute.h"
#include "doticu_skylib/enum_calendar_date_weekday.h"

namespace doticu_skylib {

    class Package_Schedule_t    // PackageSchedule
    {
    public:
        Calendar_Date_Month_t   month;                  // 0
        Calendar_Date_Weekday_e weekday;                // 1
        Calendar_Date_Day_t     day;                    // 2
        Calendar_Time_Hour_24_t hour;                   // 3
        Calendar_Time_Minute_t  minute;                 // 4
        u8                      pad_05;                 // 5
        u8                      pad_06;                 // 6
        u8                      pad_07;                 // 7
        s32                     duration_in_minutes;    // 8
    };
    STATIC_ASSERT(sizeof(Package_Schedule_t) == 0x0C);

}

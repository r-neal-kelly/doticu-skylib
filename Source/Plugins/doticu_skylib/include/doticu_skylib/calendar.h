/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/calendar_now.h"
#include "doticu_skylib/enum.h"
#include "doticu_skylib/enum_calendar_date_weekday.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Global_t;

    class Calendar_t    // Calendar
    {
    public:
        static constexpr Float_t    DEFAULT_YEAR            = 201.0f;
        static constexpr Float_t    DEFAULT_MONTH           = 7.0f;
        static constexpr Float_t    DEFAULT_DAY             = 17.0f;
        static constexpr Float_t    DEFAULT_HOUR            = 8.0f;
        static constexpr Float_t    DEFAULT_DAYS_PASSED     = 1.0f;
        static constexpr Float_t    DEFAULT_TIME_SCALE      = 20.0f;

        static constexpr Float_t    DAYS_PER_YEAR           = 365.0f;

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                SELF = 0x01EC0A80, // 514287
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        static Calendar_t&                      Self();
        static maybe<Calendar_Now_t>            Days_Passed_Now(Float_t days_passed, Bool_t do_replicate_bugs);
        static maybe<Calendar_Date_Weekday_e>   Days_Passed_Weekday(Float_t days_passed);

    public:
        u64                 pad_00;             // 00
        maybe<Global_t*>    year;               // 08
        maybe<Global_t*>    month;              // 10
        maybe<Global_t*>    day;                // 18
        maybe<Global_t*>    hour;               // 20
        maybe<Global_t*>    days_passed;        // 28
        maybe<Global_t*>    time_scale;         // 30
        u32                 midnights_passed;   // 38
        Float_t             raw_days_passed;    // 3C

    public:
        maybe<Calendar_Now_t>           Now() const;
        void                            Now(some<Calendar_Now_t> now);

        maybe<Calendar_Date_t>          Date() const;
        void                            Date(some<Calendar_Date_t> date);
        maybe<Calendar_Date_Month_t>    Month() const;
        void                            Month(some<Calendar_Date_Month_t> month);
        maybe<Calendar_Date_Day_t>      Day() const;
        void                            Day(some<Calendar_Date_Day_t> day);
        maybe<Calendar_Date_Year_t>     Year() const;
        void                            Year(some<Calendar_Date_Year_t> year);

        maybe<Calendar_Time_t>          Time() const;
        void                            Time(some<Calendar_Time_t> time);
        maybe<Calendar_Time_24_t>       Time_24() const;
        void                            Time_24(some<Calendar_Time_24_t> time_24);
        maybe<Calendar_Time_12_t>       Time_12() const;
        void                            Time_12(some<Calendar_Time_12_t> time_12);
        maybe<Calendar_Time_Hour_24_t>  Hour_24() const;
        void                            Hour_24(some<Calendar_Time_Hour_24_t> hour_24);
        maybe<Calendar_Time_Hour_12_t>  Hour_12() const;
        void                            Hour_12(some<Calendar_Time_Hour_12_t> hour_12);
        maybe<Calendar_Time_Minute_t>   Minute() const;
        void                            Minute(some<Calendar_Time_Minute_t> minute);
        maybe<Calendar_Time_AM_PM_e>    AM_PM() const;
        void                            AM_PM(some<Calendar_Time_AM_PM_e> am_pm);

        maybe<Calendar_Now_t>           Days_Passed_Now() const;
        maybe<Calendar_Date_Weekday_e>  Days_Passed_Weekday() const;

    public:
        void    Log_Now(std::string indent = "") const;
    };
    STATIC_ASSERT(sizeof(Calendar_t) == 0x40);

}

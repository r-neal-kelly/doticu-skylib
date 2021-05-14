/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Global_t;

    class Calendar_t    // Calendar
    {
    public:
        static Calendar_t& Self();

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
        u16     Year() const;
        void    Year(u16 value);
        u16     Month() const;
        void    Month(u16 value);
        u16     Day() const;
        void    Day(u16 value);
        u16     Hour() const;
        void    Hour(u16 value);
        u16     Minute() const;
        void    Minute(u16 value);

    public:
        void    Log(std::string indent = "") const;
    };
    STATIC_ASSERT(sizeof(Calendar_t) == 0x40);

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Day_e : public Enum_t<s8>
    {
    public:
        enum : value_type
        {
            ANY                     = -1,
            SUNDAY                  = 0,
            MONDAY                  = 1,
            TUESDAY                 = 2,
            WEDNESDAY               = 3,
            THURSDAY                = 4,
            FRIDAY                  = 5,
            SATURDAY                = 6,
            WEEKDAYS                = 7,
            WEEKENDS                = 8,
            MONDAY_WEDNESDAY_FRIDAY = 9,
            TUESDAY_THURSDAY        = 10,

            _END_,
        };
        using Enum_t::Enum_t;
    };

}

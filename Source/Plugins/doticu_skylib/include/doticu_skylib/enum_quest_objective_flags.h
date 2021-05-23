/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Quest_Objective_Flags_e :
        public Enum_t<u32>
    {
    public:
        enum enum_type : value_type
        {
            OR_WITH_PREVIOUS    = static_cast<value_type>(1 << 0),
            DONT_TRACK_STATS    = static_cast<value_type>(1 << 1),
        };

    public:
        using Enum_t::Enum_t;
    };

}

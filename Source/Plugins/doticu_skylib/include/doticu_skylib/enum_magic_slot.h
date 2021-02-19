/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Magic_Slot_e :
        public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            LEFT_HAND       = 0,
            RIGHT_HAND      = 1,
            UNK_2           = 2,
            POWER_OR_SHOUT  = 3,

            _TOTAL_,
        };
        using Enum_t::Enum_t;
    };

}

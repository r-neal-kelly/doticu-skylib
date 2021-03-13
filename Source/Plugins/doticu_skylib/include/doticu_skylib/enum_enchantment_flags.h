/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Enchantment_Flags_e :
        public Enum_t<u32>
    {
    public:
        enum enum_type : value_type
        {
            NO_AUTO_CALC            = static_cast<value_type>(1 << 0),
            IS_FOOD_ITEM            = static_cast<value_type>(1 << 1),
            UNK_02                  = static_cast<value_type>(1 << 2),
            EXTEND_RECAST_DURATION  = static_cast<value_type>(1 << 3),
        };

    public:
        using Enum_t::Enum_t;
    };

}

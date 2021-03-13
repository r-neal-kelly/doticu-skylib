/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Magic_Type_e :
        public Enum_t<u32>
    {
    public:
        enum enum_type : value_type
        {
            SPELL           = 0,
            DISEASE         = 1,
            POWER           = 2,
            LESSER_POWER    = 3,
            ABILITY         = 4,
            POISON          = 5,
            ENCHANTMENT     = 6,
            POTION          = 7,
            INGREDIENT      = 8,
            LEVELED_SPELL   = 9,
            ADDICTION       = 10,
            VOICE           = 11,
            STAFF           = 12,
            SCROLL          = 13,
        };
        using Enum_t::Enum_t;
    };

}

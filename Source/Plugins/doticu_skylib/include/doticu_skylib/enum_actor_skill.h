/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Actor_Skill_e : public Enum_t<u8>
    {
    public:
        enum : value_type
        {
            ONE_HANDED  = 0,
            TWO_HANDED  = 1,
            MARKSMAN    = 2,
            BLOCK       = 3,
            SMITHING    = 4,
            HEAVY_ARMOR = 5,
            LIGHT_ARMOR = 6,
            PICKPOCKET  = 7,
            LOCKPICKING = 8,
            SNEAK       = 9,
            ALCHEMY     = 10,
            SPEECHCRAFT = 11,
            ALTERATION  = 12,
            CONJURATION = 13,
            DESTRUCTION = 14,
            ILLUSION    = 15,
            RESTORATION = 16,
            ENCHANTING  = 17,

            _TOTAL_,
        };
        using Enum_t::Enum_t;
    };

}

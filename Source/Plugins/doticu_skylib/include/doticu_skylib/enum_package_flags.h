/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Package_Flags_e : public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            OFFERS_SERVICES                 = 1 << 0,
            MUST_COMPLETE                   = 1 << 2,
            MAINTAIN_SPEED_AT_GOAL          = 1 << 3,
            UNLOCKS_DOORS_AT_PACKAGE_START  = 1 << 6,
            UNLOCKS_DOORS_AT_PACKAGE_END    = 1 << 7,
            CONTINUE_IF_NEAR_PC             = 1 << 9,
            ONLY_ONCE_PER_DAY               = 1 << 10,
            ALLOW_PREFERRED_SPEED           = 1 << 13,
            ALWAYS_SNEAK                    = 1 << 17,
            ALLOW_SWIMMING                  = 1 << 18,
            IGNORE_COMBAT                   = 1 << 20,
            HIDE_WEAPONS                    = 1 << 21,
            KEEP_WEAPONS_DRAWN              = 1 << 23,
            SKIP_COMBAT_ALERT               = 1 << 27,
            WEAR_SLEEP_OUTFIT               = 1 << 29,
        };
        using Enum_t::Enum_t;
    };

}

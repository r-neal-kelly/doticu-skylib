/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Weapon_Flags_1_e :
        public Enum_t<u16>
    {
    public:
        enum enum_type : value_type
        {
            IS_ONLY_FOR_PLAYER          = static_cast<value_type>(1 << 0),
            NPC_USES_AMMO               = static_cast<value_type>(1 << 1),
            HAS_FIXED_RANGE             = static_cast<value_type>(1 << 5),
            ISNT_USED_IN_NORMAL_COMBAT  = static_cast<value_type>(1 << 6),
            ISNT_HOSTILE                = static_cast<value_type>(1 << 12),
            IS_BOUND                    = static_cast<value_type>(1 << 13),
        };

    public:
        using Enum_t::Enum_t;
    };

    class Weapon_Flags_2_e :
        public Enum_t<u8>
    {
    public:
        enum enum_type : value_type
        {
            IGNORES_NORMAL_WEAPON_RESISTANCE    = static_cast<value_type>(1 << 0),
            CANT_DROP                           = static_cast<value_type>(1 << 3),
            ISNT_PLAYABLE                       = static_cast<value_type>(1 << 7),
        };

    public:
        using Enum_t::Enum_t;
    };

}

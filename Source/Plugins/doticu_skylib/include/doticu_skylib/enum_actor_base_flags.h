/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Actor_Base_Flags_e :
        public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            IS_FEMALE                       = static_cast<value_type>(1 << 0),
            IS_ESSENTIAL                    = static_cast<value_type>(1 << 1),
            IS_CHARGEN_FACE_PRESET          = static_cast<value_type>(1 << 2),
            DOES_RESPAWN                    = static_cast<value_type>(1 << 3),
            DOES_AUTO_CALCUATE_STATS        = static_cast<value_type>(1 << 4),
            IS_UNIQUE                       = static_cast<value_type>(1 << 5),
            DOESNT_AFFECT_STEALTH_METER     = static_cast<value_type>(1 << 6),
            HAS_PC_LEVEL_MULTIPLIER         = static_cast<value_type>(1 << 7),
            DOES_USE_TEMPLATE               = static_cast<value_type>(1 << 8),
            IS_PROTECTED                    = static_cast<value_type>(1 << 11),
            IS_SUMMONABLE                   = static_cast<value_type>(1 << 14),
            DOESNT_BLEED                    = static_cast<value_type>(1 << 16),
            HAS_BLEEDOUT_OVERRIDE           = static_cast<value_type>(1 << 18),
            HAS_OPPOSITE_GENDER_ANIMATIONS  = static_cast<value_type>(1 << 19),
            IS_SIMPLE_ACTOR                 = static_cast<value_type>(1 << 20),
            HAS_LOOPED_SCRIPT               = static_cast<value_type>(1 << 21),
            HAS_LOOPED_AUDIO                = static_cast<value_type>(1 << 28),
            IS_GHOST                        = static_cast<value_type>(1 << 29),
            IS_INVULNERABLE                 = static_cast<value_type>(1 << 31),
        };
        using Enum_t::Enum_t;
    };

}

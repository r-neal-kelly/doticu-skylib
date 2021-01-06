/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Actor_Base_Flags_e : public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            IS_FEMALE                       = 1lu << 0,
            IS_ESSENTIAL                    = 1lu << 1,
            IS_CHARGEN_FACE_PRESET          = 1lu << 2,
            DOES_RESPAWN                    = 1lu << 3,
            DOES_AUTO_CALCUATE_STATS        = 1lu << 4,
            IS_UNIQUE                       = 1lu << 5,
            DOESNT_AFFECT_STEALTH_METER     = 1lu << 6,
            HAS_PC_LEVEL_MULTIPLIER         = 1lu << 7,
            DOES_USE_TEMPLATE               = 1lu << 8,
            IS_PROTECTED                    = 1lu << 11,
            IS_SUMMONABLE                   = 1lu << 14,
            DOESNT_BLEED                    = 1lu << 16,
            HAS_BLEEDOUT_OVERRIDE           = 1lu << 18,
            HAS_OPPOSITE_GENDER_ANIMATIONS  = 1lu << 19,
            IS_SIMPLE_ACTOR                 = 1lu << 20,
            HAS_LOOPED_SCRIPT               = 1lu << 21,
            HAS_LOOPED_AUDIO                = 1lu << 28,
            IS_GHOST                        = 1lu << 29,
            IS_INVULNERABLE                 = 1lu << 31,
        };
        using Enum_t::Enum_t;
    };

}

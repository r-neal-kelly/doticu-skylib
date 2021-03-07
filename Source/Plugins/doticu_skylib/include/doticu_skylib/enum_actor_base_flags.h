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
        enum enum_type : value_type
        {
            IS_FEMALE                       = static_cast<value_type>(1 << 0),
            IS_ESSENTIAL                    = static_cast<value_type>(1 << 1),
            IS_CHARGEN_FACE_PRESET          = static_cast<value_type>(1 << 2),
            DOES_RESPAWN                    = static_cast<value_type>(1 << 3),
            DOES_AUTO_CALCULATE_STATS       = static_cast<value_type>(1 << 4),
            IS_UNIQUE                       = static_cast<value_type>(1 << 5),
            DOESNT_AFFECT_STEALTH_METER     = static_cast<value_type>(1 << 6),
            HAS_PC_LEVEL_MULTIPLIER         = static_cast<value_type>(1 << 7),
            UNK_08                          = static_cast<value_type>(1 << 8), // maybe something to do with sound templates
            UNK_09                          = static_cast<value_type>(1 << 9),
            UNK_10                          = static_cast<value_type>(1 << 10),
            IS_PROTECTED                    = static_cast<value_type>(1 << 11),
            UNK_12                          = static_cast<value_type>(1 << 12),
            UNK_13                          = static_cast<value_type>(1 << 13),
            IS_SUMMONABLE                   = static_cast<value_type>(1 << 14),
            UNK_15                          = static_cast<value_type>(1 << 15),
            DOESNT_BLEED                    = static_cast<value_type>(1 << 16),
            UNK_17                          = static_cast<value_type>(1 << 17),
            HAS_BLEEDOUT_OVERRIDE           = static_cast<value_type>(1 << 18),
            HAS_OPPOSITE_GENDER_ANIMATIONS  = static_cast<value_type>(1 << 19),
            IS_SIMPLE_ACTOR                 = static_cast<value_type>(1 << 20),
            HAS_LOOPED_SCRIPT               = static_cast<value_type>(1 << 21),
            UNK_22                          = static_cast<value_type>(1 << 22),
            UNK_23                          = static_cast<value_type>(1 << 23),
            UNK_24                          = static_cast<value_type>(1 << 24),
            UNK_25                          = static_cast<value_type>(1 << 25),
            UNK_26                          = static_cast<value_type>(1 << 26),
            UNK_27                          = static_cast<value_type>(1 << 27),
            HAS_LOOPED_AUDIO                = static_cast<value_type>(1 << 28),
            IS_GHOST                        = static_cast<value_type>(1 << 29),
            UNK_30                          = static_cast<value_type>(1 << 30),
            IS_INVULNERABLE                 = static_cast<value_type>(1 << 31),
        };

    public:
        using Enum_t::Enum_t;

    public:
        void Log(std::string indent = "");
    };

}

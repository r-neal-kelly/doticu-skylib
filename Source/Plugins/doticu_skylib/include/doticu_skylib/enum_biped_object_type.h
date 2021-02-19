/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Biped_Object_Type_e : // BIPED_OBJECT
        public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            _NONE_              = static_cast<value_type>(-1),

            HEAD                = 0,
            HAIR                = 1,
            BODY                = 2,
            HANDS               = 3,
            FOREARMS            = 4,
            AMULET              = 5,
            RING                = 6,
            FEET                = 7,
            CALVES              = 8,
            SHIELD              = 9,
            TAIL                = 10,
            LONG_HAIR           = 11,
            CIRCLET             = 12,
            EARS                = 13,
            DECAPTIATED_HEAD    = 20,
            DECAPITATED_NECK    = 21,
            FX                  = 31,
            HAND_TO_HAND_MELEE  = 32,
            SWORD_MELEE         = 33,
            DAGGER_MELEE        = 34,
            AXE_MELEE           = 35,
            MACE_MELEE          = 36,
            TWO_HAND_MELEE      = 37,
            BOW                 = 38,
            STAFF               = 39,
            CROSSBOW            = 40,
            QUIVER              = 41,

            _TOTAL_             = 42,
        };
        using Enum_t::Enum_t;
    };

}

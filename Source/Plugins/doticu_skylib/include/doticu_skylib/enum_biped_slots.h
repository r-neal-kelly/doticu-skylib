/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Biped_Slots_e : public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            HEAD                = 1lu << 0,
            HAIR                = 1lu << 1,
            BODY                = 1lu << 2,
            HANDS               = 1lu << 3,
            FOREARMS            = 1lu << 4,
            AMULET              = 1lu << 5,
            RING                = 1lu << 6,
            FEET                = 1lu << 7,
            CALVES              = 1lu << 8,
            SHIELD              = 1lu << 9,
            TAIL                = 1lu << 10,
            LONG_HAIR           = 1lu << 11,
            CIRCLET             = 1lu << 12,
            EARS                = 1lu << 13,
            DECAPTIATED_HEAD    = 1lu << 20,
            DECAPITATED_NECK    = 1lu << 21,
            FX                  = 1lu << 31,
        };
        using Enum_t::Enum_t;
    };

}

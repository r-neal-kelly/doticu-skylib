/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Actor_Critical_Stage_e : public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            NONE                = 0,
            GOO_START           = 1,
            GOO_STOP            = 2,
            DISINTEGRATE_START  = 3,
            DISINTEGRATE_STOP   = 4,
        };
        using Enum_t::Enum_t;
    };

}

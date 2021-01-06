/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Weapon_State_e : Enum_t<u8>
    {
        enum : value_type
        {
            SHEATHED            = 0,
            WANTS_TO_DRAW       = 1,
            DRAWING             = 2,
            DRAWN               = 3,
            WANTS_TO_SHEATHE    = 4,
            SHEATHING           = 5,
        };
        using Enum_t::Enum_t;
    };

}

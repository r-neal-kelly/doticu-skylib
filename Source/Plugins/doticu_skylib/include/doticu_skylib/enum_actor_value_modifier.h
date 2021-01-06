/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Actor_Value_Modifier_e : public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            PERMANENT   = 0,
            TEMPORARY   = 1,
            DAMAGE      = 2,
            INVALID     = 3,
        };
        using Enum_t::Enum_t;
    };

}

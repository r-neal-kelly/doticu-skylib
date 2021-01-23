/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Dialogue_Branch_Flags_e : public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            TOP_LEVEL   = static_cast<value_type>(1 << 0),
            BLOCKING    = static_cast<value_type>(1 << 1),
            EXCLUSIVE   = static_cast<value_type>(1 << 2),
        };
        using Enum_t::Enum_t;
    };

}

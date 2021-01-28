/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Reference_Count_Flags_e : public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            COUNT_MASK  = static_cast<value_type>(0x3FF),
            IS_VALID    = static_cast<value_type>(1 << 10),
        };
        using Enum_t::Enum_t;
    };

}

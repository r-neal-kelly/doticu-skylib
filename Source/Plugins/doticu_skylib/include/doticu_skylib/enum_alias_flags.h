/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Alias_Flags_e : public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            // ...
            IS_ESSENTIAL    = 1 << 6,
            // ...
            IS_PROTECTED    = 1 << 10,
            // ...
        };
        using Enum_t::Enum_t;
    };

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Static_Flags_e : public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            NONE = 0,
        };
        using Enum_t::Enum_t;
    };

}

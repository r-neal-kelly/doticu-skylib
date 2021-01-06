/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Alias_Fill_e : public Enum_t<u16>
    {
    public:
        enum : value_type
        {
            CONDITION   = 0,
            FORCED      = 1,
            // ...
        };
        using Enum_t::Enum_t;
    };

}

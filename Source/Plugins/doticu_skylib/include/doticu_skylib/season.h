/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Season_e : public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            NONE    = static_cast<u32>(-1),

            SPRING  = 0,
            SUMMER  = 1,
            FALL    = 2,
            WINTER  = 3,

            _END_,
        };
        using Enum_t::Enum_t;
    };

}

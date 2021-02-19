/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Race_Size_e :
        public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            SMALL       = 0,
            MEDIUM      = 1,
            LARGE       = 2,
            EXTRA_LARGE = 3,

            _TOTAL_,
        };
        using Enum_t::Enum_t;
    };

}

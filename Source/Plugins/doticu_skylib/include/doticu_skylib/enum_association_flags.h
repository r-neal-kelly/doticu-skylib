/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Association_Flags_e :
        public Enum_t<u32>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_      = 0,

            IS_FAMILY   = static_cast<value_type>(1 << 0),
        };

    public:
        using Enum_t::Enum_t;
    };

}

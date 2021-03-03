/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Face_Part_Type_e :
        public Enum_t<u32>
    {
    public:
        enum enum_type : value_type
        {
            NOSE        = 0x0,
            UNKNOWN_1   = 0x1,
            EYES        = 0x2,
            MOUTH       = 0x3,

            _TOTAL_     = 0x4,
        };
        using Enum_t::Enum_t;
    };

}

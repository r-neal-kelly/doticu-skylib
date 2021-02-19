/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Sex_e :
        public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            _NONE_  = static_cast<value_type>(-1),

            MALE    = 0,
            FEMALE  = 1,

            _TOTAL_,
        };

    public:
        using Enum_t::Enum_t;

    public:
        static const char* To_String(Sex_e sex_e);
    };

}

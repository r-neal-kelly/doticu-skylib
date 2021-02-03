/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Crime_Type_e : public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            _NONE_      = static_cast<value_type>(~0),
            _TOTAL_     = static_cast<value_type>(7),

            STEAL       = static_cast<value_type>(0),
            PICKPOCKET  = static_cast<value_type>(1),
            TRESPASS    = static_cast<value_type>(2),
            ATTACK      = static_cast<value_type>(3),
            MURDER      = static_cast<value_type>(4),
            ESCAPE      = static_cast<value_type>(5),
            UNUSED      = static_cast<value_type>(6),
        };
        using Enum_t::Enum_t;
    };

}

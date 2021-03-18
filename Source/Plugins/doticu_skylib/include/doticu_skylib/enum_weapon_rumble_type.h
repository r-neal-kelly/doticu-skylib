/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Weapon_Rumble_Type_e :
        public Enum_t<u32>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_              = static_cast<value_type>(-1),

            CONSTANT            = static_cast<value_type>(0),
            PERIODIC_SQUARE     = static_cast<value_type>(1),
            PERIODIC_TRIANGLE   = static_cast<value_type>(2),
            PERIODIC_SAWTOOTH   = static_cast<value_type>(3),

            _TOTAL_             = static_cast<value_type>(4),
        };

    public:
        using Enum_t::Enum_t;
    };

}

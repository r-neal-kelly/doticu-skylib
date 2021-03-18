/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Weapon_Hit_Type_e :
        public Enum_t<u32>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_                          = static_cast<value_type>(-1),

            NORMAL                          = static_cast<value_type>(0),
            ONLY_DISMEMBERS                 = static_cast<value_type>(1),
            ONLY_EXPLODES                   = static_cast<value_type>(2),
            NEVER_DISMEMBERS_OR_EXPLODES    = static_cast<value_type>(3),

            _TOTAL_                         = static_cast<value_type>(4),
        };

    public:
        using Enum_t::Enum_t;
    };

}

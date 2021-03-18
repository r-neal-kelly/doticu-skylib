/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Weapon_Animation_Type_e :
        public Enum_t<u8>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_                  = static_cast<value_type>(-1),

            HAND_TO_HAND            = static_cast<value_type>(0),
            SWORD                   = static_cast<value_type>(1),
            DAGGER                  = static_cast<value_type>(2),
            WARAXE                  = static_cast<value_type>(3),
            MACE                    = static_cast<value_type>(4),
            GREATSWORD              = static_cast<value_type>(5),
            BATTLEAXE_OR_WARHAMMER  = static_cast<value_type>(6),
            BOW                     = static_cast<value_type>(7),
            STAFF                   = static_cast<value_type>(8),
            CROSSBOW                = static_cast<value_type>(9),

            _TOTAL_                 = static_cast<value_type>(10),
        };

    public:
        using Enum_t::Enum_t;
    };

}

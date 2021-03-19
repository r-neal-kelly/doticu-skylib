/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Ammo_Flags_e :
        public Enum_t<u8>
    {
    public:
        enum enum_type : value_type
        {
            IGNORES_NORMAL_WEAPON_RESISTANCE    = static_cast<value_type>(1 << 0),
            ISNT_PLAYABLE                       = static_cast<value_type>(1 << 1),
            ISNT_BOLT                           = static_cast<value_type>(1 << 2),
        };

    public:
        using Enum_t::Enum_t;
    };

}

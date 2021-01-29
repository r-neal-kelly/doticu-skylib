/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Havok_Collidable_Flags_e : public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            NO_COLLISION            = static_cast<value_type>(1 << 14),

            COLLISION_LAYER_MASK    = static_cast<value_type>(0x7F),
        };
        using Enum_t::Enum_t;
    };

}

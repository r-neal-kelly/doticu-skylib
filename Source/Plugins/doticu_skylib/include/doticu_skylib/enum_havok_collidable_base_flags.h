/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Havok_Collidable_Base_Flags_e : public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            ACTIVE = static_cast<value_type>(1 << 0),
            // ...
        };
        using Enum_t::Enum_t;
    };

}

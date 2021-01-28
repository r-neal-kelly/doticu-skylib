/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Actor_Controller_Flags_e : public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            NO_ACTOR_COLLISIONS = static_cast<value_type>(1 << 27),
        };
        using Enum_t::Enum_t;
    };

}

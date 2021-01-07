/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Container_Flags_e : public Enum_t<u8>
    {
    public:
        enum : value_type
        {
            ALLOW_ANIMATION_SOUNDS  = 1 << 0,
            DOES_RESPAWN            = 1 << 1,
            DOES_SHOW_OWNER         = 1 << 2,
        };
        using Enum_t::Enum_t;
    };

}

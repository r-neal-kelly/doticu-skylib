/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Package_Interrupt_e : public Enum_t<u8>
    {
    public:
        enum : value_type
        {
            NONE            = static_cast<value_type>(-1),

            SPECTATOR       = 0,
            OBSERVE_DEAD    = 1,
            GUARD_WARN      = 2,
            COMBAT          = 3,

            _END_,
        };
        using Enum_t::Enum_t;
    };

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Preferred_Speed_e : public Enum_t<u8>
    {
    public:
        enum : value_type
        {
            WALK        = 0,
            JOG         = 1,
            RUN         = 2,
            FAST_WALK   = 3,
        };
        using Enum_t::Enum_t;
    };

}

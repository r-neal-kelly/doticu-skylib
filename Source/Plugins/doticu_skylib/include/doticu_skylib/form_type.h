/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Form_Type_e : public Enum_t<u8>
    {
    public:
        enum : u8
        {
            ACTOR_BASE          = 0x2B,
            LEVELED_ACTOR_BASE  = 0x2C,

            ACTOR               = 0x3E,
        };
        using Enum_t::Enum_t;
    };

}

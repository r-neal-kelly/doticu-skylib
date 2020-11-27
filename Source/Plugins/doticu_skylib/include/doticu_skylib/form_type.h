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
            SCRIPT              = 0x13, // SCPT

            ACTOR_BASE          = 0x2B, // NPC_
            LEVELED_ACTOR_BASE  = 0x2C, // LVLN

            REFERENCE           = 0X3D, // REFR
            ACTOR               = 0x3E, // ACHR
        };
        using Enum_t::Enum_t;
    };

}

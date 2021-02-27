/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Life_State_e :
        public Enum_t<u8>
    {
    public:
        enum enum_type : value_type
        {
            ALIVE           = 0x0,
            DYING           = 0x1,
            DEAD            = 0x2,
            UNCONSCIOUS     = 0x3,
            REANIMATED      = 0x4,
            RECYCLED        = 0x5,
            RESTRAINED      = 0x6,
            ESSENTIAL_KNEEL = 0x7,
            BLEEDOUT        = 0x8,
        };
        using Enum_t::Enum_t;
    };

}

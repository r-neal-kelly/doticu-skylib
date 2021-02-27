/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Fly_State_e :
        public Enum_t<u8>
    {
    public:
        enum enum_type : value_type
        {
            NONE        = 0x0,
            TAKE_OFF    = 0x1,
            CRUISING    = 0x2,
            HOVERING    = 0x3,
            LANDING     = 0x4,
            PERCHING    = 0x5,
            ACTION      = 0x6,
        };
        using Enum_t::Enum_t;
    };

}

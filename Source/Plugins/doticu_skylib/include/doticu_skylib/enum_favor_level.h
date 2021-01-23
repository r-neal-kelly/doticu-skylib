/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Favor_Level_e : public Enum_t<u8>
    {
    public:
        enum : value_type
        {
            NONE    = 0,
            SMALL   = 1,
            MEDIUM  = 2,
            LARGE   = 3,
        };
        using Enum_t::Enum_t;
    };

}

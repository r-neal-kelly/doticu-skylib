/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Soul_Level_e : public Enum_t<u8>
    {
    public:
        enum : value_type
        {
            NONE    = 0,
            PETTY   = 1,
            LESSER  = 2,
            COMMON  = 3,
            GREATER = 4,
            GRAND   = 5,
        };
        using Enum_t::Enum_t;
    };

}

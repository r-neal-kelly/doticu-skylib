/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Armor_e : public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            LIGHT_ARMOR = 0,
            HEAVY_ARMOR = 1,
            CLOTHING    = 2,
        };
        using Enum_t::Enum_t;
    };

}

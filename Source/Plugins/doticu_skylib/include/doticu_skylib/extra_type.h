/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Extra_Type_e : public Enum_t<u8>
    {
    public:
        enum : u8
        {
            FACTIONS_AND_RANKS  = 0x5B,

            ALIASES             = 0x88,
            LOCATION            = 0x89,
        };
        using Enum_t::Enum_t;
    };

}

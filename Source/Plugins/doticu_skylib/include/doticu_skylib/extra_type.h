/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Extra_Type_e : public Enum_t<u8>
    {
    public:
        enum : value_type
        {
            OWNER               = 0x21, // XOWN

            FACTIONS_AND_RANKS  = 0x5B, // XRNK

            ENCOUNTER_ZONE      = 0x70,

            ALIASES             = 0x88,
            LOCATION            = 0x89,
        };
        using Enum_t::Enum_t;
    };

}

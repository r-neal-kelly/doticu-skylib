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
            FOLLOWERS           = 0x1D,

            GHOST               = 0x1F,

            OWNER               = 0x21, // XOWN

            TALK_TO_PLAYER      = 0x54,

            FACTIONS_AND_RANKS  = 0x5B, // XRNK

            ENCOUNTER_ZONE      = 0x70,

            ALIASES             = 0x88,
            LOCATION            = 0x89,

            OUTFIT              = 0x8E,

            TEXT_DISPLAY        = 0x99,

            SOUL                = 0x9C,

            FLAGS               = 0xA0,
        };
        using Enum_t::Enum_t;
    };

}

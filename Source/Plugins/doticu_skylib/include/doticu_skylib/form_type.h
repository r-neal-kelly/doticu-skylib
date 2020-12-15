/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Form_Type_e : public Enum_t<u8>
    {
    public:
        static constexpr size_t MAX_TYPES = 0x8A;

        enum : u8
        {
            FORM                    = 0x00,

            KEYWORD                 = 0x04, // KYWD
            LOCATION_REFERENCE_TYPE = 0X05, // LCRT

            GLOBAL                  = 0x09, // GLOB
            FACTION                 = 0x0B, // FACT

            RACE                    = 0x0E, // RACE

            SCRIPT                  = 0x13, // SCPT

            ACTOR_BASE              = 0x2B, // NPC_
            LEVELED_ACTOR_BASE      = 0x2C, // LVLN

            CELL                    = 0x3C, // CELL
            REFERENCE               = 0x3D, // REFR
            ACTOR                   = 0x3E, // ACHR

            WORLDSPACE              = 0x47, // WRLD

            QUEST                   = 0x4D, // QUST

            LOCATION                = 0x68, // LCTN

            ALIAS_BASE              = 0x8B,
            ALIAS_REFERENCE         = 0x8C,
            ALIAS_LOCATION          = 0x8D,
        };
        using Enum_t::Enum_t;
    };

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    using Raw_Form_Type_t = u8;

    class Form_Type_Base_e : public Enum_Base_t<Raw_Form_Type_t>
    {
    public:
        enum : _BASE_TYPE_
        {
            FORM                    = 0x00,

            KEYWORD                 = 0x04, // KYWD
            LOCATION_REFERENCE_TYPE = 0X05, // LCRT

            GLOBAL                  = 0x09, // GLOB
            FACTION                 = 0x0B, // FACT

            RACE                    = 0x0E, // RACE

            SCRIPT                  = 0x13, // SCPT

            ACTIVATOR               = 0x18, // ACTI

            FLORA                   = 0x27, // FLOR

            ACTOR_BASE              = 0x2B, // NPC_
            LEVELED_ACTOR_BASE      = 0x2C, // LVLN

            CELL                    = 0x3C, // CELL
            REFERENCE               = 0x3D, // REFR
            ACTOR                   = 0x3E, // ACHR

            WORLDSPACE              = 0x47, // WRLD

            QUEST                   = 0x4D, // QUST

            LOCATION                = 0x68, // LCTN

            _END_                   = 0x8A,
        };
    };

    class Form_Type_e :
        public Form_Type_Base_e,
        public Enum_t<Raw_Form_Type_t>
    {
    public:
        using Enum_t::Enum_t;
    };
    STATIC_ASSERT(sizeof(Form_Type_e) == 0x1);

}

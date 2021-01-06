/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Cell_Flags_e : public Enum_t<u16>
    {
    public:
        enum : value_type
        {
            IS_INTERIOR         = 1 << 0,
            HAS_WATER           = 1 << 1,
            CAN_TRAVEL_FROM     = 1 << 2,
            HASNT_LOD_WATER     = 1 << 3,
            HAS_TEMP_DATA       = 1 << 4,
            IS_PUBLIC           = 1 << 5,
            IS_HAND_CHANGED     = 1 << 6,
            HAS_SKY             = 1 << 7,
            HAS_SKY_LIGHTING    = 1 << 8,
        };
        using Enum_t::Enum_t;
    };

}

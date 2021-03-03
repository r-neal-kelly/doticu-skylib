/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Face_Morph_Type_e :
        public Enum_t<u32>
    {
    public:
        enum enum_type : value_type
        {
            NOSE_LONG_SHORT         = 0x00,
            NOSE_UP_DOWN            = 0x01,
            JAW_UP_DOWN             = 0x02,
            JAW_NARROW_WIDE         = 0x03,
            JAW_FORWARD_BACK        = 0x04,
            CHEEKS_UP_DOWN          = 0x05,
            CHEEKS_FORWARD_BACK     = 0x06,
            EYES_UP_DOWN            = 0x07,
            EYES_IN_OUT             = 0x08,
            BROWS_UP_DOWN           = 0x09,
            BROWS_IN_OUT            = 0x0A,
            BROWS_FORWARD_BACK      = 0x0B,
            LIPS_UP_DOWN            = 0x0C,
            LIPS_IN_OUT             = 0x0D,
            CHIN_NARROW_WIDE        = 0x0E,
            CHIN_UP_DOWN            = 0x0F,
            CHIN_UNDERBITE_OVERBITE = 0x10,
            EYES_FORWARD_BACK       = 0x11,
            UNKNOWN_12              = 0x12,

            _TOTAL_                 = 0x13,
        };
        using Enum_t::Enum_t;
    };

}

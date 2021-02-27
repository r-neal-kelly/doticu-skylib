/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Attack_State_e :
        public Enum_t<u8>
    {
    public:
        enum enum_type : value_type
        {
            NONE                = 0x00,
            DRAW                = 0x01,
            SWING               = 0x02,
            HIT                 = 0x03,
            NEXT_ATTACK         = 0x04,
            FOLLOW_THROUGH      = 0x05,
            BASH                = 0x06,
            UNK_07              = 0x07,
            BOW_DRAW            = 0x08,
            BOW_ATTACHED        = 0x09,
            BOW_DRAWN           = 0x0A,
            BOW_RELEASING       = 0x0B,
            BOW_RELEASED        = 0x0C,
            BOW_NEXT_ATTACK     = 0x0D,
            BOW_FOLLOW_THROUGH  = 0x0E,
            FIRE                = 0x0F,
            FIRING              = 0x10,
            FIRED               = 0x11,
        };
        using Enum_t::Enum_t;
    };

}

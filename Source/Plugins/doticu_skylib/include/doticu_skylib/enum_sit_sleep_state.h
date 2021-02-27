/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Sit_Sleep_State_e :
        public Enum_t<u8>
    {
    public:
        enum enum_type : value_type
        {
            NORMAL                      = 0x0,
            WANTS_TO_SIT                = 0x1,
            WAITING_FOR_SIT_ANIMATION   = 0x2,
            SITTING                     = 0x3,
            WANTS_TO_STAND              = 0x4,
            WANTS_TO_SLEEP              = 0x5,
            WAITING_FOR_SLEEP_ANIMATION = 0x6,
            SLEEPING                    = 0x7,
            WANTS_TO_WAKE               = 0x8,
        };
        using Enum_t::Enum_t;
    };

}

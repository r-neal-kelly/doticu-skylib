/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#undef OUT

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Knock_State_e :
        public Enum_t<u8>
    {
    public:
        enum enum_type : value_type
        {
            NORMAL              = 0x0,
            EXPLODE             = 0x1,
            EXPLODE_LEAD_IN     = 0x2,
            OUT                 = 0x3,
            OUT_LEAD_IN         = 0x4,
            QUEUED              = 0x5,
            GET_UP              = 0x6,
            DOWN                = 0x7,
            WAIT_FOR_TASK_QUEUE = 0x8,
        };
        using Enum_t::Enum_t;
    };

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Message_Flags_e : public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            MESSAGE_BOX     = 1 << 0,
            INITIAL_DELAY   = 1 << 1,
        };
        using Enum_t::Enum_t;
    };

}

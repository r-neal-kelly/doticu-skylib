/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Extra_Flags_e : public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            BLOCK_ACTIVATION        = 1 << 0,
            BLOCK_PLAYER_ACTIVATION = 1 << 1,
            BLOCK_LOAD_EVENTS       = 1 << 2,
            BLOCK_ACTIVATION_TEXT   = 1 << 3,
            PLAYER_HAS_TAKEN        = 1 << 5,
        };
        using Enum_t::Enum_t;
    };

}

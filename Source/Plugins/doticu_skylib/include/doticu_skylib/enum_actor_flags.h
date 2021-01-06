/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Actor_Flags_1_e : public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            PROCESS_AI          = 1 << 1,
            RESET_AI            = 1 << 17,
            IS_PLAYER_TEAMMATE  = 1 << 26,
            IS_PARALYZED        = static_cast<u32>(1 << 31),
        };
        using Enum_t::Enum_t;
    };

    class Actor_Flags_2_e : public Enum_t<u32>
    {
    public:
        enum : value_type
        {

        };
        using Enum_t::Enum_t;
    };

}

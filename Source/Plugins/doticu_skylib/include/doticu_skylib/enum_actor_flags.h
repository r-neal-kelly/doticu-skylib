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
            IS_PARALYZED        = static_cast<value_type>(1 << 31),
        };
        using Enum_t::Enum_t;
    };

    class Actor_Flags_2_e : public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            IS_MOUNT                    = 1 << 1,
            CAN_DO_FAVOR                = 1 << 7,
            CAN_SPEAK                   = 1 << 13,
            IS_ESSENTIAL                = 1 << 18,
            IS_PROTECTED                = 1 << 19,
            IS_HIDDEN_FROM_STEALTH_EYE  = 1 << 26,
            IS_UNDERWATER               = static_cast<value_type>(1 << 31),
        };
        using Enum_t::Enum_t;
    };

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Actor_Flags_1_e :
        public Enum_t<u32>
    {
    public:
        enum enum_type : value_type
        {
            DO_PROCESS_AI       = static_cast<value_type>(1 << 1),
            DO_RESET_AI         = static_cast<value_type>(1 << 17),
            IS_PLAYER_TEAMMATE  = static_cast<value_type>(1 << 26),
            IS_PARALYZED        = static_cast<value_type>(1 << 31),
        };

    public:
        using Enum_t::Enum_t;
    };

    class Actor_Flags_2_e :
        public Enum_t<u32>
    {
    public:
        enum enum_type : value_type
        {
            IS_MOUNT                    = static_cast<value_type>(1 << 1),
            CAN_DO_FAVORS               = static_cast<value_type>(1 << 7),
            CAN_SPEAK                   = static_cast<value_type>(1 << 13),
            IS_ESSENTIAL                = static_cast<value_type>(1 << 18),
            IS_PROTECTED                = static_cast<value_type>(1 << 19),
            IS_HIDDEN_FROM_STEALTH_EYE  = static_cast<value_type>(1 << 26),
            IS_UNDERWATER               = static_cast<value_type>(1 << 31),
        };
        using Enum_t::Enum_t;
    };

}

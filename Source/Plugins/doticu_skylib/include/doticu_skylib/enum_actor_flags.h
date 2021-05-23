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
            DO_PROCESS_AI           = static_cast<value_type>(1 << 1),
            IS_IN_COMBAT_SEARCH     = static_cast<value_type>(1 << 14),
            WILL_ATTACK_NEXT_THEFT  = static_cast<value_type>(1 << 15),
            DO_RESET_AI             = static_cast<value_type>(1 << 17),
            IS_IN_WATER             = static_cast<value_type>(1 << 18),
            IS_SWIMMING             = static_cast<value_type>(1 << 19),
            IS_PLAYER_TEAMMATE      = static_cast<value_type>(1 << 26),
            IS_PARALYZED            = static_cast<value_type>(1 << 31),
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
            IS_ANGRY_WITH_PLAYER        = static_cast<value_type>(1 << 11),
            CAN_SPEAK                   = static_cast<value_type>(1 << 13),
            WILL_ATTACK_ON_SIGHT        = static_cast<value_type>(1 << 15),
            IS_ESSENTIAL                = static_cast<value_type>(1 << 18),
            IS_PROTECTED                = static_cast<value_type>(1 << 19),
            CAN_ATTACK                  = static_cast<value_type>(1 << 20),
            CAN_CAST_MAGIC              = static_cast<value_type>(1 << 21),
            IS_IN_CRIME_SEARCH          = static_cast<value_type>(1 << 24),
            IS_HIDDEN_FROM_STEALTH_EYE  = static_cast<value_type>(1 << 26),
            CAN_MOVE                    = static_cast<value_type>(1 << 27),
            IS_UNDERWATER               = static_cast<value_type>(1 << 31),
        };

    public:
        using Enum_t::Enum_t;
    };

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Dialogue_Info_Flags_e : public Enum_t<u16>
    {
    public:
        enum : value_type
        {
            GOODBYE                     = static_cast<value_type>(1 << 0),
            RANDOM                      = static_cast<value_type>(1 << 1),
            SAY_ONCE                    = static_cast<value_type>(1 << 2),
            REQUIRES_PLAYER_ACTIVATION  = static_cast<value_type>(1 << 3),
            INFO_REFUSAL                = static_cast<value_type>(1 << 4),
            RANDOM_END                  = static_cast<value_type>(1 << 5),
            INVISIBLE_CONTINUE          = static_cast<value_type>(1 << 6),
            WALK_AWAY                   = static_cast<value_type>(1 << 7),
            INVISIBLE_WALK_AWAY         = static_cast<value_type>(1 << 8),
            FORCE_SUBTITLE              = static_cast<value_type>(1 << 9),
            CAN_MOVE_WHILE_GREETING     = static_cast<value_type>(1 << 10),
            HASNT_LIP_FILE              = static_cast<value_type>(1 << 11),
            REQUIRES_POST_PROCESSING    = static_cast<value_type>(1 << 12),
            AUDIO_OUTPUT_OVERRIDE       = static_cast<value_type>(1 << 13),
            SPENDS_FAVOR_POINTS         = static_cast<value_type>(1 << 14),
        };
        using Enum_t::Enum_t;
    };

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Package_Interrupts_e : public Enum_t<u16>
    {
    public:
        enum : value_type
        {
            ALLOW_HELLOS_TO_PLAYER      = 1 << 0,
            ALLOW_HELLOS_TO_NPCS        = 1 << 1,
            OBSERVE_COMBAT_BEHAVIOR     = 1 << 2,
            INSPECT_CORPSE_BEHAVIOR     = 1 << 3,
            REACT_TO_PLAYER_ACTIONS     = 1 << 4,
            COMMENT_ON_FRIENDLY_FIRE    = 1 << 5,
            ALLOW_AGGRO_RADIUS_BEHAVIOR = 1 << 6,
            ALLOW_IDLE_CHATTER          = 1 << 7,
            ALLOW_WORLD_INTERACTIONS    = 1 << 9,
        };
        using Enum_t::Enum_t;
    };

}

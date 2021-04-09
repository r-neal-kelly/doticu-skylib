/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Package_Interrupt_Flags_e :
        public Enum_t<u16>
    {
    public:
        enum enum_type : value_type
        {
            ALLOW_HELLOS_TO_PLAYER      = static_cast<value_type>(1 << 0),
            ALLOW_HELLOS_TO_NPCS        = static_cast<value_type>(1 << 1),
            OBSERVE_COMBAT              = static_cast<value_type>(1 << 2),
            INSPECT_CORPSES             = static_cast<value_type>(1 << 3),
            REACT_TO_PLAYER_ACTIONS     = static_cast<value_type>(1 << 4),
            COMMENT_ON_FRIENDLY_FIRE    = static_cast<value_type>(1 << 5),
            ALLOW_AGGRO_RADIUS          = static_cast<value_type>(1 << 6),
            ALLOW_IDLE_CHATTER          = static_cast<value_type>(1 << 7),
            ALLOW_WORLD_INTERACTIONS    = static_cast<value_type>(1 << 9),
        };

    public:
        using Enum_t::Enum_t;
    };

}

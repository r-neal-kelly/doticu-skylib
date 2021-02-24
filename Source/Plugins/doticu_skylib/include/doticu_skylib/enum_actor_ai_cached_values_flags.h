/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Actor_AI_Cached_Values_Flags_1_e :
        public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            CONDITION_PREVENTS_RUN          = static_cast<value_type>(1 << 0),
            HAS_ACTOR_BASE_OWNER            = static_cast<value_type>(1 << 1),
            HAS_UNDEAD_OWNER                = static_cast<value_type>(1 << 2),
            HAS_OWNER_IN_COMBATANT_FACTION  = static_cast<value_type>(1 << 3),
        };

    public:
        using Enum_t::Enum_t;
    };

    class Actor_AI_Cached_Values_Flags_2_e :
        public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            IS_GHOST = static_cast<value_type>(1 << 20),
        };
        using Enum_t::Enum_t;
    };

}

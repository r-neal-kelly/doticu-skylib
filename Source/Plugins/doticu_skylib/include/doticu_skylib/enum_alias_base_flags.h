/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Alias_Base_Flags_e :
        public Enum_t<u32>
    {
    public:
        enum enum_type : value_type
        {
            IS_RESERVED             = static_cast<value_type>(1 << 0),
            IS_OPTIONAL             = static_cast<value_type>(1 << 1),
            IS_QUEST_ITEM           = static_cast<value_type>(1 << 2),
            ALLOWS_REUSE            = static_cast<value_type>(1 << 3),
            ALLOWS_DEAD             = static_cast<value_type>(1 << 4),
            ONLY_LOADED             = static_cast<value_type>(1 << 5),
            IS_ESSENTIAL            = static_cast<value_type>(1 << 6),
            ALLOWS_DISABLED         = static_cast<value_type>(1 << 7),
            STORES_NAME             = static_cast<value_type>(1 << 8),
            ALLOWS_RESERVED         = static_cast<value_type>(1 << 9),
            IS_PROTECTED            = static_cast<value_type>(1 << 10),
            IS_FORCED_FROM_ALIAS    = static_cast<value_type>(1 << 11),
            ALLOWS_DESTROYED        = static_cast<value_type>(1 << 12),
            FINDS_CLOSEST_TO_PLAYER = static_cast<value_type>(1 << 13),
            USES_NAMES              = static_cast<value_type>(1 << 14),
            IS_INITIALLY_DISABLED   = static_cast<value_type>(1 << 15),
            ALLOWS_CLEARED          = static_cast<value_type>(1 << 16),
            CLEARS_NAME_ON_REMOVE   = static_cast<value_type>(1 << 17),
            ONLY_ACTORS             = static_cast<value_type>(1 << 18),
            IS_TRANSIENT            = static_cast<value_type>(1 << 19),
            CANT_BE_PICKPOCKETED    = static_cast<value_type>(1 << 21),
            IS_SCENE_OPTIONAL       = static_cast<value_type>(1 << 24),
        };
        using Enum_t::Enum_t;
    };

}

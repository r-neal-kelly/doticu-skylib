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
            UNK_20                  = static_cast<value_type>(1 << 20),
            CANT_BE_PICKPOCKETED    = static_cast<value_type>(1 << 21),
            UNK_22                  = static_cast<value_type>(1 << 22),
            UNK_23                  = static_cast<value_type>(1 << 23),
            IS_SCENE_OPTIONAL       = static_cast<value_type>(1 << 24),
            UNK_25                  = static_cast<value_type>(1 << 25),
            UNK_26                  = static_cast<value_type>(1 << 26),
            UNK_27                  = static_cast<value_type>(1 << 27),
            UNK_28                  = static_cast<value_type>(1 << 28),
            UNK_29                  = static_cast<value_type>(1 << 29),
            UNK_30                  = static_cast<value_type>(1 << 30),
            UNK_31                  = static_cast<value_type>(1 << 31),
        };

    public:
        using Enum_t::Enum_t;

    public:
        void Log(std::string indent = "")
        {
            SKYLIB_LOG(indent + "Alias_Base_Flags_e::Log");
            SKYLIB_LOG(indent + "{");

            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(IS_RESERVED));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(IS_OPTIONAL));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(IS_QUEST_ITEM));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(ALLOWS_REUSE));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(ALLOWS_DEAD));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(ONLY_LOADED));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(IS_ESSENTIAL));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(ALLOWS_DISABLED));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(STORES_NAME));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(ALLOWS_RESERVED));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(IS_PROTECTED));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(IS_FORCED_FROM_ALIAS));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(ALLOWS_DESTROYED));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(FINDS_CLOSEST_TO_PLAYER));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(USES_NAMES));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(IS_INITIALLY_DISABLED));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(ALLOWS_CLEARED));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(CLEARS_NAME_ON_REMOVE));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(ONLY_ACTORS));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(IS_TRANSIENT));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(UNK_20));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(CANT_BE_PICKPOCKETED));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(UNK_22));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(UNK_23));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(IS_SCENE_OPTIONAL));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(UNK_25));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(UNK_26));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(UNK_27));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(UNK_28));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(UNK_29));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(UNK_30));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(UNK_31));

            SKYLIB_LOG(indent + "}");
        }
    };

}

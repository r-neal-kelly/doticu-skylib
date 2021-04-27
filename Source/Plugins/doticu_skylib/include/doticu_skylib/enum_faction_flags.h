/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Faction_Flags_e :
        public Enum_t<u32>
    {
    public:
        enum enum_type : value_type
        {
            HIDDEN_FROM_NPC             = 1 << 0,
            SPECIAL_COMBAT              = 1 << 1,
            PLAYER_IS_EXPELLED          = 1 << 2,
            PLAYER_IS_ENEMY             = 1 << 3,
            TRACK_CRIME                 = 1 << 6,
            IGNORES_MURDER              = 1 << 7,
            IGNORES_ASSAULT             = 1 << 8,
            IGNORES_STEALING            = 1 << 9,
            IGNORES_TRESPASSING         = 1 << 10,
            DOESNT_REPORT_MEMBER_CRIME  = 1 << 11,
            USE_DEFAULT_CRIME_GOLD      = 1 << 12,
            IGNORES_PICKPOCKETING       = 1 << 13,
            IS_VENDOR                   = 1 << 14,
            CAN_BE_OWNER                = 1 << 15,
            IGNORES_WEREWOLF            = 1 << 16,
        };

    public:
        using Enum_t::Enum_t;

    public:
        inline void Log(std::string indent) const
        {
            SKYLIB_LOG(indent + "Faction_Flags_e::Log");
            SKYLIB_LOG(indent + "{");

            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(HIDDEN_FROM_NPC));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(SPECIAL_COMBAT));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(PLAYER_IS_EXPELLED));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(PLAYER_IS_ENEMY));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(TRACK_CRIME));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(IGNORES_MURDER));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(IGNORES_ASSAULT));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(IGNORES_STEALING));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(IGNORES_TRESPASSING));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(DOESNT_REPORT_MEMBER_CRIME));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(USE_DEFAULT_CRIME_GOLD));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(IGNORES_PICKPOCKETING));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(IS_VENDOR));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(CAN_BE_OWNER));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(IGNORES_WEREWOLF));

            SKYLIB_LOG(indent + "}");
        }
    };

}

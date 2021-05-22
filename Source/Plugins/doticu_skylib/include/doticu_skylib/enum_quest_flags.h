/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Quest_Flags_e :
        public Enum_t<u16>
    {
    public:
        enum enum_type : value_type
        {
            IS_ENABLED          = static_cast<value_type>(1 << 0),
            IS_COMPLETED        = static_cast<value_type>(1 << 1),
            DOES_START_ENABLED  = static_cast<value_type>(1 << 4),
            IS_DISPLAYED_IN_HUD = static_cast<value_type>(1 << 5),
            IS_FAILED           = static_cast<value_type>(1 << 6),
            DOES_RUN_ONCE       = static_cast<value_type>(1 << 8),
            IS_ACTIVE           = static_cast<value_type>(1 << 11),
        };

    public:
        using Enum_t::Enum_t;

    public:
        void Log(std::string indent = "") const
        {
            SKYLIB_LOG(indent + "Quest_Flags_e::Log");
            SKYLIB_LOG(indent + "{");

            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(IS_ENABLED));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(IS_COMPLETED));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(DOES_START_ENABLED));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(IS_DISPLAYED_IN_HUD));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(IS_FAILED));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(DOES_RUN_ONCE));
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(IS_ACTIVE));

            SKYLIB_LOG(indent + "}");
        }
    };

}

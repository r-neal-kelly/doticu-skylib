/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Quest_Flags_e : public Enum_t<u16>
    {
    public:
        enum : value_type
        {
            IS_ENABLED          = static_cast<value_type>(1 << 0),
            IS_COMPLETED        = static_cast<value_type>(1 << 1),
            DOES_START_ENABLED  = static_cast<value_type>(1 << 4),
            IS_DISPLAYED_IN_HUD = static_cast<value_type>(1 << 5),
            IS_FAILED           = static_cast<value_type>(1 << 6),
            DOES_RUN_ONCE       = static_cast<value_type>(1 << 8),
            IS_ACTIVE           = static_cast<value_type>(1 << 11),
        };
        using Enum_t::Enum_t;
    };

}

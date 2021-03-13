/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Magic_Effect_Flags_e :
        public Enum_t<u32>
    {
    public:
        enum enum_type : value_type
        {
            HOSTILE                 = static_cast<value_type>(1 << 0),
            RECOVER                 = static_cast<value_type>(1 << 1),
            DETRIMENTAL             = static_cast<value_type>(1 << 2),
            SNAP_TO_NAV_MESH        = static_cast<value_type>(1 << 3),
            NO_HIT_EVENT            = static_cast<value_type>(1 << 4),
            DISPEL_WITH_KEYWORDS    = static_cast<value_type>(1 << 8),
            NO_DURATION             = static_cast<value_type>(1 << 9),
            NO_MAGNITUDE            = static_cast<value_type>(1 << 10),
            NO_AREA                 = static_cast<value_type>(1 << 11),
            FX_PERSISTS             = static_cast<value_type>(1 << 12),
            GORY_VISUALS            = static_cast<value_type>(1 << 14),
            HIDE_IN_UI              = static_cast<value_type>(1 << 15),
            NO_RECAST               = static_cast<value_type>(1 << 17),
            POWER_AFFECTS_MAGNITUDE = static_cast<value_type>(1 << 21),
            POWER_AFFECTS_DURATION  = static_cast<value_type>(1 << 22),
            PAINLESS                = static_cast<value_type>(1 << 26),
            NO_HIT_EFFECT           = static_cast<value_type>(1 << 27),
            NO_DEATH_DISPEL         = static_cast<value_type>(1 << 28),
        };

    public:
        using Enum_t::Enum_t;
    };

}

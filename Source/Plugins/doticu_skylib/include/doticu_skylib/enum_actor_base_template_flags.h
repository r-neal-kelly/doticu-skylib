/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Actor_Base_Template_Flags_e : public Enum_t<u16>
    {
    public:
        enum : value_type
        {
            TRAITS              = 1lu << 0,
            STATS               = 1lu << 1,
            FACTIONS            = 1lu << 2,
            SPELLS              = 1lu << 3,
            AI_DATA             = 1lu << 4,
            AI_PACKAGES         = 1lu << 5,
            UNUSED              = 1lu << 6,
            BASE_DATA           = 1lu << 7,
            INVENTORY           = 1lu << 8,
            SCRIPT              = 1lu << 9,
            AI_DEFAULT_PACKAGES = 1lu << 10,
            ATTACK_DATA         = 1lu << 11,
            KEYWORDS            = 1lu << 12,
        };
        using Enum_t::Enum_t;
    };

}

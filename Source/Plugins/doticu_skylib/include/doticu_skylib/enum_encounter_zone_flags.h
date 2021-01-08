/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Encounter_Zone_Flags_e : public Enum_t<u8>
    {
    public:
        enum : value_type
        {
            NEVER_RESETS                    = 1 << 0,
            MATCH_PC_BELOW_MINIMUM_LEVEL    = 1 << 1,
            DISABLE_COMBAT_BOUNDARY         = 1 << 2,
        };
        using Enum_t::Enum_t;
    };

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Quest_Type_e : public Enum_t<u8>
    {
    public:
        enum : value_type
        {
            NONE                = 0,
            MAIN                = 1,
            MAGES_GUILD         = 2,
            THIEVES_GUILD       = 3,
            DARK_BROTHERHOOD    = 4,
            COMPANIONS          = 5,
            MISC                = 6,
            DAEDRIC             = 7,
            SIDE                = 8,
            CIVIL_WAR           = 9,
            DAWNGUARD           = 10,
            DRAGONBORN          = 11,
        };
        using Enum_t::Enum_t;
    };

}

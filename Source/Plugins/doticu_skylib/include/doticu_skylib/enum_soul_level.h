/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Soul_Level_e : public Enum_t<u8>
    {
    public:
        enum : value_type
        {
            NONE    = 0,
            PETTY   = 1,
            LESSER  = 2,
            COMMON  = 3,
            GREATER = 4,
            GRAND   = 5,
        };

        static constexpr const char* NONE_STRING    = "None";
        static constexpr const char* PETTY_STRING   = "Petty";
        static constexpr const char* LESSER_STRING  = "Lesser";
        static constexpr const char* COMMON_STRING  = "Common";
        static constexpr const char* GREATER_STRING = "Greater";
        static constexpr const char* GRAND_STRING   = "Grand";

    public:
        using Enum_t::Enum_t;

    public:
        static some<const char*>    To_String(Soul_Level_e soul_level_e);
        static Soul_Level_e         From_String(maybe<const char*> soul_level_cstr);
    };

}

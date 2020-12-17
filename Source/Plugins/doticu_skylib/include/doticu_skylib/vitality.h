/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Vitality_e : public Enum_t<s8>
    {
    public:
        enum : s8
        {
            NONE            = -1,
            MORTAL          = 0,
            PROTECTED       = 1,
            ESSENTIAL       = 2,
            INVULNERABLE    = 3,
        };

        static constexpr const char* NONE_STRING            = "None";
        static constexpr const char* MORTAL_STRING          = "Mortal";
        static constexpr const char* PROTECTED_STRING       = "Protected";
        static constexpr const char* ESSENTIAL_STRING       = "Essential";
        static constexpr const char* INVULNERABLE_STRING    = "Invulnerable";

    public:
        using Enum_t::Enum_t;

        static some<const char*>    To_String(Vitality_e vitality);
        static Vitality_e           From_String(some<const char*> vitality);
    };

}

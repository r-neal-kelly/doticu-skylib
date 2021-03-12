/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    using Raw_Actor_Value_Modifier_t = u32;

    class Actor_Value_Modifier_e :
        public Enum_t<Raw_Actor_Value_Modifier_t>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_      = static_cast<value_type>(-1),

            PERMANENT   = static_cast<value_type>(0x0),
            TEMPORARY   = static_cast<value_type>(0x1),
            DAMAGE      = static_cast<value_type>(0x2),

            _TOTAL_     = static_cast<value_type>(0x3),
        };

    public:
        using Enum_t::Enum_t;

    public:
        static some<const char* const*> Strings();
        static some<const char*>        To_String(Actor_Value_Modifier_e actor_value_modifier);
        static Actor_Value_Modifier_e   From_String(maybe<const char*> actor_value_modifier);
    };

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cstring.h"
#include "doticu_skylib/enum_actor_value_modifier.h"

namespace doticu_skylib {

    some<const char* const*> Actor_Value_Modifier_e::Strings()
    {
        static const char* const strings[_TOTAL_] =
        {
            SKYLIB_ENUM_TO_STRING(PERMANENT),
            SKYLIB_ENUM_TO_STRING(TEMPORARY),
            SKYLIB_ENUM_TO_STRING(DAMAGE),
        };

        return strings;
    }

    some<const char*> Actor_Value_Modifier_e::To_String(Actor_Value_Modifier_e actor_value_modifier)
    {
        if (actor_value_modifier < _TOTAL_) {
            return Strings()[actor_value_modifier];
        } else {
            return "NONE";
        }
    }

    Actor_Value_Modifier_e Actor_Value_Modifier_e::From_String(maybe<const char*> actor_value_modifier)
    {
        if (actor_value_modifier) {
            some<const char* const*> strings = Strings();
            for (size_t idx = 0, end = _TOTAL_; idx < end; idx += 1) {
                some<const char*> string = strings[idx];
                if (CString_t::Is_Same(string(), actor_value_modifier(), true)) {
                    return static_cast<Actor_Value_Modifier_e::value_type>(idx);
                }
            }
            return _NONE_;
        } else {
            return _NONE_;
        }
    }

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cstring.h"
#include "doticu_skylib/enum_vitality.h"

namespace doticu_skylib {

    Bool_t Vitality_ev::Is_Valid(value_type value)
    {
        return value > -1 && value < _TOTAL_;
    }

    some<const char* const*> Vitality_ev::Strings()
    {
        static const char* const strings[_TOTAL_] =
        {
            SKYLIB_ENUM_TO_STRING(MORTAL),
            SKYLIB_ENUM_TO_STRING(PROTECTED),
            SKYLIB_ENUM_TO_STRING(ESSENTIAL),
            SKYLIB_ENUM_TO_STRING(INVULNERABLE),
        };

        return strings;
    }

    some<const char*> Vitality_ev::To_String(value_type value)
    {
        if (Is_Valid(value)) {
            return Strings()[value];
        } else {
            return "NONE";
        }
    }

    Vitality_ev::value_type Vitality_ev::From_String(maybe<const char*> vitality)
    {
        if (vitality) {
            some<const char* const*> strings = Strings();
            for (size_t idx = 0, end = _TOTAL_; idx < end; idx += 1) {
                some<const char*> string = strings[idx];
                if (CString_t::Is_Same(string(), vitality(), true)) {
                    return static_cast<Vitality_e::value_type>(idx);
                }
            }
            return _NONE_;
        } else {
            return _NONE_;
        }
    }

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cstring.h"
#include "doticu_skylib/enum_soul_level.h"

namespace doticu_skylib {

    some<const char* const*> Soul_Level_e::Strings()
    {
        static const char* const strings[_TOTAL_] =
        {
            SKYLIB_ENUM_TO_STRING(EMPTY),
            SKYLIB_ENUM_TO_STRING(PETTY),
            SKYLIB_ENUM_TO_STRING(LESSER),
            SKYLIB_ENUM_TO_STRING(COMMON),
            SKYLIB_ENUM_TO_STRING(GREATER),
            SKYLIB_ENUM_TO_STRING(GRAND),
        };

        return strings;
    }

    some<const char*> Soul_Level_e::To_String(Soul_Level_e soul_level)
    {
        if (soul_level) {
            return Strings()[soul_level];
        } else {
            return "NONE";
        }
    }

    Soul_Level_e Soul_Level_e::From_String(maybe<const char*> soul_level)
    {
        if (soul_level) {
            some<const char* const*> strings = Strings();
            for (size_t idx = 0, end = _TOTAL_; idx < end; idx += 1) {
                some<const char*> string = strings[idx];
                if (CString_t::Is_Same(string(), soul_level(), true)) {
                    return static_cast<Soul_Level_e::value_type>(idx);
                }
            }
            return _NONE_;
        } else {
            return _NONE_;
        }
    }

    some<const char*> Soul_Level_e::As_String()
    {
        return To_String(*this);
    }

    Soul_Level_e::operator Bool_t() const
    {
        return this->value < _TOTAL_;
    }

}

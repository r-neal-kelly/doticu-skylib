/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cstring.h"
#include "doticu_skylib/enum_remove_reason.h"

namespace doticu_skylib {

    some<const char* const*> Remove_Reason_e::Strings()
    {
        static const char* const strings[_TOTAL_] =
        {
            SKYLIB_ENUM_TO_STRING(DEFAULT),
            SKYLIB_ENUM_TO_STRING(STEAL),
            SKYLIB_ENUM_TO_STRING(SELL),
            SKYLIB_ENUM_TO_STRING(DROP),
            SKYLIB_ENUM_TO_STRING(CONTAINER),
            SKYLIB_ENUM_TO_STRING(TEAMMATE),
        };

        return strings;
    }

    some<const char*> Remove_Reason_e::To_String(Remove_Reason_e remove_reason)
    {
        if (remove_reason) {
            return Strings()[remove_reason];
        } else {
            return "NONE";
        }
    }

    Remove_Reason_e Remove_Reason_e::From_String(maybe<const char*> remove_reason)
    {
        if (remove_reason) {
            some<const char* const*> strings = Strings();
            for (size_t idx = 0, end = _TOTAL_; idx < end; idx += 1) {
                some<const char*> string = strings[idx];
                if (CString_t::Is_Same(string(), remove_reason(), true)) {
                    return static_cast<Remove_Reason_e::value_type>(idx);
                }
            }
            return _NONE_;
        } else {
            return _NONE_;
        }
    }

    some<const char*> Remove_Reason_e::As_String()
    {
        return To_String(*this);
    }

    Remove_Reason_e::operator Bool_t() const
    {
        return this->value < _TOTAL_;
    }

}

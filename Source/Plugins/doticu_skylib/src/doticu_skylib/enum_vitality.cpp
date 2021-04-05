/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/enum_vitality.h"

namespace doticu_skylib {

    Bool_t Vitality_e_data::Is_Valid(value_type value)
    {
        return value > _NONE_ && value < _TOTAL_;
    }

    some<const char* const*> Vitality_e_data::Strings()
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

    some<const char*> Vitality_e_data::To_String(value_type value)
    {
        return Enum_Type_Data_t::To_String(Strings(), "NONE", &Is_Valid, value);
    }

    Vitality_e_data::value_type Vitality_e_data::From_String(maybe<const char*> string)
    {
        return Enum_Type_Data_t::From_String(Strings(), _NONE_, _TOTAL_, string);
    }

}

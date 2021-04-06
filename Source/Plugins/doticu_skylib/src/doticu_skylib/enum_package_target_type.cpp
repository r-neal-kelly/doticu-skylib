/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/enum_package_target_type.h"

namespace doticu_skylib {

    Bool_t Package_Target_Type_e_data::Is_Valid(value_type value)
    {
        return value > _NONE_ && value < _TOTAL_;
    }

    some<const char* const*> Package_Target_Type_e_data::Strings()
    {
        static const char* const strings[_TOTAL_] =
        {
            SKYLIB_ENUM_TO_STRING(SPECIFIC),
            SKYLIB_ENUM_TO_STRING(FORM_ID),
            SKYLIB_ENUM_TO_STRING(FORM_TYPE),
            SKYLIB_ENUM_TO_STRING(LINKED),
            SKYLIB_ENUM_TO_STRING(ALIAS_ID),
            SKYLIB_ENUM_TO_STRING(UNKNOWN),
            SKYLIB_ENUM_TO_STRING(SELF),
        };

        return strings;
    }

    some<const char*> Package_Target_Type_e_data::To_String(value_type value)
    {
        return Enum_Type_Data_t::To_String(Strings(), "NONE", &Is_Valid, value);
    }

    Package_Target_Type_e_data::value_type Package_Target_Type_e_data::From_String(maybe<const char*> string)
    {
        return Enum_Type_Data_t::From_String(Strings(), _NONE_, _TOTAL_, string);
    }

}

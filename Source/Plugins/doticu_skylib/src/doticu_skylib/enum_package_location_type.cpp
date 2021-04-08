/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/enum_package_location_type.h"

namespace doticu_skylib {

    Bool_t Package_Location_Type_e_data::Is_Valid(value_type value)
    {
        return value > _NONE_ && value < _TOTAL_;
    }

    some<const char* const*> Package_Location_Type_e_data::Strings()
    {
        static const char* const strings[_TOTAL_] =
        {
            SKYLIB_ENUM_TO_STRING(REFERENCE_HANDLE),
            SKYLIB_ENUM_TO_STRING(CELL),
            SKYLIB_ENUM_TO_STRING(PACKAGE_START),
            SKYLIB_ENUM_TO_STRING(EDITOR_LOCATION),
            SKYLIB_ENUM_TO_STRING(BOUND_OBJECT),
            SKYLIB_ENUM_TO_STRING(FORM_TYPE),
            SKYLIB_ENUM_TO_STRING(LINKED_REFERENCE),
            SKYLIB_ENUM_TO_STRING(PACKAGE_LOCATION),
            SKYLIB_ENUM_TO_STRING(ALIAS_REFERENCE),
            SKYLIB_ENUM_TO_STRING(ALIAS_LOCATION),
            SKYLIB_ENUM_TO_STRING(UNKNOWN_10),
            SKYLIB_ENUM_TO_STRING(UNKNOWN_11),
            SKYLIB_ENUM_TO_STRING(SELF),
        };

        return strings;
    }

    some<const char*> Package_Location_Type_e_data::To_String(value_type value)
    {
        return Enum_Type_Data_t::To_String(Strings(), "NONE", &Is_Valid, value);
    }

    Package_Location_Type_e_data::value_type Package_Location_Type_e_data::From_String(maybe<const char*> string)
    {
        return Enum_Type_Data_t::From_String(Strings(), _NONE_, _TOTAL_, string);
    }

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/enum_package_interrupt_type.h"

namespace doticu_skylib {

    Bool_t Package_Interrupt_Type_e_data::Is_Valid(value_type value)
    {
        return value > _NONE_ && value < _TOTAL_;
    }

    some<const char* const*> Package_Interrupt_Type_e_data::Strings()
    {
        static const char* const strings[_TOTAL_] =
        {
            SKYLIB_ENUM_TO_STRING(SPECTATOR),
            SKYLIB_ENUM_TO_STRING(OBSERVE_DEAD),
            SKYLIB_ENUM_TO_STRING(GUARD_WARN),
            SKYLIB_ENUM_TO_STRING(COMBAT),
        };

        return strings;
    }

    some<const char*> Package_Interrupt_Type_e_data::To_String(value_type value)
    {
        return Enum_Type_Data_t::To_String(Strings(), "NONE", &Is_Valid, value);
    }

    Package_Interrupt_Type_e_data::value_type Package_Interrupt_Type_e_data::From_String(maybe<const char*> string)
    {
        return Enum_Type_Data_t::From_String(Strings(), _NONE_, _TOTAL_, string);
    }

}

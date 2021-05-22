/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#undef FAILED

#include "doticu_skylib/enum_type.h"

namespace doticu_skylib {

    class Quest_Objective_State_e_data :
        public Enum_Type_Data_t<s8>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_                  = -1,

            DORMANT                 = 0,
            DISPLAYED               = 1,
            COMPLETED               = 2,
            COMPLETED_AND_DISPLAYED = 3,
            FAILED                  = 4,
            FAILED_AND_DISPLAYED    = 5,

            _TOTAL_,
        };

    public:
        static inline Bool_t Is_Valid(value_type value)
        {
            return value > _NONE_ && value < _TOTAL_;
        }

        static inline some<const char* const*> Strings()
        {
            static const char* const strings[_TOTAL_] =
            {
                SKYLIB_ENUM_TO_STRING(DORMANT),
                SKYLIB_ENUM_TO_STRING(DISPLAYED),
                SKYLIB_ENUM_TO_STRING(COMPLETED),
                SKYLIB_ENUM_TO_STRING(COMPLETED_AND_DISPLAYED),
                SKYLIB_ENUM_TO_STRING(FAILED),
                SKYLIB_ENUM_TO_STRING(FAILED_AND_DISPLAYED),
            };

            return strings;
        }

        static inline some<const char*> To_String(value_type value)
        {
            return Enum_Type_Data_t::To_String(Strings(), "NONE", &Is_Valid, value);
        }

        static inline value_type From_String(maybe<const char*> string)
        {
            return Enum_Type_Data_t::From_String(Strings(), _NONE_, _TOTAL_, string);
        }
    };

    class Quest_Objective_State_e :
        public Enum_Type_t<Quest_Objective_State_e_data>
    {
    public:
        using Enum_Type_t::Enum_Type_t;
    };

    template <>
    class none<Quest_Objective_State_e> :
        public none_enum<Quest_Objective_State_e>
    {
    public:
        using none_enum::none_enum;
    };

    template <>
    class maybe<Quest_Objective_State_e> :
        public maybe_enum<Quest_Objective_State_e>
    {
    public:
        using maybe_enum::maybe_enum;
    };

    template <>
    class some<Quest_Objective_State_e> :
        public some_enum<Quest_Objective_State_e>
    {
    public:
        using some_enum::some_enum;
    };

}

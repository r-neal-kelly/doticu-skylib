/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_type.h"

namespace doticu_skylib {

    class Calendar_Time_AM_PM_e_data :
        public Enum_Type_Data_t<s8>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_ = -1,

            AM,
            PM,

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
                SKYLIB_ENUM_TO_STRING(AM),
                SKYLIB_ENUM_TO_STRING(PM),
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

    class Calendar_Time_AM_PM_e :
        public Enum_Type_t<Calendar_Time_AM_PM_e_data>
    {
    public:
        using Enum_Type_t::Enum_Type_t;
    };

    template <>
    class none<Calendar_Time_AM_PM_e> :
        public none_enum<Calendar_Time_AM_PM_e>
    {
    public:
        using none_enum::none_enum;
    };

    template <>
    class maybe<Calendar_Time_AM_PM_e> :
        public maybe_enum<Calendar_Time_AM_PM_e>
    {
    public:
        using maybe_enum::maybe_enum;
    };

    template <>
    class some<Calendar_Time_AM_PM_e> :
        public some_enum<Calendar_Time_AM_PM_e>
    {
    public:
        using some_enum::some_enum;
    };

}

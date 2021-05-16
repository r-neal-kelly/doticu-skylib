/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_type.h"

namespace doticu_skylib {

    class Calendar_Date_Weekday_e_data :
        public Enum_Type_Data_t<s8>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_ = -1,
            _ANY_ = -1,

            SUNDAY,
            MONDAY,
            TUESDAY,
            WEDNESDAY,
            THURSDAY,
            FRIDAY,
            SATURDAY,
            WEEKDAYS,
            WEEKENDS,
            MONDAY_WEDNESDAY_FRIDAY,
            TUESDAY_THURSDAY,

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
                SKYLIB_ENUM_TO_STRING(SUNDAY),
                SKYLIB_ENUM_TO_STRING(MONDAY),
                SKYLIB_ENUM_TO_STRING(TUESDAY),
                SKYLIB_ENUM_TO_STRING(WEDNESDAY),
                SKYLIB_ENUM_TO_STRING(THURSDAY),
                SKYLIB_ENUM_TO_STRING(FRIDAY),
                SKYLIB_ENUM_TO_STRING(SATURDAY),
                SKYLIB_ENUM_TO_STRING(WEEKDAYS),
                SKYLIB_ENUM_TO_STRING(WEEKENDS),
                SKYLIB_ENUM_TO_STRING(MONDAY_WEDNESDAY_FRIDAY),
                SKYLIB_ENUM_TO_STRING(TUESDAY_THURSDAY),
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

    class Calendar_Date_Weekday_e :
        public Enum_Type_t<Calendar_Date_Weekday_e_data>
    {
    public:
        using Enum_Type_t::Enum_Type_t;
    };

    template <>
    class none<Calendar_Date_Weekday_e> :
        public none_enum<Calendar_Date_Weekday_e>
    {
    public:
        using none_enum::none_enum;
    };

    template <>
    class maybe<Calendar_Date_Weekday_e> :
        public maybe_enum<Calendar_Date_Weekday_e>
    {
    public:
        using maybe_enum::maybe_enum;
    };

    template <>
    class some<Calendar_Date_Weekday_e> :
        public some_enum<Calendar_Date_Weekday_e>
    {
    public:
        using some_enum::some_enum;
    };

}

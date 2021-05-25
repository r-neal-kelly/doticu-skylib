/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_type.h"

namespace doticu_skylib {

    class Calendar_Date_Month_e_data :
        public Enum_Type_Data_t<s8>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_ = -1,
            _ANY_ = -1,

            MORNING_STAR,
            SUNS_DAWN,
            FIRST_SEED,
            RAINS_HAND,
            SECOND_SEED,
            MID_YEAR,
            SUNS_HEIGHT,
            LAST_SEED,
            HEARTH_FIRE,
            FROST_FALL,
            SUNS_DUSK,
            EVENING_STAR,

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
                SKYLIB_ENUM_TO_STRING(MORNING_STAR),
                SKYLIB_ENUM_TO_STRING(SUNS_DAWN),
                SKYLIB_ENUM_TO_STRING(FIRST_SEED),
                SKYLIB_ENUM_TO_STRING(RAINS_HAND),
                SKYLIB_ENUM_TO_STRING(SECOND_SEED),
                SKYLIB_ENUM_TO_STRING(MID_YEAR),
                SKYLIB_ENUM_TO_STRING(SUNS_HEIGHT),
                SKYLIB_ENUM_TO_STRING(LAST_SEED),
                SKYLIB_ENUM_TO_STRING(HEARTH_FIRE),
                SKYLIB_ENUM_TO_STRING(FROST_FALL),
                SKYLIB_ENUM_TO_STRING(SUNS_DUSK),
                SKYLIB_ENUM_TO_STRING(EVENING_STAR),
            };

            return strings;
        }

        static inline some<const char* const*> English_Strings()
        {
            static const char* const strings[_TOTAL_] =
            {
                "Morning Star",
                "Sun's Dawn",
                "First Seed",
                "Rain's Hand",
                "Second Seed",
                "Mid Year",
                "Sun's Height",
                "Last Seed",
                "Hearth Fire",
                "Frost Fall",
                "Sun's Dusk",
                "Evening Star",
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

        static inline some<const char*> To_English_String(value_type value)
        {
            return Enum_Type_Data_t::To_String(English_Strings(), "None", &Is_Valid, value);
        }

        static inline value_type From_English_String(maybe<const char*> string)
        {
            return Enum_Type_Data_t::From_String(English_Strings(), _NONE_, _TOTAL_, string);
        }
    };

    class Calendar_Date_Month_e :
        public Enum_Type_t<Calendar_Date_Month_e_data>
    {
    public:
        using Enum_Type_t::Enum_Type_t;
    };

    template <>
    class none<Calendar_Date_Month_e> :
        public none_enum<Calendar_Date_Month_e>
    {
    public:
        using none_enum::none_enum;
    };

    template <>
    class maybe<Calendar_Date_Month_e> :
        public maybe_enum<Calendar_Date_Month_e>
    {
    public:
        using maybe_enum::maybe_enum;
    };

    template <>
    class some<Calendar_Date_Month_e> :
        public some_enum<Calendar_Date_Month_e>
    {
    public:
        using some_enum::some_enum;
    };

}

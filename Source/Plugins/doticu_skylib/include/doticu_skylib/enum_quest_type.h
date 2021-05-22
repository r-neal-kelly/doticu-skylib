/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_type.h"

namespace doticu_skylib {

    class Quest_Type_e_data :
        public Enum_Type_Data_t<s8>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_              = -1,

            OTHER               = 0,
            MAIN                = 1,
            MAGES_GUILD         = 2,
            THIEVES_GUILD       = 3,
            DARK_BROTHERHOOD    = 4,
            COMPANIONS          = 5,
            MISC                = 6,
            DAEDRIC             = 7,
            SIDE                = 8,
            CIVIL_WAR           = 9,
            DAWNGUARD           = 10,
            DRAGONBORN          = 11,

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
                SKYLIB_ENUM_TO_STRING(OTHER),
                SKYLIB_ENUM_TO_STRING(MAIN),
                SKYLIB_ENUM_TO_STRING(MAGES_GUILD),
                SKYLIB_ENUM_TO_STRING(THIEVES_GUILD),
                SKYLIB_ENUM_TO_STRING(DARK_BROTHERHOOD),
                SKYLIB_ENUM_TO_STRING(COMPANIONS),
                SKYLIB_ENUM_TO_STRING(MISC),
                SKYLIB_ENUM_TO_STRING(DAEDRIC),
                SKYLIB_ENUM_TO_STRING(SIDE),
                SKYLIB_ENUM_TO_STRING(CIVIL_WAR),
                SKYLIB_ENUM_TO_STRING(DAWNGUARD),
                SKYLIB_ENUM_TO_STRING(DRAGONBORN),
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

    class Quest_Type_e :
        public Enum_Type_t<Quest_Type_e_data>
    {
    public:
        using Enum_Type_t::Enum_Type_t;
    };

    template <>
    class none<Quest_Type_e> :
        public none_enum<Quest_Type_e>
    {
    public:
        using none_enum::none_enum;
    };

    template <>
    class maybe<Quest_Type_e> :
        public maybe_enum<Quest_Type_e>
    {
    public:
        using maybe_enum::maybe_enum;
    };

    template <>
    class some<Quest_Type_e> :
        public some_enum<Quest_Type_e>
    {
    public:
        using some_enum::some_enum;
    };

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_type.h"

namespace doticu_skylib {

    class Package_Location_Type_e_data :
        public Enum_Type_Data_t<s8>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_              = -1,

            REFERENCE_HANDLE    = 0,
            CELL                = 1,
            PACKAGE_START       = 2,
            EDITOR_LOCATION     = 3,
            OBJECT              = 4,
            FORM_TYPE           = 5,
            LINKED_FORM         = 6,
            PACKAGE_LOCATION    = 7,
            ALIAS_REFERENCE     = 8,
            ALIAS_LOCATION      = 9,
            UNKNOWN_10          = 10,
            UNKNOWN_11          = 11,
            SELF                = 12,

            _TOTAL_             = 13,
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
                SKYLIB_ENUM_TO_STRING(REFERENCE_HANDLE),
                SKYLIB_ENUM_TO_STRING(CELL),
                SKYLIB_ENUM_TO_STRING(PACKAGE_START),
                SKYLIB_ENUM_TO_STRING(EDITOR_LOCATION),
                SKYLIB_ENUM_TO_STRING(OBJECT),
                SKYLIB_ENUM_TO_STRING(FORM_TYPE),
                SKYLIB_ENUM_TO_STRING(LINKED_FORM),
                SKYLIB_ENUM_TO_STRING(PACKAGE_LOCATION),
                SKYLIB_ENUM_TO_STRING(ALIAS_REFERENCE),
                SKYLIB_ENUM_TO_STRING(ALIAS_LOCATION),
                SKYLIB_ENUM_TO_STRING(UNKNOWN_10),
                SKYLIB_ENUM_TO_STRING(UNKNOWN_11),
                SKYLIB_ENUM_TO_STRING(SELF),
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

    class Package_Location_Type_e :
        public Enum_Type_t<Package_Location_Type_e_data>
    {
    public:
        using Enum_Type_t::Enum_Type_t;
    };

    template <>
    class none<Package_Location_Type_e> :
        public none_enum<Package_Location_Type_e>
    {
    public:
        using none_enum::none_enum;
    };

    template <>
    class maybe<Package_Location_Type_e> :
        public maybe_enum<Package_Location_Type_e>
    {
    public:
        using maybe_enum::maybe_enum;
    };

    template <>
    class some<Package_Location_Type_e> :
        public some_enum<Package_Location_Type_e>
    {
    public:
        using some_enum::some_enum;
    };

}

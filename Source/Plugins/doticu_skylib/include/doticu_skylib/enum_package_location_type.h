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
            BOUND_OBJECT        = 4,
            FORM_TYPE           = 5,
            LINKED_REFERENCE    = 6,
            PACKAGE_LOCATION    = 7,
            ALIAS_REFERENCE     = 8,
            ALIAS_LOCATION      = 9,
            UNKNOWN_10          = 10,
            UNKNOWN_11          = 11,
            SELF                = 12,

            _TOTAL_             = 13,
        };

    public:
        static Bool_t                   Is_Valid(value_type value);

        static some<const char* const*> Strings();
        static some<const char*>        To_String(value_type value);
        static value_type               From_String(maybe<const char*> string);
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

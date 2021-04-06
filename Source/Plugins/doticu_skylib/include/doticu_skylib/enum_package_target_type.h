/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_type.h"

namespace doticu_skylib {

    class Package_Target_Type_e_data :
        public Enum_Type_Data_t<s8>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_      = -1,

            SPECIFIC    = 0,
            FORM_ID     = 1, // form_id. need to verify this isn't 5 instead.
            FORM_TYPE   = 2,
            LINKED      = 3,
            ALIAS_ID    = 4,
            UNKNOWN     = 5, // unknown, interrupt flag?
            SELF        = 6,

            _TOTAL_     = 7,
        };

    public:
        static Bool_t                   Is_Valid(value_type value);

        static some<const char* const*> Strings();
        static some<const char*>        To_String(value_type value);
        static value_type               From_String(maybe<const char*> string);
    };

    class Package_Target_Type_e :
        public Enum_Type_t<Package_Target_Type_e_data>
    {
    public:
        using Enum_Type_t::Enum_Type_t;
    };

    template <>
    class none<Package_Target_Type_e> :
        public none_enum<Package_Target_Type_e>
    {
    public:
        using none_enum::none_enum;
    };

    template <>
    class maybe<Package_Target_Type_e> :
        public maybe_enum<Package_Target_Type_e>
    {
    public:
        using maybe_enum::maybe_enum;
    };

    template <>
    class some<Package_Target_Type_e> :
        public some_enum<Package_Target_Type_e>
    {
    public:
        using some_enum::some_enum;
    };

}

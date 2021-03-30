/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_type.h"

namespace doticu_skylib {

    class Vitality_e_data :
        public Enum_Type_Data_t<s8>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_          = -1,

            MORTAL          = 0,
            PROTECTED       = 1,
            ESSENTIAL       = 2,
            INVULNERABLE    = 3,

            _TOTAL_,
        };

    public:
        static Bool_t                   Is_Valid(value_type value);

        static some<const char* const*> Strings();
        static some<const char*>        To_String(value_type value);
        static value_type               From_String(maybe<const char*> string);
    };

    class Vitality_e :
        public Enum_Type_t<Vitality_e_data>
    {
    public:
        using Enum_Type_t::Enum_Type_t;
    };

    template <>
    class none<Vitality_e> :
        public none_enum<Vitality_e>
    {
    public:
        using none_enum::none_enum;
    };

    template <>
    class maybe<Vitality_e> :
        public maybe_enum<Vitality_e>
    {
    public:
        using maybe_enum::maybe_enum;
    };

    template <>
    class some<Vitality_e> :
        public some_enum<Vitality_e>
    {
    public:
        using some_enum::some_enum;
    };

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_type.h"

namespace doticu_skylib {

    class Package_Interrupt_Type_e_data :
        public Enum_Type_Data_t<s8>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_          = -1,

            SPECTATOR       = 0,
            OBSERVE_DEAD    = 1,
            GUARD_WARN      = 2,
            COMBAT          = 3,

            _TOTAL_,
        };

    public:
        static Bool_t                   Is_Valid(value_type value);

        static some<const char* const*> Strings();
        static some<const char*>        To_String(value_type value);
        static value_type               From_String(maybe<const char*> string);
    };

    class Package_Interrupt_Type_e :
        public Enum_Type_t<Package_Interrupt_Type_e_data>
    {
    public:
        using Enum_Type_t::Enum_Type_t;
    };

    template <>
    class none<Package_Interrupt_Type_e> :
        public none_enum<Package_Interrupt_Type_e>
    {
    public:
        using none_enum::none_enum;
    };

    template <>
    class maybe<Package_Interrupt_Type_e> :
        public maybe_enum<Package_Interrupt_Type_e>
    {
    public:
        using maybe_enum::maybe_enum;
    };

    template <>
    class some<Package_Interrupt_Type_e> :
        public some_enum<Package_Interrupt_Type_e>
    {
    public:
        using some_enum::some_enum;
    };

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_type.h"

namespace doticu_skylib {

    class Preferred_Speed_e_data :
        public Enum_Type_Data_t<s8>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_      = -1,

            WALK        = 0,
            JOG         = 1,
            RUN         = 2,
            FAST_WALK   = 3,

            _TOTAL_,
        };

    public:
        static Bool_t                   Is_Valid(value_type value);

        static some<const char* const*> Strings();
        static some<const char*>        To_String(value_type value);
        static value_type               From_String(maybe<const char*> string);
    };

    class Preferred_Speed_e :
        public Enum_Type_t<Preferred_Speed_e_data>
    {
    public:
        using Enum_Type_t::Enum_Type_t;
    };

    template <>
    class none<Preferred_Speed_e> :
        public none_enum<Preferred_Speed_e>
    {
    public:
        using none_enum::none_enum;
    };

    template <>
    class maybe<Preferred_Speed_e> :
        public maybe_enum<Preferred_Speed_e>
    {
    public:
        using maybe_enum::maybe_enum;
    };

    template <>
    class some<Preferred_Speed_e> :
        public some_enum<Preferred_Speed_e>
    {
    public:
        using some_enum::some_enum;
    };

}

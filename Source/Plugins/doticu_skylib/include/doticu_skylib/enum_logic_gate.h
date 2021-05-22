/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_type.h"

namespace doticu_skylib {

    class Logic_Gate_e_data :
        public Enum_Type_Data_t<s8>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_ = -1,

            NOT,
            OR,
            AND,
            XOR,
            NOR,
            NAND,
            XNOR,

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
                SKYLIB_ENUM_TO_STRING(NOT),
                SKYLIB_ENUM_TO_STRING(OR),
                SKYLIB_ENUM_TO_STRING(AND),
                SKYLIB_ENUM_TO_STRING(XOR),
                SKYLIB_ENUM_TO_STRING(NOR),
                SKYLIB_ENUM_TO_STRING(NAND),
                SKYLIB_ENUM_TO_STRING(XNOR),
            };

            return strings;
        }

        static inline some<const char* const*> Symbols()
        {
            static const char* const symbols[_TOTAL_] =
            {
                "!",
                "|",
                "&",
                "^",
                "!|",
                "!&",
                "!^",
            };

            return symbols;
        }

        static inline some<const char*> To_String(value_type value)
        {
            return Enum_Type_Data_t::To_String(Strings(), "NONE", &Is_Valid, value);
        }

        static inline value_type From_String(maybe<const char*> string)
        {
            return Enum_Type_Data_t::From_String(Strings(), _NONE_, _TOTAL_, string);
        }

        static inline some<const char*> To_Symbol(value_type value)
        {
            return Enum_Type_Data_t::To_String(Symbols(), "NONE", &Is_Valid, value);
        }

        static inline value_type From_Symbol(maybe<const char*> string, Bool_t do_trim)
        {
            return Enum_Type_Data_t::From_String(Symbols(), _NONE_, _TOTAL_, string, do_trim);
        }
    };

    class Logic_Gate_e :
        public Enum_Type_t<Logic_Gate_e_data>
    {
    public:
        using Enum_Type_t::Enum_Type_t;
    };

    template <>
    class none<Logic_Gate_e> :
        public none_enum<Logic_Gate_e>
    {
    public:
        using none_enum::none_enum;
    };

    template <>
    class maybe<Logic_Gate_e> :
        public maybe_enum<Logic_Gate_e>
    {
    public:
        using maybe_enum::maybe_enum;
    };

    template <>
    class some<Logic_Gate_e> :
        public some_enum<Logic_Gate_e>
    {
    public:
        using some_enum::some_enum;
    };

}

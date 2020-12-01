/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    template <typename Type>
    class Enum_t
    {
    public:
        Type value;

        Enum_t() :
            value(0)
        {
        }

        Enum_t(Type value) :
            value(value)
        {
        }

        operator Type()
        {
            return static_cast<Type>(value);
        }

        operator const Type() const
        {
            return static_cast<const Type>(value);
        }
    };

    class Binary_e : public Enum_t<s64>
    {
    public:
        enum : s64
        {
            ALL = -1,
            BOTH = -1,
            EITHER = -1,
            NONE = 0,
            NEITHER = 0,
            A = 1,
            B = 2,
        };
        using Enum_t::Enum_t;
    };

    class Ternary_e : public Enum_t<s64>
    {
    public:
        enum : s64
        {
            ALL = -1,
            ANY = -1,
            NONE = 0,
            A = 1,
            B = 2,
            C = 3,
        };
        using Enum_t::Enum_t;
    };

    class Quaternary_e : public Enum_t<s64>
    {
    public:
        enum : s64
        {
            ALL = -1,
            ANY = -1,
            NONE = 0,
            A = 1,
            B = 2,
            C = 3,
            D = 4,
        };
        using Enum_t::Enum_t;
    };

    class Iterator_e : public Binary_e
    {
    public:
        enum : s8
        {
            CONTINUE    = Binary_e::A,
            BREAK       = Binary_e::B,
        };
        using Binary_e::Binary_e;
    };

    class Comparator_e : public Enum_t<Word_t>
    {
    public:
        enum
        {
            IS_ORDERED      = -1,
            IS_UNORDERED    = 1,
            IS_EQUAL        = 0,
        };
        using Enum_t::Enum_t;
    };

}

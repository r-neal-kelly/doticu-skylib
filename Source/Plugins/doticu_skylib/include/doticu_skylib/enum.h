/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/atomic_number.h"
#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    template <typename T>
    using enable_if_enumable_t = std::enable_if_t<
        std::is_integral<T>::value &&
        !std::is_pointer<T>::value,
        Bool_t
    >;

    template <typename T, enable_if_enumable_t<T> = true>
    class Enum_Base_t
    {
    public:
    };

    template <typename T, enable_if_enumable_t<T> = true>
    class Enum_t
    {
    public:
        using value_type = T;

    protected:
        T value;

    public:
        Enum_t() :
            value(0)
        {
        }

        Enum_t(T value) :
            value(value)
        {
        }

        Enum_t(const Enum_t& other) :
            value(other.value)
        {
        }

        Enum_t(Enum_t&& other) :
            value(std::exchange(other.value, 0))
        {
        }

        Enum_t& operator = (const Enum_t& other)
        {
            if (std::addressof(other) != this) {
                this->value = other.value;
            }
            return *this;
        }

        Enum_t& operator = (Enum_t&& other)
        {
            if (std::addressof(other) != this) {
                this->value = std::exchange(other.value, 0);
            }
            return *this;
        }

    public:
        operator T() const
        {
            return this->value;
        }

        T operator () () const
        {
            return this->value;
        }

        Enum_t operator ~() const
        {
            return ~this->value;
        }

        Enum_t& operator |=(const T other)
        {
            this->value |= other;
            return *this;
        }

        Enum_t& operator &=(const T other)
        {
            this->value &= other;
            return *this;
        }

        Enum_t& operator ^=(const T other)
        {
            this->value ^= other;
            return *this;
        }
    };

    template <typename T>
    using Atomic_Enum_t = Atomic_Number_t<typename T::value_type>;

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

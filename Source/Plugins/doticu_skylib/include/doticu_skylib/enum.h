/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#undef TRUE
#undef FALSE

#include "doticu_skylib/atomic_number.inl" // should be .h
#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    template <typename T>
    using enable_if_enumable_t = std::enable_if_t<
        std::is_integral<T>::value &&
        !std::is_same<T, Bool_t>::value,
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
        Atomic_Number_t<T> value;

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
            value(std::move(other.value))
        {
        }

        Enum_t& operator =(const Enum_t& other)
        {
            if (std::addressof(other) != this) {
                this->value = other.value;
            }
            return *this;
        }

        Enum_t& operator =(Enum_t&& other)
        {
            if (std::addressof(other) != this) {
                this->value = std::move(other.value);
            }
            return *this;
        }

        ~Enum_t()
        {
            this->value = 0;
        }

    public:
        operator T() const
        {
            return this->value;
        }

        T operator ()() const
        {
            return this->value;
        }

    public:
        Bool_t Is_Flagged(T flag)
        {
            return (this->value & flag) != 0;
        }

        const char* Is_Flagged_String(T flag)
        {
            return Is_Flagged(flag) ? "true" : "false";
        }

        void Flag(T flag)
        {
            this->value |= flag;
        }

        void Unflag(T flag)
        {
            this->value &= ~flag;
        }
    };

    class Binary_e :
        public Enum_t<s64>
    {
    public:
        enum : value_type
        {
            ALL     = -1,
            BOTH    = -1,
            EITHER  = -1,

            NONE    = 0,
            NEITHER = 0,

            A       = 1,
            B       = 2,
        };
        using Enum_t::Enum_t;
    };

    class Ternary_e :
        public Enum_t<s64>
    {
    public:
        enum : value_type
        {
            ALL     = -1,
            ANY     = -1,

            NONE    = 0,

            A       = 1,
            B       = 2,
            C       = 3,
        };
        using Enum_t::Enum_t;
    };

    class Quaternary_e :
        public Enum_t<s64>
    {
    public:
        enum : value_type
        {
            ALL     = -1,
            ANY     = -1,

            NONE    = 0,

            A       = 1,
            B       = 2,
            C       = 3,
            D       = 4,
        };
        using Enum_t::Enum_t;
    };

    class Iterator_e :
        public Binary_e
    {
    public:
        enum : s8
        {
            CONTINUE    = Binary_e::A,
            BREAK       = Binary_e::B,
        };
        using Binary_e::Binary_e;
    };

    class Boolean_e
    {
    public:
        using value_type = s64;

    public:
        enum enum_type : value_type
        {
            NEITHER = static_cast<value_type>(-1),
            FALSE   = static_cast<value_type>(0),
            TRUE    = static_cast<value_type>(1),
        };

    protected:
        enum_type value;

    public:
        Boolean_e()                             : value(NEITHER) {}
        Boolean_e(Bool_t value)                 : value(value ? TRUE : FALSE) {}
        Boolean_e(enum_type value)              : value(value == 0 ? FALSE : value > 0 ? TRUE : NEITHER) {}
        Boolean_e(value_type value)             : value(Boolean_e(static_cast<enum_type>(value)).value) {}
        Boolean_e(const Boolean_e& other)       : value(other.value) {}
        Boolean_e(Boolean_e&& other) noexcept   : value(std::exchange(other.value, NEITHER)) {}

        Boolean_e& operator = (const Boolean_e& other)
        {
            if (std::addressof(other) != this) {
                this->value = other.value;
            }
            return *this;
        }

        Boolean_e& operator = (Boolean_e&& other) noexcept
        {
            if (std::addressof(other) != this) {
                this->value = std::exchange(other.value, NEITHER);
            }
            return *this;
        }

    public:
        Bool_t operator == (enum_type other) const          { return this->value == other; }
        Bool_t operator == (const Boolean_e& other) const   { return operator ==(other.value); }
        Bool_t operator == (Boolean_e&& other) const        { return operator ==(other.value); }

        Bool_t operator != (enum_type other) const          { return this->value != other; }
        Bool_t operator != (const Boolean_e& other) const   { return operator !=(other.value); }
        Bool_t operator != (Boolean_e&& other) const        { return operator !=(other.value); }

        Bool_t operator () () const                         { return this->value == TRUE ? true : false; }
    };
    STATIC_ASSERT(sizeof(Boolean_e) == 0x8);

    class Comparator_e :
        public Enum_t<Word_t>
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

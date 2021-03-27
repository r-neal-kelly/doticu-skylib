/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe_enum.h"

namespace doticu_skylib {

    template <typename T, enable_if_enumable_t<T> = true>
    class Enum_Values_t
    {
    public:
        using value_type = T;
    };

    template <typename Enum_Values>
    class Enum_Type_t : // as opposed to Enum_Flags_t
        public Enum_Values
    {
    public:
        using enum_type = typename Enum_Values::enum_type;
        using value_type = typename Enum_Values::value_type;

    public:
        static some<const char*> To_String(maybe<Enum_Type_t> value)
        {
            return Enum_Values::To_String(value());
        }

        static maybe<Enum_Type_t> From_String(maybe<const char*> string)
        {
            return Enum_Values::From_String(string);
        }

    protected:
        Atomic_Number_t<value_type> value;

    public:
        Enum_Type_t() :
            value(_NONE_)
        {
        }

        Enum_Type_t(value_type value) :
            value(Is_Valid(value) ? value : _NONE_)
        {
        }

        Enum_Type_t(const Enum_Type_t& other) :
            value(other.value)
        {
        }

        Enum_Type_t(Enum_Type_t&& other) noexcept :
            value(std::move(other.value))
        {
        }

        Enum_Type_t& operator =(const Enum_Type_t& other)
        {
            if (this != std::addressof(other)) {
                this->value = other.value;
            }
            return *this;
        }

        Enum_Type_t& operator =(Enum_Type_t&& other) noexcept
        {
            if (this != std::addressof(other)) {
                this->value = std::move(other.value);
            }
            return *this;
        }

        ~Enum_Type_t()
        {
            this->value = _NONE_;
        }

    public:
        some<const char*> As_String() const
        {
            return To_String(*this);
        }

    public:
        explicit operator Bool_t() const
        {
            return Is_Valid(this->value);
        }

        operator value_type() const
        {
            return static_cast<Bool_t>(*this) ? this->value : _NONE_;
        }

    public:
        Bool_t operator !() const
        {
            return !static_cast<Bool_t>(*this);
        }

        value_type operator ()() const
        {
            return static_cast<value_type>(*this);
        }
    };

    template <typename T>
    class none<Enum_Type_t<T>> :
        public none_enum<Enum_Type_t<T>>
    {
    public:
        using none_enum::none_enum;
    };

    template <typename T>
    class maybe<Enum_Type_t<T>> :
        public maybe_enum<Enum_Type_t<T>>
    {
    public:
        using maybe_enum::maybe_enum;
    };

    template <typename T>
    class some<Enum_Type_t<T>> :
        public some_enum<Enum_Type_t<T>>
    {
    public:
        using some_enum::some_enum;
    };

}

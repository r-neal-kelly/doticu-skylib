/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    template <typename Numeric_t>
    class none_numeric;
    template <typename Numeric_t>
    class maybe_numeric;
    template <typename Numeric_t>
    class some_numeric;

    template <typename Numeric_t>
    class none_numeric
    {
    public:
        using value_type = Numeric_t;

    public:
        friend maybe_numeric<Numeric_t>;
        friend some_numeric<Numeric_t>;

    protected:
        const Numeric_t value;

    public:
        none_numeric(const Numeric_t value) : value(value) {}

        Numeric_t operator()()          { return const_cast<Numeric_t>(value); }
        Numeric_t operator()() const    { return const_cast<Numeric_t>(value); }

        friend Bool_t operator==(const none<Numeric_t>& a, const Numeric_t b)   { return Is_Equal(a, b); }
        friend Bool_t operator==(const none<Numeric_t>&& a, const Numeric_t b)  { return Is_Equal(a, b); }
        friend Bool_t operator==(const Numeric_t a, const none<Numeric_t>& b)   { return Is_Equal(b, a); }
        friend Bool_t operator==(const Numeric_t a, const none<Numeric_t>&& b)  { return Is_Equal(b, a); }
        friend Bool_t operator!=(const none<Numeric_t>& a, const Numeric_t b)   { return !Is_Equal(a, b); }
        friend Bool_t operator!=(const none<Numeric_t>&& a, const Numeric_t b)  { return !Is_Equal(a, b); }
        friend Bool_t operator!=(const Numeric_t a, const none<Numeric_t>& b)   { return !Is_Equal(b, a); }
        friend Bool_t operator!=(const Numeric_t a, const none<Numeric_t>&& b)  { return !Is_Equal(b, a); }
    };

    template <typename Numeric_t>
    class maybe_numeric
    {
    public:
        using value_type = Numeric_t;

    protected:
        Numeric_t value;

    public:
        maybe_numeric() : value(none<Numeric_t>().value) {}
        maybe_numeric(const Numeric_t value) : value(value) {}
        maybe_numeric(const none<Numeric_t> none) : value(none.value) {}
        maybe_numeric(const maybe_numeric& other) : value(other.value) {}
        maybe_numeric(maybe_numeric&& other) noexcept : value(std::exchange(other.value, none<Numeric_t>().value)) {}

        maybe_numeric& operator=(const maybe_numeric& other)
        {
            if (this != std::addressof(other)) {
                value = other.value;
            }
            return *this;
        }
        maybe_numeric& operator=(maybe_numeric&& other)
        {
            if (this != std::addressof(other)) {
                value = std::exchange(other.value, none<Numeric_t>().value);
            }
            return *this;
        }

        Numeric_t operator()()          { return value; }
        Numeric_t operator()() const    { return value; }

        Bool_t operator==(const maybe_numeric& other)       { return value == other(); }
        Bool_t operator==(const maybe_numeric& other) const { return value == other(); }
        Bool_t operator!=(const maybe_numeric& other)       { return !operator==(other); }
        Bool_t operator!=(const maybe_numeric& other) const { return !operator==(other); }

        explicit operator Bool_t()          { return value != none<Numeric_t>(); }
        explicit operator Bool_t() const    { return value != none<Numeric_t>(); }

        template <typename TT>
        operator maybe<TT>() const
        {
            if (operator Bool_t()) {
                return static_cast<TT>(value);
            } else {
                return none<TT>();
            }
        }
    };

    template <typename Numeric_t>
    class some_numeric
    {
    public:
        using value_type = Numeric_t;

    protected:
        Numeric_t value;

    public:
        some_numeric() = delete;
        some_numeric(Numeric_t value) : value(value) {}
        some_numeric(const none<Numeric_t> none) : value(none.value) {}
        some_numeric(const some_numeric& other) : value(other.value) {}
        some_numeric(some_numeric&& other) noexcept : value(std::exchange(other.value, none<Numeric_t>().value)) {}

        some_numeric& operator=(const some_numeric& other)
        {
            if (this != std::addressof(other)) {
                value = other.value;
            }
            return *this;
        }
        some_numeric& operator=(some_numeric&& other) noexcept
        {
            if (this != std::addressof(other)) {
                value = std::exchange(other.value, none<Numeric_t>().value);
            }
            return *this;
        }

        Numeric_t operator()()          { return value; }
        Numeric_t operator()() const    { return value; }

        Bool_t operator==(const some_numeric& other)        { return value == other(); }
        Bool_t operator==(const some_numeric& other) const  { return value == other(); }
        Bool_t operator!=(const some_numeric& other)        { return !operator==(other); }
        Bool_t operator!=(const some_numeric& other) const  { return !operator==(other); }

        explicit operator Bool_t()          { return value != none<Numeric_t>(); }
        explicit operator Bool_t() const    { return value != none<Numeric_t>(); }

        template <typename TT>
        operator some<TT>() const
        {
            if (operator Bool_t()) {
                return static_cast<TT>(value);
            } else {
                return none<TT>();
            }
        }
    };

}

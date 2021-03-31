/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    template <typename T>
    class none_numeric;
    template <typename T>
    class maybe_numeric;
    template <typename T>
    class some_numeric;

    template <typename T>
    class none_numeric
    {
    public:
        using value_type = T;

    protected:
        const value_type value;

    public:
        none_numeric() :
            value(value_type::_NONE_)
        {
        }

        none_numeric(const none_numeric& other) :
            value(value_type::_NONE_)
        {
        }

        none_numeric(none_numeric&& other) noexcept :
            value(value_type::_NONE_)
        {
        }

        none_numeric& operator =(const none_numeric& other)
        {
            return *this;
        }

        none_numeric& operator =(none_numeric&& other) noexcept
        {
            return *this;
        }

        ~none_numeric()
        {
        }

    public:
        explicit operator Bool_t() const
        {
            return false;
        }

    public:
        Bool_t operator !() const
        {
            return true;
        }

        value_type operator ()() const
        {
            return value_type::_NONE_;
        }
    };

    template <typename T>
    class maybe_numeric
    {
    public:
        using value_type = T;

    protected:
        value_type value;

    public:
        maybe_numeric() :
            value(value_type::_NONE_)
        {
        }

        maybe_numeric(typename value_type::value_type value) :
            value(value)
        {
        }

        maybe_numeric(const value_type& value) :
            value(value)
        {
        }

        maybe_numeric(value_type&& value) noexcept :
            value(std::exchange(value, value_type::_NONE_))
        {
        }

        maybe_numeric(const none_numeric<value_type>& other) :
            value(value_type::_NONE_)
        {
        }

        maybe_numeric(none_numeric<value_type>&& other) noexcept :
            value(value_type::_NONE_)
        {
        }

        maybe_numeric(const maybe_numeric& other) :
            value(other.value)
        {
        }

        maybe_numeric(maybe_numeric&& other) noexcept :
            value(std::exchange(other.value, value_type::_NONE_))
        {
        }

        maybe_numeric(const some_numeric<value_type>& other) :
            value(other.value)
        {
        }

        maybe_numeric(some_numeric<value_type>&& other) noexcept :
            value(std::exchange(other.value, value_type::_NONE_))
        {
        }

        maybe_numeric& operator =(const maybe_numeric& other)
        {
            if (this != std::addressof(other)) {
                this->value = other.value;
            }
            return *this;
        }

        maybe_numeric& operator =(maybe_numeric&& other) noexcept
        {
            if (this != std::addressof(other)) {
                this->value = std::exchange(other.value, value_type::_NONE_);
            }
            return *this;
        }

        ~maybe_numeric()
        {
            this->value = value_type::_NONE_;
        }

    public:
        explicit operator Bool_t() const
        {
            return static_cast<Bool_t>(this->value);
        }

        template <typename TT>
        operator maybe<TT>()
        {
            return maybe<TT>(static_cast<TT&>(this->value));
        }

    public:
        Bool_t operator !() const
        {
            return !static_cast<Bool_t>(*this);
        }

        value_type operator ()() const
        {
            return this->value;
        }
    };

    template <typename T>
    class some_numeric
    {
    public:
        friend class maybe_numeric<T>;

    public:
        using value_type = T;

    protected:
        value_type value;

    public:
        some_numeric() = delete;

        some_numeric(typename value_type::value_type value) :
            value(value)
        {
        }

        some_numeric(const value_type& value) :
            value(value)
        {
        }

        some_numeric(value_type&& value) noexcept :
            value(std::exchange(value, value_type::_NONE_))
        {
        }

        some_numeric(const some_numeric& other) :
            value(other.value)
        {
        }

        some_numeric(some_numeric&& other) noexcept :
            value(std::exchange(other.value, value_type::_NONE_))
        {
        }

        some_numeric& operator =(const some_numeric& other)
        {
            if (this != std::addressof(other)) {
                this->value = other.value;
            }
            return *this;
        }

        some_numeric& operator =(some_numeric&& other) noexcept
        {
            if (this != std::addressof(other)) {
                this->value = std::exchange(other.value, value_type::_NONE_);
            }
            return *this;
        }

        ~some_numeric()
        {
            this->value = value_type::_NONE_;
        }

    public:
        explicit operator Bool_t() const
        {
            return static_cast<Bool_t>(this->value);
        }

        template <typename TT>
        operator some<TT>()
        {
            return some<TT>(static_cast<TT&>(this->value));
        }

    public:
        Bool_t operator !() const
        {
            return !static_cast<Bool_t>(*this);
        }

        value_type operator ()() const
        {
            return this->value;
        }
    };

}

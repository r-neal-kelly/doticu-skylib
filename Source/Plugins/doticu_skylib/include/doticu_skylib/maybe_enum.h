/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    template <typename T>
    class none_enum;
    template <typename T>
    class maybe_enum;
    template <typename T>
    class some_enum;

    template <typename T>
    class none_enum
    {
    public:
        using value_type = T;

    public:
        value_type value;

    public:
        none_enum() :
            value()
        {
        }

        none_enum(const none_enum& other) = delete;

        none_enum(none_enum&& other) = delete;

        none_enum& operator =(const none_enum& other) = delete;

        none_enum& operator =(none_enum&& other) noexcept = delete;

        ~none_enum()
        {
        }

    public:
        explicit operator Bool_t() const
        {
            return false;
        }

        template <typename TT>
        operator none<TT>() const
        {
            return none<TT>(static_cast<TT>(this->value));
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
    class maybe_enum
    {
    public:
        using value_type = T;

    public:
        value_type value;

    public:
        maybe_enum() :
            value()
        {
        }

        maybe_enum(typename value_type::value_type value) :
            value(value)
        {
        }

        maybe_enum(const value_type& value) :
            value(value)
        {
        }

        maybe_enum(value_type&& value) noexcept :
            value(std::move(value))
        {
        }

        maybe_enum(none<value_type> value) :
            value()
        {
        }

        maybe_enum(some<value_type> value) :
            value(value())
        {
        }

        maybe_enum(const maybe_enum& other) :
            value(other.value)
        {
        }

        maybe_enum(maybe_enum&& other) noexcept :
            value(std::move(other.value))
        {
        }

        maybe_enum& operator =(const maybe_enum& other)
        {
            if (this != std::addressof(other)) {
                this->value = other.value;
            }
            return *this;
        }

        maybe_enum& operator =(maybe_enum&& other) noexcept
        {
            if (this != std::addressof(other)) {
                this->value = std::move(other.value);
            }
            return *this;
        }

        ~maybe_enum()
        {
        }

    public:
        explicit operator Bool_t() const
        {
            return static_cast<Bool_t>(this->value);
        }

        template <typename TT>
        operator maybe<TT>() const
        {
            return maybe<TT>(static_cast<TT>(this->value));
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
    class some_enum
    {
    public:
        using value_type = T;

    public:
        value_type value;

    public:
        some_enum(typename value_type::value_type value) :
            value(value)
        {
        }

        some_enum(const value_type& value) :
            value(value)
        {
        }

        some_enum(value_type&& value) noexcept :
            value(std::move(value))
        {
        }

        some_enum(const some_enum& other) :
            value(other.value)
        {
        }

        some_enum(some_enum&& other) noexcept :
            value(std::move(other.value))
        {
        }

        some_enum& operator =(const some_enum& other)
        {
            if (this != std::addressof(other)) {
                this->value = other.value;
            }
            return *this;
        }

        some_enum& operator =(some_enum&& other) noexcept
        {
            if (this != std::addressof(other)) {
                this->value = std::move(other.value);
            }
            return *this;
        }

        ~some_enum()
        {
        }

    public:
        explicit operator Bool_t() const
        {
            return static_cast<Bool_t>(this->value);
        }

        template <typename TT>
        operator some<TT>() const
        {
            return some<TT>(static_cast<TT>(this->value));
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

    template <typename T, template <typename> typename TT,
        std::enable_if_t<is_none_maybe_some<T, TT>::value, Bool_t> = true
    > inline Bool_t operator ==(const TT<T>& a, const typename T::value_type b)
    {
        return a() == b;
    }

    template <typename T, template <typename> typename TT,
        std::enable_if_t<is_none_maybe_some<T, TT>::value, Bool_t> = true
    > inline Bool_t operator ==(const typename T::value_type a, const TT<T>& b)
    {
        return a == b();
    }

    template <typename T, template <typename> typename TT,
        std::enable_if_t<is_none_maybe_some<T, TT>::value, Bool_t> = true
    > inline Bool_t operator !=(const TT<T>& a, const typename T::value_type b)
    {
        return !(operator ==(a, b));
    }

    template <typename T, template <typename> typename TT,
        std::enable_if_t<is_none_maybe_some<T, TT>::value, Bool_t> = true
    > inline Bool_t operator !=(const typename T::value_type a, const TT<T>& b)
    {
        return !(operator ==(a, b));
    }

}

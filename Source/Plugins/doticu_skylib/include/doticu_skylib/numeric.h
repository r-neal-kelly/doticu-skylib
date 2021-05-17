/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/traits.h"

namespace doticu_skylib {

    template <typename T, enable_if_arithmetic_t<T> = true>
    class Numeric_Data_t
    {
    public:
        using value_type = T;
    };

    template <typename T>
    using enable_if_numeric_data_t = std::enable_if_t<
        std::is_convertible<T, Numeric_Data_t<typename T::value_type>>::value,
        Bool_t
    >;
    template <typename T, typename _ = void>
    struct is_numeric_data :
        public std::false_type
    {
    };
    template <typename T>
    struct is_numeric_data<T, std::conditional_t<false, enable_if_numeric_data_t<T>, void>> :
        public std::true_type
    {
    };

    template <typename Data_t, enable_if_numeric_data_t<Data_t> = true>
    class Numeric_t :
        public Data_t
    {
    public:
        using data_type = typename Data_t;
        using value_type = typename Data_t::value_type;

    protected:
        value_type value;

    public:
        Numeric_t() :
            value(Data_t::_NONE_)
        {
        }

        Numeric_t(value_type value) :
            value(Data_t::Is_Valid(value) ? value : Data_t::_NONE_)
        {
        }

        Numeric_t(const Numeric_t& other) :
            value(other.value)
        {
        }

        Numeric_t(Numeric_t&& other) noexcept :
            value(std::exchange(other.value, Data_t::_NONE_))
        {
        }

        Numeric_t& operator =(const Numeric_t& other)
        {
            if (this != std::addressof(other)) {
                this->value = other.value;
            }
            return *this;
        }

        Numeric_t& operator =(Numeric_t&& other) noexcept
        {
            if (this != std::addressof(other)) {
                this->value = std::exchange(other.value, Data_t::_NONE_);
            }
            return *this;
        }

        ~Numeric_t()
        {
            this->value = Data_t::_NONE_;
        }

    public:
        explicit operator Bool_t() const
        {
            return Data_t::Is_Valid(this->value);
        }

        operator value_type() const
        {
            return static_cast<Bool_t>(*this) ? this->value : Data_t::_NONE_;
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
    using enable_if_numeric_t = std::enable_if_t<
        std::is_convertible<T, Numeric_t<typename T::data_type>>::value,
        Bool_t
    >;
    template <typename T, typename _ = void>
    struct is_numeric :
        public std::false_type
    {
    };
    template <typename T>
    struct is_numeric<T, std::conditional_t<false, enable_if_numeric_t<T>, void>> :
        public std::true_type
    {
    };

    template <typename T, enable_if_numeric_t<T> = true>
    class none_numeric;
    template <typename T, enable_if_numeric_t<T> = true>
    class maybe_numeric;
    template <typename T, enable_if_numeric_t<T> = true>
    class some_numeric;

    template <typename T, enable_if_numeric_t<T>>
    class none_numeric
    {
    public:
        using value_type = T;

    protected:
        const value_type value;

    public:
        none_numeric() :
            value()
        {
        }

        none_numeric(const none_numeric& other) :
            value()
        {
        }

        none_numeric(none_numeric&& other) noexcept :
            value()
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

        operator value_type() const
        {
            return this->value;
        }

    public:
        Bool_t operator !() const
        {
            return true;
        }

        const value_type operator ()() const
        {
            return this->value;
        }
    };

    template <typename T, enable_if_numeric_t<T>>
    class maybe_numeric :
        public T
    {
    public:
        using T::T;

    public:
        maybe_numeric() :
            T()
        {
        }

        maybe_numeric(const T& other) :
            T(other)
        {
        }

        maybe_numeric(T&& other) noexcept :
            T(std::move(other))
        {
        }

        maybe_numeric(const none_numeric<T>& other) :
            T()
        {
        }

        maybe_numeric(none_numeric<T>&& other) noexcept :
            T()
        {
        }

        maybe_numeric(const maybe_numeric<T>& other) :
            T(other)
        {
        }

        maybe_numeric(maybe_numeric<T>&& other) noexcept :
            T(std::move(other))
        {
        }

        maybe_numeric(const some_numeric<T>& other) :
            T(other)
        {
        }

        maybe_numeric(some_numeric<T>&& other) noexcept :
            T(std::move(other))
        {
        }

        maybe_numeric& operator =(const maybe_numeric& other)
        {
            T::operator =(other);
            return *this;
        }

        maybe_numeric& operator =(maybe_numeric&& other) noexcept
        {
            T::operator =(std::move(other));
            return *this;
        }

        ~maybe_numeric()
        {
        }

    public:
        some_numeric<T> some()
        {
            return some_numeric<T>(static_cast<T&>(*this));
        }

    public:
        operator typename T::value_type() const = delete;
    };

    template <typename T, enable_if_numeric_t<T>>
    class some_numeric :
        public T
    {
    public:
        using T::T;

    public:
        some_numeric() = delete;

        some_numeric(const T& other) :
            T(other)
        {
        }

        some_numeric(T&& other) noexcept :
            T(std::move(other))
        {
        }

        some_numeric(const none_numeric<T>& other) = delete;
        some_numeric(none_numeric<T>&& other) noexcept = delete;

        some_numeric(const maybe_numeric<T>& other) = delete;
        some_numeric(maybe_numeric<T>&& other) noexcept = delete;

        some_numeric(const some_numeric<T>& other) :
            T(other)
        {
        }

        some_numeric(some_numeric<T>&& other) noexcept :
            T(std::move(other))
        {
        }

        some_numeric& operator =(const some_numeric& other)
        {
            T::operator =(other);
            return *this;
        }

        some_numeric& operator =(some_numeric&& other) noexcept
        {
            T::operator =(std::move(other));
            return *this;
        }

        ~some_numeric()
        {
        }

    public:
        operator typename T::value_type() const = delete;
    };

    template <typename T>
    class none<Numeric_t<T>> :
        public none_numeric<Numeric_t<T>>
    {
    public:
        using none_numeric::none_numeric;
    };

    template <typename T>
    class maybe<Numeric_t<T>> :
        public maybe_numeric<Numeric_t<T>>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <typename T>
    class some<Numeric_t<T>> :
        public some_numeric<Numeric_t<T>>
    {
    public:
        using some_numeric::some_numeric;
    };

}

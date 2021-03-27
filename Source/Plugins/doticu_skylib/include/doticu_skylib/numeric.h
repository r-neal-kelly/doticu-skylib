/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe_numeric.h"
#include "doticu_skylib/traits.h"

namespace doticu_skylib {

    template <typename T, T none_value, enable_if_arithmetic_t<T> = true>
    class Numeric_Data_t
    {
    public:
        using value_type = T;

    public:
        static constexpr const T _NONE_ = static_cast<value_type>(none_value);
    };

    template <typename T>
    using enable_if_numeric_data_t = std::enable_if_t<
        std::is_convertible<T, Numeric_Data_t<typename T::value_type, T::_NONE_>>::value,
        Bool_t
    >;

    template <typename Data_t, enable_if_numeric_data_t<Data_t> = true>
    class Numeric_t :
        public Data_t
    {
    public:
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

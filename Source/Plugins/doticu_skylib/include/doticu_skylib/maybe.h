/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    template <typename T>
    using enable_if_integral_t = std::enable_if_t<
        std::is_integral<T>::value,
        Bool_t
    >;

    template <typename T>
    using enable_if_signed_integral_t = std::enable_if_t<
        std::is_integral<T>::value &&
        std::is_signed<T>::value,
        Bool_t
    >;

    template <typename T>
    using enable_if_unsigned_integral_t = std::enable_if_t<
        std::is_integral<T>::value &&
        std::is_unsigned<T>::value,
        Bool_t
    >;

    template <typename T>
    class none;
    template <typename T>
    class some;
    template <typename T>
    class maybe;

    // <Index_t>

    template <>
    class none<Index_t>
    {
    private:
        Index_t value;

    public:
        none() :
            value(-1)
        {
        }

        Bool_t operator==(const Index_t& other)
        {
            return other <= value;
        }

        Bool_t operator!=(const Index_t& other)
        {
            return !operator==(other);
        }

        Index_t operator()()
        {
            return operator Index_t();
        }

        operator Index_t()
        {
            return value;
        }

        template <typename TT>
        operator none<TT>()
        {
            return static_cast<TT>(value);
        }
    };

    template <>
    class some<Index_t>
    {
    private:
        Index_t value;

    public:
        some() = delete;

        template <typename T, enable_if_signed_integral_t<T> = true>
        some(T value) :
            value(value)
        {
        }

        some(const some& other) :
            value(other.value)
        {
        }

        some(some&& other) noexcept :
            value(std::exchange(other.value, none<Index_t>()))
        {
        }

        some& operator=(const some& other)
        {
            if (this != &other) {
                value = other.value;
            }
            return *this;
        }

        some& operator=(some&& other) noexcept
        {
            if (this != &other) {
                value = std::exchange(other.value, none<Index_t>());
            }
            return *this;
        }

        Index_t operator()()
        {
            return operator Index_t();
        }

        operator Index_t()
        {
            //SKYLIB_ASSERT_SOME(operator Bool_t());
            return value;
        }

        template <typename T, enable_if_signed_integral_t<T> = true>
        operator some<T>()
        {
            return static_cast<T>(value);
        }

        operator Bool_t()
        {
            return value != none<Index_t>();
        }
    };

    template <>
    class maybe<Index_t>
    {
    private:
        Index_t value;

    public:
        maybe() :
            value(none<Index_t>())
        {
        }

        maybe(none<Index_t> value) :
            value(value)
        {
        }

        template <typename T, enable_if_signed_integral_t<T> = true>
        maybe(T value) :
            value(value)
        {
        }

        maybe(const maybe& other) :
            value(other.value)
        {
        }

        maybe(maybe&& other) noexcept :
            value(std::exchange(other.value, none<Index_t>()))
        {
        }

        maybe& operator=(const maybe& other)
        {
            if (this != &other) {
                value = other.value;
            }
            return *this;
        }

        maybe& operator=(maybe&& other)
        {
            if (this != &other) {
                value = std::exchange(other.value, none<Index_t>());
            }
            return *this;
        }

        Index_t operator()()
        {
            return operator Index_t();
        }

        operator Index_t()
        {
            //SKYLIB_ASSERT_MAYBE(operator Bool_t());
            return value;
        }

        template <typename T, enable_if_signed_integral_t<T> = true>
        operator some<T>()
        {
            //SKYLIB_ASSERT_MAYBE(operator Bool_t());
            return static_cast<T>(value);
        }

        template <typename T, enable_if_signed_integral_t<T> = true>
        operator maybe<T>()
        {
            return static_cast<T>(value);
        }

        operator Bool_t()
        {
            return value != none<Index_t>();
        }
    };

    // <T*>

    template <typename T>
    class none<T*>
    {
    private:
        T* value;

    public:
        none() :
            value(nullptr)
        {
        }

        T* operator()()
        {
            return operator T*();
        }

        operator T*()
        {
            return value;
        }

        operator T*() const
        {
            return value;
        }

        template <typename TT>
        operator none<TT*>()
        {
            return static_cast<TT*>(value);
        }
    };

    template <typename T>
    class some<T*>
    {
    private:
        T* value;

    public:
        some() = delete;

        some(Nullptr_t) = delete;

        some(T* value) :
            value(value)
        {
        }

        some(const some& other) :
            value(other.value)
        {
        }

        some(some&& other) noexcept :
            value(std::exchange(other.value, none<T*>()))
        {
        }

        some& operator=(const some& other)
        {
            if (this != &other) {
                value = other.value;
            }
            return *this;
        }

        some& operator=(some&& other) noexcept
        {
            if (this != &other) {
                value = std::exchange(other.value, none<T*>());
            }
            return *this;
        }

        T* operator->()
        {
            return operator T*();
        }

        T& operator*()
        {
            return *operator T*();
        }

        T* operator()()
        {
            return operator T*();
        }

        Bool_t operator==(const some& other)
        {
            return value == other.value;
        }

        Bool_t operator!=(const some& other)
        {
            return !operator==(other);
        }

        operator T*()
        {
            //SKYLIB_ASSERT_SOME(operator Bool_t());
            return value;
        }

        operator T*() const
        {
            //SKYLIB_ASSERT_SOME(operator Bool_t());
            return value;
        }

        template <typename TT>
        operator some<TT*>()
        {
            return static_cast<TT*>(value);
        }

        operator Bool_t()
        {
            return value != none<T*>();
        }

        operator Bool_t() const
        {
            return value != none<T*>();
        }
    };

    template <>
    class some<Nullptr_t>
    {
    public:
        some() = delete;
    };

    template <typename T>
    class maybe<T*>
    {
    private:
        T* value;

    public:
        maybe() :
            value(none<T*>())
        {
        }

        maybe(none<T*> value) :
            value(value)
        {
        }

        maybe(T* value) :
            value(value)
        {
        }

        maybe(const maybe& other) :
            value(other.value)
        {
        }

        maybe(maybe&& other) noexcept :
            value(std::exchange(other.value, none<T*>()))
        {
        }

        maybe& operator=(const maybe& other)
        {
            if (this != &other) {
                value = other.value;
            }
            return *this;
        }

        maybe& operator=(maybe&& other)
        {
            if (this != &other) {
                value = std::exchange(other.value, none<T*>());
            }
            return *this;
        }

        T* operator->()
        {
            return operator T*();
        }

        T& operator*()
        {
            return *operator T*();
        }

        T* operator()()
        {
            return operator T*();
        }

        Bool_t operator==(const maybe& other)
        {
            return value == other.value;
        }

        Bool_t operator!=(const maybe& other)
        {
            return !operator==(other);
        }

        operator T*()
        {
            //SKYLIB_ASSERT_MAYBE(operator Bool_t());
            return value;
        }

        operator T*() const
        {
            //SKYLIB_ASSERT_MAYBE(operator Bool_t());
            return value;
        }

        template <typename TT>
        operator some<TT*>()
        {
            //SKYLIB_ASSERT_MAYBE(operator Bool_t());
            return static_cast<TT*>(value);
        }

        template <typename TT>
        operator maybe<TT*>()
        {
            return static_cast<TT*>(value);
        }

        operator Bool_t()
        {
            return value != none<T*>();
        }

        operator Bool_t() const
        {
            return value != none<T*>();
        }
    };

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    template <typename T>
    class None_p
    {
    public:
        None_p() :
            none(nullptr)
        {
        }

        operator T* ()
        {
            return none;
        }

    private:
        T* none;
    };

    template <typename T>
    class Some_p
    {
    public:
        Some_p() = delete;

        Some_p(Nullptr_t) = delete;

        Some_p(T* value) :
            value(value)
        {
        }

        Some_p(const Some_p& other) :
            value(other.value)
        {
        }

        Some_p(Some_p&& other) noexcept :
            value(std::exchange(other.value, None_p<T>()))
        {
        }

        Some_p& operator=(const Some_p& other)
        {
            if (this != &other) {
                value = other.value;
            }
            return *this;
        }

        Some_p& operator=(Some_p&& other) noexcept
        {
            if (this != &other) {
                value = std::exchange(other.value, None_p<T>());
            }
            return *this;
        }

        T* Value()
        {
            SKYLIB_ASSERT_SOME_P(operator Bool_t());
            return value;
        }

        T* operator->()
        {
            SKYLIB_ASSERT_SOME_P(operator Bool_t());
            return value;
        }

        T& operator*()
        {
            SKYLIB_ASSERT_SOME_P(operator Bool_t());
            return *value;
        }

        operator T*()
        {
            SKYLIB_ASSERT_SOME_P(operator Bool_t());
            return value;
        }

        operator Bool_t()
        {
            return value != None_p<T>();
        }

    private:
        T* value;
    };

    template <>
    class Some_p<Nullptr_t>
    {
    public:
        Some_p() = delete;
    };

    template <typename T>
    class Maybe_p
    {
    public:
        Maybe_p() :
            value(None_p<T>())
        {
        }

        Maybe_p(T* value) :
            value(value)
        {
        }

        Maybe_p(const Maybe_p& other) :
            value(other.value)
        {
        }

        Maybe_p(Maybe_p&& other) noexcept :
            value(std::exchange(other.value, None_p<T>()))
        {
        }

        Maybe_p& operator=(const Maybe_p& other)
        {
            if (this != &other) {
                value = other.value;
            }
            return *this;
        }

        Maybe_p& operator=(Maybe_p&& other)
        {
            if (this != &other) {
                value = std::exchange(other.value, None_p<T>());
            }
            return *this;
        }

        T* Value()
        {
            SKYLIB_ASSERT_MAYBE_P(operator Bool_t());
            return value;
        }

        T* operator->()
        {
            SKYLIB_ASSERT_MAYBE_P(operator Bool_t());
            return value;
        }

        T& operator*()
        {
            SKYLIB_ASSERT_MAYBE_P(operator Bool_t());
            return *value;
        }

        operator T*()
        {
            SKYLIB_ASSERT_MAYBE_P(operator Bool_t());
            return value;
        }

        operator Bool_t()
        {
            return value != None_p<T>();
        }

    private:
        T* value;
    };

}

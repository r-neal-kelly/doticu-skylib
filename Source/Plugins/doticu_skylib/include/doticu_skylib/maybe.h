/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/traits.h"

namespace doticu_skylib {

    template <typename T>
    class none;
    template <typename T>
    class maybe;
    template <typename T>
    class some;

    template <typename T>
    Bool_t Is_Equal(const none<T>& a, const T& b)
    {
        static_assert(false, "You must define Is_Equal() for your none type.");
    }

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
            return value;
        }

        template <typename T, enable_if_signed_integral_t<T> = true>
        operator some<T>()
        {
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

    // <T*>

    template <typename T>
    class none<T*>
    {
    public:
        using value_type = T;

    private:
        T* value;

    public:
        none() : value(nullptr) {}

        T* operator()()         { return value; }
        T* operator()() const   { return value; }

        explicit operator Bool_t()          { return false; }
        explicit operator Bool_t() const    { return false; }
    };

    template <typename T>
    class maybe<T*>
    {
    public:
        using value_type = T;

    private:
        T* value;

    public:
        maybe()                             : value(none<T*>()()) {}
        maybe(T* value)                     : value(value) {}
        maybe(const none<T*> other)         : value(other()) {}
        maybe(const maybe<T*>& other)       : value(other.value) {}
        maybe(maybe<T*>&& other) noexcept   : value(std::exchange(other.value, none<T*>()())) {}

        maybe<T*>& operator=(const maybe<T*>& other)
        {
            if (this != std::addressof(other)) {
                value = other.value;
            }
            return *this;
        }
        maybe<T*>& operator=(maybe<T*>&& other)
        {
            if (this != std::addressof(other)) {
                value = std::exchange(other.value, none<T*>()());
            }
            return *this;
        }

        T* operator()()         { return value; }
        T* operator()() const   { return value; }

        T* operator->()         { return value; }
        T* operator->() const   { return value; }

        T& operator*()          { return *value; }
        T& operator*() const    { return *value; }

        T** operator&()         { return &value; }
        T** operator&() const   { return &value; }

        T& operator[](size_t idx)       { return *(value + idx); }
        T& operator[](size_t idx) const { return *(value + idx); }

        Bool_t operator==(const maybe<T*>& other)       { return value == other(); }
        Bool_t operator==(const maybe<T*>& other) const { return value == other(); }
        Bool_t operator!=(const maybe<T*>& other)       { return !operator==(other); }
        Bool_t operator!=(const maybe<T*>& other) const { return !operator==(other); }

        explicit operator Bool_t()          { return value != none<T*>()(); }
        explicit operator Bool_t() const    { return value != none<T*>()(); }

        template <typename TT>
        operator maybe<TT*>()       { return static_cast<TT*>(value); }
        template <typename TT>
        operator maybe<TT*>() const { return static_cast<TT*>(value); }
    };

    template <typename T>
    class some<T*>
    {
    public:
        using value_type = T;

    private:
        T* value;

    public:
        some()                          = delete;
        some(Nullptr_t)                 = delete;
        some(T* value)                  : value(value) {}
        some(const some<T*>& other)     : value(other.value) {}
        some(some<T*>&& other) noexcept : value(std::exchange(other.value, none<T*>()())) {}

        some<T*>& operator=(const some<T*>& other)
        {
            if (this != std::addressof(other)) {
                value = other.value;
            }
            return *this;
        }
        some<T*>& operator=(some<T*>&& other) noexcept
        {
            if (this != std::addressof(other)) {
                value = std::exchange(other.value, none<T*>()());
            }
            return *this;
        }

        T* operator()()         { return value; }
        T* operator()() const   { return value; }

        T* operator->()         { return value; }
        T* operator->() const   { return value; }

        T& operator*()          { return *value; }
        T& operator*() const    { return *value; }

        T** operator&()         { return &value; }
        T** operator&() const   { return &value; }

        T& operator[](size_t idx)       { return *(value + idx); }
        T& operator[](size_t idx) const { return *(value + idx); }

        Bool_t operator==(const some<T*>& other)        { return value == other(); }
        Bool_t operator==(const some<T*>& other) const  { return value == other(); }
        Bool_t operator!=(const some<T*>& other)        { return !operator==(other); }
        Bool_t operator!=(const some<T*>& other) const  { return !operator==(other); }

        explicit operator Bool_t()          { return value != none<T*>()(); }
        explicit operator Bool_t() const    { return value != none<T*>()(); }

        template <typename TT>
        operator some<TT*>()        { return static_cast<TT*>(value); }
        template <typename TT>
        operator some<TT*>() const  { return static_cast<TT*>(value); }
    };

    template <>
    class some<Nullptr_t>
    {
    public:
        some() = delete;
    };

}

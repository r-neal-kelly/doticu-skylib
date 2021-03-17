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
    class none
    {
    public:
        using value_type = T;

    public:
        none()
        {
        }
    };

    template <typename T>
    class maybe
    {
    public:
        using value_type = T;

    protected:
        T       value;
        Bool_t  has_value;

    public:
        maybe()
            : value(T()), has_value(false)
        {
        }

        maybe(const none<T> none)
            : value(T()), has_value(false)
        {
        }

        maybe(const T value)
            : value(value), has_value(true)
        {
        }

        maybe(const T value, Bool_t has_value)
            : value(value), has_value(has_value)
        {
        }

        maybe(const some<T>& other)
            : value(other()), has_value(true)
        {
        }

        maybe(const maybe& other)
            : value(other.value), has_value(other.has_value)
        {
        }

        maybe(maybe&& other) noexcept
            : value(std::exchange(other.value, T())), has_value(std::exchange(other.has_value, false))
        {
        }

        maybe& operator =(const maybe& other)
        {
            if (this != std::addressof(other)) {
                this->value = other.value;
                this->has_value = other.has_value;
            }
            return *this;
        }

        maybe& operator =(maybe&& other)
        {
            if (this != std::addressof(other)) {
                this->value = std::exchange(other.value, T());
                this->has_value = std::exchange(other.value, false);
            }
            return *this;
        }

        ~maybe()
        {
            this->value.~T();
            this->has_value = false;
        }

    public:
        Bool_t Has_Value() const
        {
            return this->has_value;
        }

        T Value() const
        {
            return this->value;
        }

    public:
        T operator ()() const
        {
            return this->value;
        }
    };

    template <typename T>
    class some
    {
    public:
        using value_type = T;

    protected:
        T value;

    public:
        some(const T value)
            : value(value)
        {
        }

        some(const some& other)
            : value(other.value)
        {
        }

        some(some&& other) noexcept
            : value(std::exchange(other.value, T()))
        {
        }

        some& operator =(const some& other)
        {
            if (this != std::addressof(other)) {
                this->value = other.value;
            }
            return *this;
        }

        some& operator =(some&& other)
        {
            if (this != std::addressof(other)) {
                this->value = std::exchange(other.value, T());
            }
            return *this;
        }

        ~some()
        {
            this->value.~T();
        }

    public:
        T Value() const
        {
            return this->value;
        }

    public:
        operator T() const
        {
            return this->value;
        }

    public:
        T operator ()() const
        {
            return this->value;
        }
    };

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

        Bool_t operator !()         { return !static_cast<Bool_t>(*this); }
        Bool_t operator !() const   { return !static_cast<Bool_t>(*this); }
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

        ~maybe()
        {
            this->value = none<T*>()();
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

        explicit operator Bool_t()          { return value != none<T*>()(); }
        explicit operator Bool_t() const    { return value != none<T*>()(); }
        explicit operator T*&()             { return this->value; }

        Bool_t operator !()         { return !static_cast<Bool_t>(*this); }
        Bool_t operator !() const   { return !static_cast<Bool_t>(*this); }

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

        ~some()
        {
            this->value = none<T*>()();
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

        explicit operator Bool_t()          { return value != none<T*>()(); }
        explicit operator Bool_t() const    { return value != none<T*>()(); }
        explicit operator T*&()             { return this->value; }

        Bool_t operator !()         { return !static_cast<Bool_t>(*this); }
        Bool_t operator !() const   { return !static_cast<Bool_t>(*this); }

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

    template <
        typename T,
        template <typename> typename TT_1,
        template <typename> typename TT_2,
        std::enable_if_t<
            (std::is_same<TT_1<T*>, none<T*>>::value ||
            std::is_same<TT_1<T*>, maybe<T*>>::value ||
            std::is_same<TT_1<T*>, some<T*>>::value) &&
            (std::is_same<TT_2<T*>, none<T*>>::value ||
            std::is_same<TT_2<T*>, maybe<T*>>::value ||
            std::is_same<TT_2<T*>, some<T*>>::value),
            Bool_t
        > = true
    > inline Bool_t operator ==(const TT_1<T*>& a, const TT_2<T*>& b)
    {
        return a() == b();
    }

    template <
        typename T,
        template <typename> typename TT_1,
        template <typename> typename TT_2,
        std::enable_if_t<
            (std::is_same<TT_1<T*>, none<T*>>::value ||
            std::is_same<TT_1<T*>, maybe<T*>>::value ||
            std::is_same<TT_1<T*>, some<T*>>::value) &&
            (std::is_same<TT_2<T*>, none<T*>>::value ||
            std::is_same<TT_2<T*>, maybe<T*>>::value ||
            std::is_same<TT_2<T*>, some<T*>>::value),
            Bool_t
        > = true
    > inline Bool_t operator !=(const TT_1<T*>& a, const TT_2<T*>& b)
    {
        return a() != b();
    }

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    template <typename T>
    class unique
    {
    public:
        using value_type = T;

    protected:
        maybe<T*> value;

    public:
        unique() :
            value(nullptr)
        {
        }

        unique(std::nullptr_t value) :
            value(nullptr)
        {
        }

        template <typename TT>
        unique(TT* value) :
            value(static_cast<T*>(value))
        {
        }

        template <typename TT>
        unique(none<TT*> value) :
            value(static_cast<T*>(value()))
        {
        }

        template <typename TT>
        unique(maybe<TT*> value) :
            value(static_cast<T*>(value()))
        {
        }

        template <typename TT>
        unique(some<TT*> value) :
            value(static_cast<T*>(value()))
        {
        }

        template <typename TT>
        unique(const unique<TT>& other) = delete;

        template <typename TT>
        unique(unique<TT>&& other) noexcept :
            value(static_cast<maybe<T*>>(std::exchange(other.value, none<TT*>())))
        {
        }

        template <typename TT>
        unique& operator =(const unique<TT>& other) = delete;

        template <typename TT>
        unique& operator =(unique<TT>&& other) noexcept
        {
            if (this != std::addressof(other)) {
                this->value = static_cast<maybe<T*>>(std::exchange(other.value, none<TT*>()));
            }
        }

        ~unique()
        {
            if (this->value) {
                delete this->value();
                this->value = nullptr;
            }
        }

    public:
        explicit operator Bool_t() const { return static_cast<Bool_t>(this->value); }

    public:
        Bool_t              operator !() const              { return !static_cast<Bool_t>(*this); }
        T&                  operator *() const              { return *this->value; }
        some<maybe<T*>*>    operator &() const              { return &this->value(); }
        maybe<T*>           operator ()() const             { return this->value; }
        maybe<T*>           operator ->() const             { return this->value; }
        T&                  operator [](size_t index) const { return *(this->value() + index); }
    };

    template <typename T>
    class none<unique<T>>
    {
    public:
        using value_type = unique<T>;

    public:
        none() {}
    };

    template <typename T>
    class maybe<unique<T>>
    {
    public:
        using value_type = unique<T>;

    protected:
        value_type value;

    public:
        maybe()                         : value(nullptr) {}
        maybe(none<value_type> other)   : value(nullptr) {}
        maybe(value_type value)         : value(std::move(value)) {}
        maybe(const maybe& other)       = delete;
        maybe(maybe&& other) noexcept   : value(std::move(other.value)) {}

        template <typename TT>
        maybe(TT* value) :
            value(value)
        {
        }

        maybe& operator =(const maybe& other) = delete;

        maybe& operator =(maybe&& other) noexcept
        {
            if (this != std::addressof(other)) {
                this->value = std::move(other.value);
            }
            return *this;
        }

        ~maybe()
        {
            value.~value_type();
        }

    public:
        explicit operator Bool_t() const { return this->value.operator Bool_t(); }

    public:
        Bool_t              operator !() const              { return this->value.operator !(); }
        T&                  operator *() const              { return this->value.operator *(); }
        some<maybe<T*>*>    operator &() const              { return this->value.operator &(); }
        maybe<T*>           operator ()() const             { return this->value.operator ()(); }
        maybe<T*>           operator ->() const             { return this->value.operator ->(); }
        T&                  operator [](size_t index) const { return this->value.operator [](index); }
    };

    template <typename T>
    class some<unique<T>>
    {
    public:
        using value_type = unique<T>;

    protected:
        value_type value;

    public:
        some()                          : value(nullptr) {}
        some(none<value_type> other)    : value(nullptr) {}
        some(value_type value)          : value(std::move(value)) {}
        some(const some& other)         = delete;
        some(some&& other) noexcept     : value(std::move(other.value)) {}

        template <typename TT>
        some(TT* value) :
            value(value)
        {
        }

        some& operator =(const some& other) = delete;

        some& operator =(some&& other) noexcept
        {
            if (this != std::addressof(other)) {
                this->value = std::move(other.value);
            }
            return *this;
        }

        ~some()
        {
            value.~value_type();
        }

    public:
        explicit operator Bool_t() const { return this->value.operator Bool_t(); }

    public:
        Bool_t              operator !() const              { return this->value.operator !(); }
        T&                  operator *() const              { return this->value.operator *(); }
        some<maybe<T*>*>    operator &() const              { return this->value.operator &(); }
        maybe<T*>           operator ()() const             { return this->value.operator ()(); }
        maybe<T*>           operator ->() const             { return this->value.operator ->(); }
        T&                  operator [](size_t index) const { return this->value.operator [](index); }
    };

}

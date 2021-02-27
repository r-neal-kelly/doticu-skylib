/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    template <typename T>
    class unique_destroyer // this should call the destructor as well.
    {
    public:
        static void Destroy(some<T*> value)
        {
            SKYLIB_ASSERT_SOME(value);
            delete value();
        }
    };

    template <typename T>
    class unique
    {
    public:
        using value_type = T;

    public:
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
            value(static_cast<TT*>(value))
        {
        }

        template <typename TT>
        unique(maybe<TT*> value) :
            value(static_cast<maybe<T*>>(value))
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
        unique& operator=(const unique<TT>& other) = delete;

        template <typename TT>
        unique& operator=(unique<TT>&& other) noexcept
        {
            if (this != std::addressof(other)) {
                this->value = static_cast<maybe<T*>>(std::exchange(other.value, none<TT*>()));
            }
        }

        ~unique()
        {
            if (this->value) {
                unique_destroyer<T>::Destroy(this->value());
                this->value = nullptr;
            }
        }

    public:
        explicit operator Bool_t()          { return static_cast<Bool_t>(this->value); }
        explicit operator Bool_t() const    { return static_cast<Bool_t>(this->value); }

        Bool_t operator !()         { return !static_cast<Bool_t>(*this); }
        Bool_t operator !() const   { return !static_cast<Bool_t>(*this); }

        maybe<T*> operator()()          { return this->value; }
        maybe<T*> operator()() const    { return this->value; }

        maybe<T*> operator->()          { return this->value; }
        maybe<T*> operator->() const    { return this->value; }

        T& operator*()          { return *this->value; }
        T& operator*() const    { return *this->value; }

        some<maybe<T*>*> operator&()        { return &this->value(); }
        some<maybe<T*>*> operator&() const  { return &this->value(); }

        T& operator[](size_t index)         { return *(this->value() + index); }
        T& operator[](size_t index) const   { return *(this->value() + index); }
    };

}

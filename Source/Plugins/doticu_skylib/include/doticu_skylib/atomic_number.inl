/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/atomic.inl"
#include "doticu_skylib/atomic_number.h"

namespace doticu_skylib {

    template <typename T>
    inline Atomic_Number_t<T>::Atomic_Number_t() :
        value(0)
    {
    }

    template <typename T>
    inline Atomic_Number_t<T>::Atomic_Number_t(const T value) :
        value(value)
    {
    }

    template <typename T>
    inline Atomic_Number_t<T>::Atomic_Number_t(const Atomic_Number_t& other) :
        value(Atomic_t::Access(other.value))
    {
    }

    template <typename T>
    inline Atomic_Number_t<T>::Atomic_Number_t(Atomic_Number_t&& other) noexcept :
        value(Atomic_t::Exchange_Assign(other.value, 0))
    {
    }

    template <typename T>
    inline Atomic_Number_t<T>& Atomic_Number_t<T>::operator =(const Atomic_Number_t& other)
    {
        if (this != std::addressof(other)) {
            Atomic_t::Assign(this->value, Atomic_t::Access(other.value));
        }
        return *this;
    }

    template <typename T>
    inline Atomic_Number_t<T>& Atomic_Number_t<T>::operator =(Atomic_Number_t&& other) noexcept
    {
        if (this != std::addressof(other)) {
            Atomic_t::Assign(this->value, Atomic_t::Exchange_Assign(other.value, 0));
        }
        return *this;
    }

    template <typename T>
    inline Atomic_Number_t<T>::~Atomic_Number_t()
    {
        Atomic_t::Assign(this->value, 0);
    }

    template <typename T>
    inline Atomic_Number_t<T>::operator T() const
    {
        return Atomic_t::Access(this->value);
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator ()() const
    {
        return Atomic_t::Access(this->value);
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator =(const T other)
    {
        return Atomic_t::Assign(this->value, other);
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator +(const T other) const
    {
        return Atomic_t::Access(this->value) + other;
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator -(const T other) const
    {
        return Atomic_t::Access(this->value) - other;
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator +=(const T other)
    {
        return Atomic_t::Add(this->value, other);
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator -=(const T other)
    {
        return Atomic_t::Subtract(this->value, other);
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator ++()
    {
        return Atomic_t::Add(this->value, 1);
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator ++(int)
    {
        return Atomic_t::Exchange_Add(this->value, 1);
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator --()
    {
        return Atomic_t::Subtract(this->value, 1);
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator --(int)
    {
        return Atomic_t::Exchange_Subtract(this->value, 1);
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator ~() const
    {
        return ~Atomic_t::Access(this->value);
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator |(const T other) const
    {
        return Atomic_t::Access(this->value) | other;
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator &(const T other) const
    {
        return Atomic_t::Access(this->value) & other;
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator ^(const T other) const
    {
        return Atomic_t::Access(this->value) ^ other;
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator |=(const T other)
    {
        return Atomic_t::Or(this->value, other);
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator &=(const T other)
    {
        return Atomic_t::And(this->value, other);
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator ^=(const T other)
    {
        return Atomic_t::Xor(this->value, other);
    }

}

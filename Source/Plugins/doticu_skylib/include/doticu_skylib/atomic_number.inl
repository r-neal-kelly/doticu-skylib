/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/atomic.inl"
#include "doticu_skylib/atomic_number.h"

namespace doticu_skylib {

    template <typename T>
    inline Atomic_Number_t<T>::Atomic_Number_t(const T value) :
        value(value)
    {
    }

    template <typename T>
    inline Atomic_Number_t<T>::operator T()
    {
        return Atomic_t::Access(this->value);
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator ()()
    {
        return Atomic_t::Access(this->value);
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator =(const T other)
    {
        return Atomic_t::Assign(this->value, other);
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator +(const T other)
    {
        return Atomic_t::Access(this->value) + other;
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator -(const T other)
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
    inline T Atomic_Number_t<T>::operator |(const T other)
    {
        return Atomic_t::Access(this->value) | other;
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator &(const T other)
    {
        return Atomic_t::Access(this->value) & other;
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator ^(const T other)
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

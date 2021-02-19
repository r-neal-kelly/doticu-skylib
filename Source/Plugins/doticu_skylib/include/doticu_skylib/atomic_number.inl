/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/atomic_number.h"

namespace doticu_skylib {

    FORCEINLINE u32 Interlocked_Exchange_Add(volatile u32& subject, u32 value)
    {
        return _InterlockedExchangeAdd((volatile long*)&subject, (long)value);
    }

    FORCEINLINE u32 Interlocked_Exchange_Subtract(volatile u32& subject, u32 value)
    {
        return _InterlockedExchangeAdd((volatile long*)&subject, -(long)value);
    }

    FORCEINLINE u32 Interlocked_Or(volatile u32& subject, u32 value)
    {
        return _InterlockedOr((volatile long*)&subject, (long)value);
    }

    FORCEINLINE u32 Interlocked_And(volatile u32& subject, u32 value)
    {
        return _InterlockedAnd((volatile long*)&subject, (long)value);
    }

    FORCEINLINE u32 Interlocked_Xor(volatile u32& subject, u32 value)
    {
        return _InterlockedXor((volatile long*)&subject, (long)value);
    }

    template <typename T>
    inline Atomic_Number_t<T>::Atomic_Number_t(const T value) :
        value(value)
    {
    }

    template <typename T>
    inline Atomic_Number_t<T>::operator T ()
    {
        return Interlocked_Exchange_Add(this->value, 0);
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator () ()
    {
        return static_cast<value_type>(*this);
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator + (const T other)
    {
        return static_cast<T>(*this) + other;
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator - (const T other)
    {
        return static_cast<T>(*this) - other;
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator += (const T other)
    {
        return Interlocked_Exchange_Add(this->value, other) + other;
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator -= (const T other)
    {
        return Interlocked_Exchange_Subtract(this->value, other) - other;
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator ++ ()
    {
        return InterlockedIncrement(&this->value);
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator ++ (int)
    {
        return Interlocked_Exchange_Add(this->value, 1);
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator -- ()
    {
        return InterlockedDecrement(&this->value);
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator -- (int)
    {
        return Interlocked_Exchange_Subtract(this->value, 1);
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator | (const T other)
    {
        return static_cast<T>(*this) | other;
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator & (const T other)
    {
        return static_cast<T>(*this) & other;
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator ^ (const T other)
    {
        return static_cast<T>(*this) ^ other;
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator |= (const T other)
    {
        return Interlocked_Or(this->value, other) | other;
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator &= (const T other)
    {
        return Interlocked_And(this->value, other) & other;
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator ^= (const T other)
    {
        return Interlocked_Xor(this->value, other) ^ other;
    }

}

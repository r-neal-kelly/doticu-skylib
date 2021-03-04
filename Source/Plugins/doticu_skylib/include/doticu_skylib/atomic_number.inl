/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/atomic_number.h"

namespace doticu_skylib {

    /* Exchange_Add */

    FORCEINLINE u8 Interlocked_Exchange_Add(volatile u8& subject, u8 value)
    {
        return _InterlockedExchangeAdd8((volatile char*)&subject, (char)value);
    }

    FORCEINLINE u16 Interlocked_Exchange_Add(volatile u16& subject, u16 value)
    {
        return _InterlockedExchangeAdd16((volatile short*)&subject, (short)value);
    }

    FORCEINLINE u32 Interlocked_Exchange_Add(volatile u32& subject, u32 value)
    {
        return _InterlockedExchangeAdd((volatile long*)&subject, (long)value);
    }

    FORCEINLINE u64 Interlocked_Exchange_Add(volatile u64& subject, u64 value)
    {
        return _InterlockedExchangeAdd64((volatile long long*)&subject, (long long)value);
    }

    FORCEINLINE s8 Interlocked_Exchange_Add(volatile s8& subject, s8 value)
    {
        return _InterlockedExchangeAdd8((volatile char*)&subject, (char)value);
    }

    FORCEINLINE s16 Interlocked_Exchange_Add(volatile s16& subject, s16 value)
    {
        return _InterlockedExchangeAdd16((volatile short*)&subject, (short)value);
    }

    FORCEINLINE s32 Interlocked_Exchange_Add(volatile s32& subject, s32 value)
    {
        return _InterlockedExchangeAdd((volatile long*)&subject, (long)value);
    }

    FORCEINLINE s64 Interlocked_Exchange_Add(volatile s64& subject, s64 value)
    {
        return _InterlockedExchangeAdd64((volatile long long*)&subject, (long long)value);
    }

    /* Exchange_Subtract */

    FORCEINLINE u8 Interlocked_Exchange_Subtract(volatile u8& subject, u8 value)
    {
        return _InterlockedExchangeAdd8((volatile char*)&subject, -(char)value);
    }

    FORCEINLINE u16 Interlocked_Exchange_Subtract(volatile u16& subject, u16 value)
    {
        return _InterlockedExchangeAdd16((volatile short*)&subject, -(short)value);
    }

    FORCEINLINE u32 Interlocked_Exchange_Subtract(volatile u32& subject, u32 value)
    {
        return _InterlockedExchangeAdd((volatile long*)&subject, -(long)value);
    }

    FORCEINLINE u64 Interlocked_Exchange_Subtract(volatile u64& subject, u64 value)
    {
        return _InterlockedExchangeAdd64((volatile long long*)&subject, -(long long)value);
    }

    FORCEINLINE s8 Interlocked_Exchange_Subtract(volatile s8& subject, s8 value)
    {
        return _InterlockedExchangeAdd8((volatile char*)&subject, -(char)value);
    }

    FORCEINLINE s16 Interlocked_Exchange_Subtract(volatile s16& subject, s16 value)
    {
        return _InterlockedExchangeAdd16((volatile short*)&subject, -(short)value);
    }

    FORCEINLINE s32 Interlocked_Exchange_Subtract(volatile s32& subject, s32 value)
    {
        return _InterlockedExchangeAdd((volatile long*)&subject, -(long)value);
    }

    FORCEINLINE s64 Interlocked_Exchange_Subtract(volatile s64& subject, s64 value)
    {
        return _InterlockedExchangeAdd64((volatile long long*)&subject, -(long long)value);
    }

    /* Or */

    FORCEINLINE u8 Interlocked_Or(volatile u8& subject, u8 value)
    {
        return _InterlockedOr8((volatile char*)&subject, (char)value);
    }

    FORCEINLINE u16 Interlocked_Or(volatile u16& subject, u16 value)
    {
        return _InterlockedOr16((volatile short*)&subject, (short)value);
    }

    FORCEINLINE u32 Interlocked_Or(volatile u32& subject, u32 value)
    {
        return _InterlockedOr((volatile long*)&subject, (long)value);
    }

    FORCEINLINE u64 Interlocked_Or(volatile u64& subject, u64 value)
    {
        return _InterlockedOr64((volatile long long*)&subject, (long long)value);
    }

    FORCEINLINE s8 Interlocked_Or(volatile s8& subject, s8 value)
    {
        return _InterlockedOr8((volatile char*)&subject, (char)value);
    }

    FORCEINLINE s16 Interlocked_Or(volatile s16& subject, s16 value)
    {
        return _InterlockedOr16((volatile short*)&subject, (short)value);
    }

    FORCEINLINE s32 Interlocked_Or(volatile s32& subject, s32 value)
    {
        return _InterlockedOr((volatile long*)&subject, (long)value);
    }

    FORCEINLINE s64 Interlocked_Or(volatile s64& subject, s64 value)
    {
        return _InterlockedOr64((volatile long long*)&subject, (long long)value);
    }

    /* And */

    FORCEINLINE u8 Interlocked_And(volatile u8& subject, u8 value)
    {
        return _InterlockedAnd8((volatile char*)&subject, (char)value);
    }

    FORCEINLINE u16 Interlocked_And(volatile u16& subject, u16 value)
    {
        return _InterlockedAnd16((volatile short*)&subject, (short)value);
    }

    FORCEINLINE u32 Interlocked_And(volatile u32& subject, u32 value)
    {
        return _InterlockedAnd((volatile long*)&subject, (long)value);
    }

    FORCEINLINE u64 Interlocked_And(volatile u64& subject, u64 value)
    {
        return _InterlockedAnd64((volatile long long*)&subject, (long long)value);
    }

    FORCEINLINE s8 Interlocked_And(volatile s8& subject, s8 value)
    {
        return _InterlockedAnd8((volatile char*)&subject, (char)value);
    }

    FORCEINLINE s16 Interlocked_And(volatile s16& subject, s16 value)
    {
        return _InterlockedAnd16((volatile short*)&subject, (short)value);
    }

    FORCEINLINE s32 Interlocked_And(volatile s32& subject, s32 value)
    {
        return _InterlockedAnd((volatile long*)&subject, (long)value);
    }

    FORCEINLINE s64 Interlocked_And(volatile s64& subject, s64 value)
    {
        return _InterlockedAnd64((volatile long long*)&subject, (long long)value);
    }

    /* Xor */

    FORCEINLINE u8 Interlocked_Xor(volatile u8& subject, u8 value)
    {
        return _InterlockedXor8((volatile char*)&subject, (char)value);
    }

    FORCEINLINE u16 Interlocked_Xor(volatile u16& subject, u16 value)
    {
        return _InterlockedXor16((volatile short*)&subject, (short)value);
    }

    FORCEINLINE u32 Interlocked_Xor(volatile u32& subject, u32 value)
    {
        return _InterlockedXor((volatile long*)&subject, (long)value);
    }

    FORCEINLINE u64 Interlocked_Xor(volatile u64& subject, u64 value)
    {
        return _InterlockedXor64((volatile long long*)&subject, (long long)value);
    }

    FORCEINLINE s8 Interlocked_Xor(volatile s8& subject, s8 value)
    {
        return _InterlockedXor8((volatile char*)&subject, (char)value);
    }

    FORCEINLINE s16 Interlocked_Xor(volatile s16& subject, s16 value)
    {
        return _InterlockedXor16((volatile short*)&subject, (short)value);
    }

    FORCEINLINE s32 Interlocked_Xor(volatile s32& subject, s32 value)
    {
        return _InterlockedXor((volatile long*)&subject, (long)value);
    }

    FORCEINLINE s64 Interlocked_Xor(volatile s64& subject, s64 value)
    {
        return _InterlockedXor64((volatile long long*)&subject, (long long)value);
    }

    /* Atomic_Number_t */

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
        return Interlocked_Exchange_Add(this->value, 1) + 1;
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator ++ (int)
    {
        return Interlocked_Exchange_Add(this->value, 1);
    }

    template <typename T>
    inline T Atomic_Number_t<T>::operator -- ()
    {
        return Interlocked_Exchange_Subtract(this->value, 1) - 1;
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

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    template <typename T>
    class Atomic_Number_t
    {
    public:
        using value_type = T;

    protected:
        volatile T value; // 0

    public:
        Atomic_Number_t();
        Atomic_Number_t(const T value);
        Atomic_Number_t(const Atomic_Number_t& other);
        Atomic_Number_t(Atomic_Number_t&& other) noexcept;
        Atomic_Number_t& operator =(const Atomic_Number_t& other);
        Atomic_Number_t& operator =(Atomic_Number_t&& other) noexcept;
        ~Atomic_Number_t();

    public:
        operator T() const;

    public:
        T operator ()() const;

        T operator =(const T other);
        T operator +(const T other) const;
        T operator -(const T other) const;
        T operator +=(const T other);
        T operator -=(const T other);
        T operator ++();
        T operator ++(int);
        T operator --();
        T operator --(int);

        T operator ~() const;
        T operator |(const T other) const;
        T operator &(const T other) const;
        T operator ^(const T other) const;
        T operator |=(const T other);
        T operator &=(const T other);
        T operator ^=(const T other);
    };
    STATIC_ASSERT(sizeof(Atomic_Number_t<u32>) == 0x4);

}

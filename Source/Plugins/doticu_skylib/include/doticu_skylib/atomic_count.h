/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    // make an Atomic_Number_t<T> that this can inherit from, so we can do flag ops and other ops all over the place correctly

    class Atomic_Count_t // BSIntrusiveRefCounted
    {
    public:
        volatile u32 atomic_count; // 0

    public:
        u32 Atomic_Count();
        u32 Increment_Atomic();
        u32 Decrement_Atomic();
    };
    STATIC_ASSERT(sizeof(Atomic_Count_t) == 0x4);

}

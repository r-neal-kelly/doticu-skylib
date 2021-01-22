/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Atomic_Count_t
    {
    public:
        volatile u32 atomic_count; // 0

    public:
        u32 Count();
        u32 Increment();
        u32 Decrement();
    };
    STATIC_ASSERT(sizeof(Atomic_Count_t) == 0x4);

}

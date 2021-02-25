/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/scrap_array_allocator.h"

namespace doticu_skylib {

    template <typename T>
    class Scrap_Array_t :               // BSScrapArray
        public Scrap_Array_Allocator_t  // 00
    {
    public:
        using value_type = T;

    protected:
        u32 count;  // 18
        u32 pad_14; // 1C

    public:
        maybe<T*>   Entries();
        u32         Count();
        T&          At(u32 index);

    public:
        T& operator [] (u32 index);
    };
    STATIC_ASSERT(sizeof(Scrap_Array_t<s32>) == 0x20);

}

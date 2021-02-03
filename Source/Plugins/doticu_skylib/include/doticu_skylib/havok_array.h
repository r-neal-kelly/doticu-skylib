/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    template <typename T>
    class Havok_Array_t // hkArray
    {
    public:
        maybe<T*>   entries;            // 0
        u32         count;              // 8
        u32         capacity_and_flags; // C
    };
    STATIC_ASSERT(sizeof(Havok_Array_t<void*>) == 0x10);

}

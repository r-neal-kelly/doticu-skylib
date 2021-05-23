/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    template <typename T>
    class Singleton_t   // BSTSingletonSDM
    {
    public:
        u64 unk_00; // 00
    };
    STATIC_ASSERT(sizeof(Singleton_t<void*>) == 0x8);

}

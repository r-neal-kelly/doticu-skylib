/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Spin_Lock_t
    {
    public:
        volatile u32    owning_thread_id;
        volatile u32    lock_count;
    };
    STATIC_ASSERT(sizeof(Spin_Lock_t) == 0x8);

}

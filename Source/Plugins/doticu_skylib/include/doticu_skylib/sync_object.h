/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/atomic_count.h"

namespace doticu_skylib {

    class Sync_Object_t :       // SyncQueueObj
        public Atomic_Count_t   // 00
    {
    public:
        virtual ~Sync_Object_t(); // 0

    public:
        u32 unk_0C; // 0C
    };
    STATIC_ASSERT(sizeof(Sync_Object_t) == 0x10);

}

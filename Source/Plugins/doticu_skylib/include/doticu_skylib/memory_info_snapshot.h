/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Memory_Info_Snapshot_t // MemoryStats
    {
    public:
        maybe<const char*>  name;           // 00
        size_t              used_size;      // 08
        size_t              committed_size; // 10
        size_t              reserved_size;  // 18
        u32                 overhead_size;  // 20
        u32                 pad_24;         // 24
        size_t              free_size;      // 28
    };
    STATIC_ASSERT(sizeof(Memory_Info_Snapshot_t) == 0x30);

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Memory_Heap_Snapshot_t // HeapStats
    {
    public:
        maybe<const char*>  name;                       // 00
        size_t              size;                       // 08
        size_t              committed_size;             // 10
        size_t              allocated_in_blocks_size;   // 18
        u32                 block_count;                // 20
        u32                 free_block_count;           // 24
        size_t              free_in_blocks_size;        // 28
        size_t              used_in_blocks_size;        // 30
        size_t              smallest_free_block_size;   // 38
        size_t              largest_free_block_size;    // 40
        size_t              overhead_size;              // 48
        size_t              unk_50;                     // 50
        size_t              block_overhead_size;        // 58
        size_t              free_size;                  // 60
    };
    STATIC_ASSERT(sizeof(Memory_Heap_Snapshot_t) == 0x68);

}

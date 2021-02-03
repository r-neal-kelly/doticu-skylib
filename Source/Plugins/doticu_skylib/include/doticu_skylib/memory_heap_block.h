/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Memory_Heap_Block_t // HeapBlock
    {
    public:
        union Conditional_u
        {
            maybe<Memory_Heap_Block_t*> previous_free;
            u32                         used_flags;
        };
        STATIC_ASSERT(sizeof(Conditional_u) == 0x8);

    public:
        size_t                      size;           // 00
        maybe<Memory_Heap_Block_t*> previous;       // 08
        Conditional_u               conditional;    // 10
        maybe<Memory_Heap_Block_t*> next_free;      // 18
    };
    STATIC_ASSERT(sizeof(Memory_Heap_Block_t) == 0x20);

}

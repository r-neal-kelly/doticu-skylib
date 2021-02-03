/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe.h"

#include "doticu_skylib/memory_heap.h"

namespace doticu_skylib {

    class Memory_Physical_Heap_t :  // ZeroOverheadHeap
        public Memory_Heap_i        // 00
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E98190, // 690289
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Memory_Physical_Heap_t(); // 0

    public:
        size_t              size;               // 08
        maybe<const char*>  name;               // 10
        maybe<Byte_t*>      data;               // 18
        maybe<Byte_t*>      next_free_block;    // 20
        u32                 unk_28;             // 28
        u32                 unk_2C;             // 2C
        u32                 unk_30;             // 30
        u32                 unk_34;             // 34
    };
    STATIC_ASSERT(sizeof(Memory_Physical_Heap_t) == 0x38);

}

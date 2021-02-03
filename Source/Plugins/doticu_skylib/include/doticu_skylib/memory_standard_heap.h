/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "doticu_skylib/memory_virtual_heap.h"

namespace doticu_skylib {

    class Memory_Standard_Heap_t :      // MemoryHeap
        public Memory_Virtual_Heap_t    // 00
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E980E8, // 690285
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Memory_Standard_Heap_t(); // 0

    public:
        Bool_t  unk_2A8;    // 2A8
        u8      pad_2A9;    // 2A9
        u16     pad_2AA;    // 2AA
        u32     pad_2AC;    // 2AC
    };
    STATIC_ASSERT(sizeof(Memory_Standard_Heap_t) == 0x2B0);

}

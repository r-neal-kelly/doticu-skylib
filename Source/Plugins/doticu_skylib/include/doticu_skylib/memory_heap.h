/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "doticu_skylib/memory_allocator.h"

namespace doticu_skylib {

    class Memory_Heap_Snapshot_t;

    class Memory_Heap_i :           // IMemoryHeap
        public Memory_Allocator_i   // 00
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E98138, // 690287
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual             ~Memory_Heap_i();                                                               // 0

        // Memory_Heap_i
        virtual const char* Get_Heap_Name() const                                                   = 0;    // 7
        virtual void*       Allocate_Heap_Block(size_t byte_count, u32 alignment)                   = 0;    // 8
        virtual void        Deallocate_Heap_Block(void* block, u32 alignment)                       = 0;    // 9
        virtual Bool_t      Has_Heap_Block(const void* block) const                                 = 0;    // A
        virtual size_t      Get_Heap_Block_Size(const void* block) const                            = 0;    // B
        virtual void        Get_Heap_Snaphot(Memory_Heap_Snapshot_t& result, Bool_t get_full) const = 0;    // C
        virtual Bool_t      _D(size_t byte_count, u32 context)                                      = 0;    // D
        virtual u32         Get_Heap_Page_Size() const                                              = 0;    // E
    };
    STATIC_ASSERT(sizeof(Memory_Heap_i) == 0x8);

}

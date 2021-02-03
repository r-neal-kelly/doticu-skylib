/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Memory_Heap_i;

    class Memory_t // MemoryManager
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                SELF        = 0x01EBD280,   // 514110
                ALLOCATE    = 0x00C02260,   // 66859
                REALLOCATE  = 0x00C024B0,   // 66860
                DEALLOCATE  = 0x00C02560,   // 66861
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Memory_t*> Self();

    public:
        Bool_t                  is_initialized;             // 000
        u16                     heap_count;                 // 002
        u16                     physical_heap_count;        // 004
        maybe<Memory_Heap_i**>  heaps;                      // 008
        maybe<Bool_t*>          unk_010;                    // 010
        maybe<Memory_Heap_i*>   context_heaps[127];         // 018
        void*                   unk_410;                    // 410
        maybe<Memory_Heap_i**>  physical_heaps;             // 418
        maybe<Memory_Heap_i*>   big_allocations_heap;       // 420
        maybe<Memory_Heap_i*>   emergency_heap;             // 428
        void*                   unk_430;                    // 430
        void*                   unk_438;                    // 438
        maybe<Memory_Heap_i*>   external_havok_allocator;   // 440
        Bool_t                  unk_448;                    // 448
        Bool_t                  unk_449;                    // 449
        u32                     system_byte_count;          // 44C
        u32                     malloc_byte_count;          // 450
        u32                     pool_alignment;             // 450
        u32                     unk_458;                    // 458
        u64                     failed_allocation_size;     // 460
        u32                     unk_468;                    // 468
        u32                     pad_46C;                    // 46C
        u64                     unk_470;                    // 470
        maybe<Memory_Heap_i*>   default_heap;               // 478

    public:
        maybe<Byte_t*>  Allocate(size_t byte_count, u32 alignment = 0, Bool_t do_align = false);
        maybe<Byte_t*>  Reallocate(some<Byte_t*> data, size_t new_byte_count, u32 alignment = 0, Bool_t do_align = false);
        void            Deallocate(some<Byte_t*> data, Bool_t is_aligned = false);
    };
    STATIC_ASSERT(sizeof(Memory_t) == 0x480);

}

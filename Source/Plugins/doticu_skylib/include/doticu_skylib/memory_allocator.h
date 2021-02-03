/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "doticu_skylib/memory_info.h"

namespace doticu_skylib {

    class Memory_Allocator_i :  // IMemoryStore
        public Memory_Info_i    // 00
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E97FD0, // 690279
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual         ~Memory_Allocator_i();                                      // 0

        // Memory_Allocator_i
        virtual void*   Allocate_Block(size_t byte_count, u32 alignment)    = 0;    // 4
        virtual void    Deallocate_Block(void*& block)                      = 0;    // 5
        virtual void*   _6(size_t byte_count, u32 alignment)                = 0;    // 6 (Reallocate_Block?)
    };
    STATIC_ASSERT(sizeof(Memory_Allocator_i) == 0x8);

}

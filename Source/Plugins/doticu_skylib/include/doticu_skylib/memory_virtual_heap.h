/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe.h"

#include "doticu_skylib/memory_heap.h"

namespace doticu_skylib {

    class Memory_Heap_Block_t;

    class Memory_Virtual_Heap_t :   // AbstractHeap
        public Memory_Heap_i        // 00
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E98110, // 690286
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual         ~Memory_Virtual_Heap_t();                                               // 00

        // Memory_Virtual_Heap_t
        virtual void*   Allocate_Virtual_Block(size_t byte_count, size_t initial_size)  = 0;    // 0F
        virtual void    Deallocate_Virtual_Block(void* block)                           = 0;    // 10
        virtual size_t  _11(void*, size_t, size_t)                                      = 0;    // 11
        virtual size_t  _12(void*, size_t, size_t)                                      = 0;    // 12
        virtual void    _13(void);                                                              // 13
        virtual void    _14(void);                                                              // 14

    public:
        CRITICAL_SECTION    critical_section;           // 008
        maybe<const char*>  name;                       // 030
        size_t              smallest_free_block_size;   // 038
        u32                 page_size;                  // 040
        u32                 unk_044;                    // 044
        size_t              size;                       // 048
        size_t              initial_size;               // 050
        size_t              current_size;               // 058 (committed_size?)
        size_t              wasted_byte_count;          // 060
        size_t              allocated_size;             // 068
        size_t              unk_070;                    // 070
        size_t              allocated_in_blocks_size;   // 078
        maybe<Byte_t*>      data;                       // 080
        u32                 block_count;                // 088
        u32                 pad_08C;                    // 08C
        void*               block_head;                 // 090
        void*               block_tail;                 // 098
        u32                 free_block_count;           // 0A0
        Bool_t              allow_decommits;            // 0A4
        Bool_t              supports_swapping;          // 0A5
        u16                 pad_0A6;                    // 0A6
        void*               unk_0A8[32];                // 0A8
        void*               unk_1A8[32];                // 1A8

    public:
        template <typename Value_t>
        Vector_t<some<Value_t*>> Instances_Of(const Value_t& value)
        {
            Vector_t<some<Value_t*>> results;

            EnterCriticalSection(&this->critical_section);

            if (this->data) {
                Byte_t* bytes = this->data();
                size_t alignment = sizeof(Value_t) > sizeof(Word_t) ? sizeof(Word_t) : sizeof(Value_t);
                for (size_t idx = 0, end = this->current_size; idx < end; idx += alignment) {
                    if (end - idx >= sizeof(Value_t)) {
                        Value_t* value_ptr = reinterpret_cast<Value_t*>(bytes + idx);
                        if (*value_ptr == value) {
                            results.push_back(value_ptr);
                        }
                    } else {
                        break;
                    }
                }
            }

            LeaveCriticalSection(&this->critical_section);

            return results;
        }

        template <typename Value_t>
        Vector_t<some<Value_t*>> Instances_Of(Value_t&& value)
        {
            return Instances_Of(value);
        }

        void Log_Instances_In_Words(Vector_t<some<Word_t*>>& instances,
                                    size_t instance_word_count,
                                    Bool_t do_reverse = false,
                                    std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Memory_Virtual_Heap_t) == 0x2A8);

}

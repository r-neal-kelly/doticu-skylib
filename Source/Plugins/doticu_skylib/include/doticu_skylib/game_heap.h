/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Game_Heap_t
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
        static some<Game_Heap_t*> Self();

    public:
        maybe<Byte_t*>  Allocate(size_t byte_count, u32 alignment = 0, Bool_t do_align = false);
        maybe<Byte_t*>  Reallocate(some<Byte_t*> data, size_t new_byte_count, u32 alignment = 0, Bool_t do_align = false);
        void            Deallocate(some<Byte_t*> data, Bool_t is_aligned = false);
    };

}

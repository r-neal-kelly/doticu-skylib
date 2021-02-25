/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Scrap_Heap_t;

    class Scrap_Array_Allocator_t // BSScrapArrayAllocator
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RESIZE = 0x00920360, // 53105
            };
            using Enum_t::Enum_t;
        };

    protected:
        maybe<Scrap_Heap_t*>    scrap_heap; // 00
        void*                   entries;    // 08
        u32                     capacity;   // 10
        u32                     pad_14;     // 14

    public:
        Bool_t Resize(u32 count);
    };
    STATIC_ASSERT(sizeof(Scrap_Array_Allocator_t) == 0x18);

}

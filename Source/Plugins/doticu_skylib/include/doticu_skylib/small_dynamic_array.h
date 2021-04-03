/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    template <typename T, u32 MAX_LOCAL_COUNT = 1>
    class Small_Dynamic_Array_t // BSTSmallArray, SpellArray
    {
    public:
        using value_type = T;

    public:
        union Entries_u
        {
        public:
            maybe<T*>   heap;
            T           local[MAX_LOCAL_COUNT];

        public:
            Entries_u();
            ~Entries_u();
        };

    protected:
        u32         capacity        : 31;   // 00::00
        u32         has_local_data  : 1;    // 00::31
        u32         pad_04;                 // 04
        Entries_u   entries;                // 08
        u32         count;                  // 10
        u32         pad_14;                 // 14

    public:
        Bool_t      Is_Empty();
        maybe<T*>   Entries();
        u32         Count();

        maybe<T*>   Point(u32 index);
        T&          At(u32 index);

    public:
        T& operator [](u32 index);
    };
    STATIC_ASSERT(sizeof(Small_Dynamic_Array_t<void*>) == 0x18);

    template <typename T>
    using Small_Array_t = Small_Dynamic_Array_t<T>;

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    template <typename T>
    class Dynamic_Array_t // tArray, BSTArray
    {
    public:
        using value_type = T;

    protected:
        maybe<T*>   entries;    // 00
        u32         capacity;   // 08
        u32         pad_0C;     // 0C
        u32         count;      // 10
        u32         pad_14;     // 14

    public:
        Dynamic_Array_t(u32 reserve_count = 0);
        Dynamic_Array_t(const Dynamic_Array_t& other)                   = delete;
        Dynamic_Array_t(Dynamic_Array_t&& other) noexcept               = delete;
        Dynamic_Array_t& operator =(const Dynamic_Array_t& other)       = delete;
        Dynamic_Array_t& operator =(Dynamic_Array_t&& other) noexcept;
        ~Dynamic_Array_t();

    public:
        void        Reserve(u32 count);
        void        Grow(Float_t grow_rate = 1.7f);
        void        Shrink();

        Bool_t      Is_Empty();
        maybe<T*>   Entries();
        u32         Count() const;

        maybe<T*>   Point(u32 index);
        T&          At(u32 index) const;
        void        Push(T& value);
        void        Push(T&& value);
        void        Clear();

    public:
        T& operator [](u32 index) const;
    };
    STATIC_ASSERT(sizeof(Dynamic_Array_t<void*>) == 0x18);

    template <typename T>
    using Array_t = Dynamic_Array_t<T>;

}

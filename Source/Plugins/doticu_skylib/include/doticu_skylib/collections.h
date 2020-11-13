/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class XYZ_t
    {
        Float_t x; // 0
        Float_t y; // 4
        Float_t z; // 8
    };
    STATIC_ASSERT(sizeof(XYZ_t) == 0xC);

    class Short_XYZ_t
    {
    public:
        s16 x; // 0
        s16 y; // 2
        s16 z; // 4
    };
    STATIC_ASSERT(sizeof(Short_XYZ_t) == 0x6);

    template <typename Type>
    class Small_Array_t
    {
    public:
        virtual ~Small_Array_t();

        Type*   entries;    // 08
        u16     capacity;   // 10
        u16     free_index; // 12
        u16     count;      // 14
        u16     grow_rate;  // 16
    };
    STATIC_ASSERT(sizeof(Small_Array_t<void*>) == 0x18);

    template <typename Key_t>
    class Set_t
    {
    public:
        class Entry_t
        {
        public:
            Key_t key;
            Entry_t* chain; // if nullptr, key is not in the table
        };

        UInt64 pad_00; // 00
        UInt32 pad_08; // 08
        UInt32 capacity; // 0C
        UInt32 free_count; // 10
        UInt32 free_idx; // 14
        Entry_t* end_of_chain; // 18
        UInt64 pad_20; // 20
        Entry_t* entries; // 28
    };
    STATIC_ASSERT(sizeof(Set_t<void*>) == 0x30);

    template <typename Key_t, typename Value_t>
    class Hash_Map_t
    {
    public:
        class Tuple_t
        {
        public:
            Key_t key;
            Value_t value;
        };

        class Entry_t
        {
        public:
            Tuple_t tuple;
            Entry_t* chain; // if nullptr, key is not in the table
        };

        UInt64 pad_00; // 00
        UInt32 pad_08; // 08
        UInt32 capacity; // 0C
        UInt32 free_count; // 10
        UInt32 free_idx; // 14
        Entry_t* end_of_chain; // 18
        UInt64 pad_20; // 20
        Entry_t* entries; // 28

        Bool_t Has_Key(Key_t key)
        {
            if (entries) {
                UInt32 idx = Utils::CRC32(key) & (capacity - 1);
                Entry_t* entry = entries + idx;
                if (entry && entry->chain != nullptr) {
                    for (; entry != end_of_chain; entry = entry->chain) {
                        if (entry->tuple.key == key) {
                            return true;
                        }
                    }
                    return false;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }
    };
    STATIC_ASSERT(sizeof(Hash_Map_t<void*, void*>) == 0x30);

    template <typename Event>
    class Event_Sink_t
    {
        virtual ~Event_Sink_t();
    };
    STATIC_ASSERT(sizeof(Event_Sink_t<void*>) == 0x8);

}

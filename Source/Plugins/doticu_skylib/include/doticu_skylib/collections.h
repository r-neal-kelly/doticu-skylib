/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <vector>

#include "doticu_skylib/enum.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class s16_xy
    {
    public:
        s16 x; // 0
        s16 y; // 2
    };
    STATIC_ASSERT(sizeof(s16_xy) == 0x4);

    class s16_yx
    {
    public:
        s16 y; // 0
        s16 x; // 2
    };
    STATIC_ASSERT(sizeof(s16_yx) == 0x4);

    class s16_xyz
    {
    public:
        s16 x; // 0
        s16 y; // 2
        s16 z; // 4
    };
    STATIC_ASSERT(sizeof(s16_xyz) == 0x6);

    class f32_xy
    {
    public:
        Float_t x; // 0
        Float_t y; // 4
    };
    STATIC_ASSERT(sizeof(f32_xy) == 0x8);

    class f32_xyz
    {
    public:
        Float_t x; // 0
        Float_t y; // 4
        Float_t z; // 8
    };
    STATIC_ASSERT(sizeof(f32_xyz) == 0xC);

    template <typename Type_t, size_t static_capacity>
    class Stack_Array_t
    {
    public:
        const size_t    capacity                    = static_capacity;
        size_t          count                       = 0;
        Type_t          entries[static_capacity];

        void Push(Type_t& entry)
        {
            SKYLIB_ASSERT(count < capacity);
            entries[count] = entry;
            count += 1;
        }

        void Push(Type_t&& entry)
        {
            SKYLIB_ASSERT(count < capacity);
            entries[count] = std::move(entry);
            count += 1;
        }

        void Push(const Type_t&& entry)
        {
            SKYLIB_ASSERT(count < capacity);
            entries[count] = std::move(entry);
            count += 1;
        }

        Type_t&& Pop()
        {
            SKYLIB_ASSERT(count > 0);
            count -= 1;
            return std::move(entries[count]);
        }

        Type_t& operator[](size_t index)
        {
            SKYLIB_ASSERT(index < count);
            return entries[index];
        }

        Bool_t Has_Space()
        {
            return count < capacity;
        }
    };
    STATIC_ASSERT(sizeof(Stack_Array_t<Byte_t, 64>) == 0x50);

    template <typename Type_t>
    class Type_Array_t
    {
    public:
        Type_t  count; // 0
        Type_t  head;

        Type_t At(Index_t index)
        {
            SKYLIB_ASSERT(index > -1 && index < count);
            return *(&head + index);
        }
    };

    template <typename Type_t>
    class Static_Array_t
    {
    public:
        Type_t* entries;    // 0
        u32     count;      // 8
        u32     pad_0C;     // C
    };
    STATIC_ASSERT(sizeof(Static_Array_t<void*>) == 0x10);

    template <typename Type_t>
    class Small_Array_t
    {
    public:
        virtual ~Small_Array_t();

        Type_t* entries;    // 08
        u16     capacity;   // 10
        u16     free_index; // 12
        u16     count;      // 14
        u16     grow_rate;  // 16
    };
    STATIC_ASSERT(sizeof(Small_Array_t<void*>) == 0x18);

    template <typename Type_t>
    class Dynamic_Array_t
    {
    public:
        Type_t* entries;    // 00
        u32     capacity;   // 08
        u32     pad_0C;     // 0C
        u32     count;      // 10
        u32     pad_14;     // 14
    };
    STATIC_ASSERT(sizeof(Dynamic_Array_t<void*>) == 0x18);

    template <typename Type_t>
    using Array_t = Dynamic_Array_t<Type_t>;

    class Buffer_Allocator_t
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : Word_t
            {
                RESIZE = 0x00920360, // 53105
            };
            using Enum_t::Enum_t;
        };

    public:
        void* allocator;

        Bool_t Resize(u32 count);
    };

    template <typename Type_t>
    class Buffer_t : public Buffer_Allocator_t
    {
    public:
        Type_t* entries;    // 08
        u32     capacity;   // 10
        u32     pad_14;     // 14
        u32     count;      // 18
        u32     pad_1C;     // 1C

        Some_p<Type_t> At(u32 index)
        {
            SKYLIB_ASSERT(index < count);
            return entries + index;
        }
    };
    STATIC_ASSERT(sizeof(Buffer_t<int>) == 0x20);

    template <typename Type>
    class Vector_t : public std::vector<Type>
    {
    public:
        Index_t Index_Of(Type& item)
        {
            for (Index_t idx = 0, end = size(); idx < end; idx += 1) {
                if (at(idx) == item) {
                    return idx;
                }
            }
            return -1;
        }

        Bool_t Has(Type& item)
        {
            return Index_Of(item) > -1;
        }

        void Sort(Int_t(*comparator)(Type* item_a, Type* item_b))
        {
            qsort(data(), size(), sizeof(Type), reinterpret_cast<int(*)(const void*, const void*)>(comparator));
        }

        void Sort(Int_t(*comparator)(Type* item_a, Type* item_b), size_t begin)
        {
            size_t end = size();
            if (begin >= end) {
                begin = end - 1;
            }
            qsort(data() + begin, end - begin, sizeof(Type), reinterpret_cast<int(*)(const void*, const void*)>(comparator));
        }
    };

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

}

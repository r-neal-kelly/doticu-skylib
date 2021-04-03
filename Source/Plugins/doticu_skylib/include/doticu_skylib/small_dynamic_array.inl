/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/small_dynamic_array.h"

namespace doticu_skylib {

    template <typename T, u32 MAX_LOCAL_COUNT>
    inline Small_Dynamic_Array_t<T, MAX_LOCAL_COUNT>::Entries_u::Entries_u()
    {
    }

    template <typename T, u32 MAX_LOCAL_COUNT>
    inline Small_Dynamic_Array_t<T, MAX_LOCAL_COUNT>::Entries_u::~Entries_u()
    {
    }

    template <typename T, u32 MAX_LOCAL_COUNT>
    inline Bool_t Small_Dynamic_Array_t<T, MAX_LOCAL_COUNT>::Is_Empty()
    {
        if (this->has_local_data) {
            return this->count == 0;
        } else {
            return !this->entries.heap || this->count == 0;
        }
    }

    template <typename T, u32 MAX_LOCAL_COUNT>
    inline maybe<T*> Small_Dynamic_Array_t<T, MAX_LOCAL_COUNT>::Entries()
    {
        if (this->has_local_data) {
            return &this->entries.local[0];
        } else {
            return this->entries.heap;
        }
    }

    template <typename T, u32 MAX_LOCAL_COUNT>
    inline u32 Small_Dynamic_Array_t<T, MAX_LOCAL_COUNT>::Count()
    {
        if (!Is_Empty()) {
            return this->count;
        } else {
            return 0;
        }
    }

    template <typename T, u32 MAX_LOCAL_COUNT>
    inline maybe<T*> Small_Dynamic_Array_t<T, MAX_LOCAL_COUNT>::Point(u32 index)
    {
        if (index < this->count) {
            if (this->has_local_data) {
                return &this->entries.local + index;
            } else if (this->entries.heap) {
                return this->entries.heap + index;
            } else {
                return none<T*>();
            }
        } else {
            return none<T*>();
        }
    }

    template <typename T, u32 MAX_LOCAL_COUNT>
    inline T& Small_Dynamic_Array_t<T, MAX_LOCAL_COUNT>::At(u32 index)
    {
        SKYLIB_ASSERT(index < this->count);

        if (this->has_local_data) {
            return this->entries.local[index];
        } else {
            SKYLIB_ASSERT(this->entries.heap);
            return this->entries.heap[index];
        }
    }

    template <typename T, u32 MAX_LOCAL_COUNT>
    inline T& Small_Dynamic_Array_t<T, MAX_LOCAL_COUNT>::operator [](u32 index)
    {
        return At(index);
    }

}

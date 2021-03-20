/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/dynamic_array.h"
#include "doticu_skylib/game.inl"

namespace doticu_skylib {

    template <typename T>
    inline Dynamic_Array_t<T>::Dynamic_Array_t(u32 reserve_count) :
        entries(none<T*>()), capacity(0), pad_0C(0), count(0), pad_14(0)
    {
        Reserve(reserve_count);
    }

    template <typename T>
    inline Dynamic_Array_t<T>& Dynamic_Array_t<T>::operator =(Dynamic_Array_t&& other) noexcept
    {
        if (this != std::addressof(other)) {
            this->entries = std::exchange(other.entries, none<T*>());
            this->capacity = std::exchange(other.capacity, 0);
            this->pad_0C = std::exchange(other.pad_0C, 0);
            this->count = std::exchange(other.count, 0);
            this->pad_14 = std::exchange(other.pad_14, 0);
        }
        return *this;
    }

    template <typename T>
    inline Dynamic_Array_t<T>::~Dynamic_Array_t()
    {
        Clear();

        if (this->entries) {
            Game_t::Deallocate<T>(this->entries());
        }

        this->entries = none<T*>();
        this->capacity = 0;
        this->pad_0C = 0;
        this->count = 0;
        this->pad_14 = 0;
    }

    template <typename T>
    inline void Dynamic_Array_t<T>::Reserve(u32 count)
    {
        u32 new_capacity = sizeof(T) * count;
        if (this->capacity < new_capacity) {
            this->capacity = new_capacity;
            if (this->entries) {
                this->entries = Game_t::Reallocate<T>(this->entries(), count)();
            } else {
                this->entries = Game_t::Allocate<T>(count)();
            }
        }
    }

    template <typename T>
    inline void Dynamic_Array_t<T>::Grow(Float_t grow_rate)
    {
        SKYLIB_ASSERT(grow_rate >= 1.0f);

        Reserve(static_cast<u32>(this->capacity * grow_rate) + 1);
    }

    template <typename T>
    inline void Dynamic_Array_t<T>::Shrink()
    {
        if (this->entries && this->capacity > sizeof(T) * this->count) {
            this->entries = Game_t::Reallocate<T>(this->entries(), this->count)();
        }
    }

    template <typename T>
    inline Bool_t Dynamic_Array_t<T>::Is_Empty()
    {
        return !this->entries || this->count == 0;
    }

    template <typename T>
    inline maybe<T*> Dynamic_Array_t<T>::Entries()
    {
        return this->entries;
    }

    template <typename T>
    inline u32 Dynamic_Array_t<T>::Count() const
    {
        if (this->entries) {
            return this->count;
        } else {
            return 0;
        }
    }

    template <typename T>
    inline maybe<T*> Dynamic_Array_t<T>::Point(u32 index)
    {
        if (this->entries && index < this->count) {
            return this->entries + index;
        } else {
            return none<T*>();
        }
    }

    template <typename T>
    inline T& Dynamic_Array_t<T>::At(u32 index) const
    {
        SKYLIB_ASSERT(this->entries);
        SKYLIB_ASSERT(index < this->count);

        return this->entries[index];
    }

    template <typename T>
    inline void Dynamic_Array_t<T>::Push(T& value)
    {
        if (this->capacity < sizeof(T) * (this->count + 1)) {
            Grow();
        }

        this->entries[this->count] = value;
        this->count += 1;
    }

    template <typename T>
    inline void Dynamic_Array_t<T>::Push(T&& value)
    {
        if (this->capacity < sizeof(T) * (this->count + 1)) {
            Grow();
        }

        this->entries[this->count] = std::move(value);
        this->count += 1;
    }

    template <typename T>
    inline void Dynamic_Array_t<T>::Clear()
    {
        for (size_t idx = 0, end = Count(); idx < end; idx += 1) {
            this->entries[idx].~T();
        }
        count = 0;
    }

    template <typename T>
    inline T& Dynamic_Array_t<T>::operator [](u32 index) const
    {
        return At(index);
    }

}

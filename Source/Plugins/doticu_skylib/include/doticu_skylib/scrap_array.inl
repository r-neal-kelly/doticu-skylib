/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/scrap_array.h"

namespace doticu_skylib {

    template <typename T>
    inline maybe<T*> Scrap_Array_t<T>::Entries()
    {
        return static_cast<T*>(this->entries);
    }

    template <typename T>
    inline u32 Scrap_Array_t<T>::Count()
    {
        if (Entries()) {
            return this->count;
        } else {
            return 0;
        }
    }

    template <typename T>
    inline T& Scrap_Array_t<T>::At(u32 index)
    {
        SKYLIB_ASSERT(this->entries);
        SKYLIB_ASSERT(index < this->count);

        return Entries()[index];
    }

    template <typename T>
    inline T& Scrap_Array_t<T>::operator [] (u32 index)
    {
        return At(index);
    }

}

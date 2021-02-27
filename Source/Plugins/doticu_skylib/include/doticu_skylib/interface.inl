/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/interface.h"
#include "doticu_skylib/memory.h"

namespace doticu_skylib {

    template <typename ...Arguments>
    inline void* Callback_i<Arguments...>::operator new(size_t byte_count)
    {
        maybe<Byte_t*> data = Memory_t::Self()->Allocate(byte_count);
        SKYLIB_ASSERT(data);
        return data();
    }

    template <typename ...Arguments>
    inline void Callback_i<Arguments...>::operator delete(void* data)
    {
        SKYLIB_ASSERT(data);
        Memory_t::Self()->Deallocate(static_cast<Byte_t*>(data));
    }

}

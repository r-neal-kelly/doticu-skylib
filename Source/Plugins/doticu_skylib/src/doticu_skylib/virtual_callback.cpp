/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/memory.h"
#include "doticu_skylib/virtual_callback.h"

namespace doticu_skylib { namespace Virtual {

    void* Callback_i::operator new(size_t byte_count)
    {
        maybe<Byte_t*> data = Memory_t::Self()->Allocate(byte_count);
        SKYLIB_ASSERT(data);
        return data();
    }

    void Callback_i::operator delete(void* data)
    {
        SKYLIB_ASSERT(data);
        Memory_t::Self()->Deallocate(static_cast<Byte_t*>(data));
    }

}}

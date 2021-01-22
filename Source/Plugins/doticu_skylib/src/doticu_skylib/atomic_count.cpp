/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/atomic_count.h"

namespace doticu_skylib {

    u32 Atomic_Count_t::Count()
    {
        return InterlockedExchangeAdd(&this->atomic_count, 0);
    }

    u32 Atomic_Count_t::Increment()
    {
        return InterlockedIncrement(&this->atomic_count);
    }

    u32 Atomic_Count_t::Decrement()
    {
        return InterlockedDecrement(&this->atomic_count);
    }

}

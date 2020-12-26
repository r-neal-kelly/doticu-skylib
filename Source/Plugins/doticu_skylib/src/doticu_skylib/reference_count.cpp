/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/reference.h"
#include "doticu_skylib/reference_count.h"

namespace doticu_skylib {

    u32 Reference_Count_t::Reference_Count()
    {
        return _InterlockedExchangeAdd(&reference_count, 0) & 0x3FF;
    }

    u32 Reference_Count_t::Increment_Reference()
    {
        return _InterlockedIncrement(&reference_count) & 0x3FF;
    }

    u32 Reference_Count_t::Decrement_Reference()
    {
        u32 count = _InterlockedDecrement(&reference_count) & 0x3FF;
        if (count < 1) {
            Destroy();
        }
        return count;
    }

}

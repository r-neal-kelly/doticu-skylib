/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/dynatomic_count.h"

namespace doticu_skylib {

    u32 Dynatomic_Count_t::Dynatomic_Count()
    {
        return InterlockedExchangeAdd(&this->dynatomic_count, 0);
    }

    u32 Dynatomic_Count_t::Increment_Dynatomic()
    {
        return InterlockedIncrement(&this->dynatomic_count);
    }

    u32 Dynatomic_Count_t::Decrement_Dynatomic()
    {
        u32 count = InterlockedDecrement(&this->dynatomic_count);
        if (count < 1) {
            Destroy();
        }
        return count;
    }

}

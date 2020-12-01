/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/reference.h"
#include "doticu_skylib/reference_count.h"

namespace doticu_skylib {

    Int_t Reference_Count_t::Reference_Count()
    {
        return reference_count & 0x3FF;
    }

    Int_t Reference_Count_t::Increment_Reference()
    {
        return _InterlockedIncrement(static_cast<volatile u32*>(&reference_count)) & 0x3FF;
    }

    Int_t Reference_Count_t::Decrement_Reference()
    {
        Int_t count = _InterlockedDecrement(static_cast<volatile u32*>(&reference_count));
        if ((count & 0x3FF) == 0) {
            delete this;
        }
        return count;
    }

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/enum_reference_count_flags.h"

#include "doticu_skylib/reference.h"
#include "doticu_skylib/reference_count.h"

namespace doticu_skylib {

    u32 Reference_Count_t::Reference_Count()
    {
        return Dynatomic_Count_t::Dynatomic_Count() & Reference_Count_Flags_e::COUNT_MASK;
    }

    u32 Reference_Count_t::Increment_Reference()
    {
        return Dynatomic_Count_t::Increment_Dynatomic() & Reference_Count_Flags_e::COUNT_MASK;
    }

    u32 Reference_Count_t::Decrement_Reference()
    {
        u32 unmasked_count = Dynatomic_Count_t::Decrement_Dynatomic();
        u32 masked_count = unmasked_count & Reference_Count_Flags_e::COUNT_MASK;
        if (unmasked_count > 0 && masked_count < 1) {
            Destroy();
        }
        return masked_count;
    }

}

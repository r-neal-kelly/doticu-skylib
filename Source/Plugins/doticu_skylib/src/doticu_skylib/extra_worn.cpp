/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/extra_data.inl"
#include "doticu_skylib/extra_worn.h"

namespace doticu_skylib {

    some<Extra_Worn_t*> Extra_Worn_t::Create()
    {
        some<Extra_Worn_t*> x_worn = Extra_Data_t::Create<Extra_Worn_t>();

        return x_worn;
    }

    void Extra_Worn_t::Destroy(some<Extra_Worn_t*> x_worn)
    {
        SKYLIB_ASSERT_SOME(x_worn);

        Extra_Data_t::Destroy<Extra_Worn_t>(x_worn);
    }

}

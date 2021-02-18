/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/extra_data.inl"
#include "doticu_skylib/extra_worn_left.h"

namespace doticu_skylib {

    some<Extra_Worn_Left_t*> Extra_Worn_Left_t::Create()
    {
        some<Extra_Worn_Left_t*> x_worn_left = Extra_Data_t::Create<Extra_Worn_Left_t>();

        return x_worn_left;
    }

    void Extra_Worn_Left_t::Destroy(some<Extra_Worn_Left_t*> x_worn_left)
    {
        SKYLIB_ASSERT_SOME(x_worn_left);

        Extra_Data_t::Destroy<Extra_Worn_Left_t>(x_worn_left);
    }

}

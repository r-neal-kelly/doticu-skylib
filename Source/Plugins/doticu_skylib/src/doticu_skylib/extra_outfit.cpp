/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/extra_data.inl"
#include "doticu_skylib/extra_outfit.h"
#include "doticu_skylib/outfit.h"

namespace doticu_skylib {

    some<Extra_Outfit_t*> Extra_Outfit_t::Create(some<Outfit_t*> outfit)
    {
        SKYLIB_ASSERT_SOME(outfit);

        some<Extra_Outfit_t*> x_outfit = Extra_Data_t::Create<Extra_Outfit_t>();

        x_outfit->outfit_form_id = outfit->form_id;
        x_outfit->pad_14 = 0;

        return x_outfit;
    }

    void Extra_Outfit_t::Destroy(some<Extra_Outfit_t*> x_outfit)
    {
        SKYLIB_ASSERT_SOME(x_outfit);

        Extra_Data_t::Destroy<Extra_Outfit_t>(x_outfit);
    }

}

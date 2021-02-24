/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/extra_data.inl"
#include "doticu_skylib/extra_ghost.h"

namespace doticu_skylib {

    some<Extra_Ghost_t*> Extra_Ghost_t::Create(Bool_t is_ghost)
    {
        some<Extra_Ghost_t*> x_ghost = Extra_Data_t::Create<Extra_Ghost_t>();

        x_ghost->is_ghost = is_ghost;

        return x_ghost;
    }

    void Extra_Ghost_t::Destroy(some<Extra_Ghost_t*> x_ghost)
    {
        SKYLIB_ASSERT_SOME(x_ghost);

        Extra_Data_t::Destroy<Extra_Ghost_t>(x_ghost);
    }

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/extra_container_changes.h"

namespace doticu_skylib {

    some<Extra_Container_Changes_t*> Extra_Container_Changes_t::Create()
    {
        some<Extra_Container_Changes_t*> x_container_changes = Extra_Data_t::Create<Extra_Container_Changes_t>();
        x_container_changes->container_changes = none<Container_Changes_t*>();
        return x_container_changes;
    }

    void Extra_Container_Changes_t::Destroy(some<Extra_Container_Changes_t*> x_container_changes)
    {
        SKYLIB_ASSERT_SOME(x_container_changes);

        Extra_Data_t::Destroy<Extra_Container_Changes_t>(x_container_changes);
    }

}

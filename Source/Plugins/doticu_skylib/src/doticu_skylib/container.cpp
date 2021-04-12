/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/container.h"
#include "doticu_skylib/reference.h"

namespace doticu_skylib {

    some<Reference_t*> Container_t::Create_Reference(some<Container_t*> container, maybe<Reference_t*> at)
    {
        SKYLIB_ASSERT_SOME(container);

        maybe<Reference_t*> reference = Reference_t::Create(container, 1, at, true, false, true);
        SKYLIB_ASSERT_SOME(reference);

        return reference();
    }

}

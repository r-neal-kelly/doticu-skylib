/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/component_container.h"
#include "doticu_skylib/container_entry.h"

namespace doticu_skylib {

    maybe<Container_Entry_t*> Container_c::Maybe_Entry(some<Bound_Object_t*> object)
    {
        SKYLIB_ASSERT_SOME(object);

        if (this->container_entries) {
            for (size_t idx = 0, end = this->container_entry_count; idx < end; idx += 1) {
                maybe<Container_Entry_t*> maybe_entry = this->container_entries[idx];
                if (maybe_entry && maybe_entry->object() == object()) {
                    return maybe_entry;
                }
            }
            return none<Container_Entry_t*>();
        } else {
            return none<Container_Entry_t*>();
        }
    }

    Container_Entry_Count_t Container_c::Entry_Count(some<Bound_Object_t*> object)
    {
        SKYLIB_ASSERT_SOME(object);

        maybe<Container_Entry_t*> maybe_entry = Maybe_Entry(object);
        if (maybe_entry) {
            return maybe_entry->count;
        } else {
            return 0;
        }
    }

}

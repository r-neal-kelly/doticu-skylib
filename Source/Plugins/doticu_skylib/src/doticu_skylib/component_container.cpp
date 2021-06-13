/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/component_container.h"
#include "doticu_skylib/container_entry.h"

namespace doticu_skylib {

    maybe<Container_Entry_t*> Container_c::Maybe_Entry(some<Bound_Object_t*> bound_object)
    {
        SKYLIB_ASSERT_SOME(bound_object);

        if (this->container_entries) {
            for (size_t idx = 0, end = this->container_entry_count; idx < end; idx += 1) {
                maybe<Container_Entry_t*> maybe_entry = this->container_entries[idx];
                if (maybe_entry && maybe_entry->bound_object() == bound_object()) {
                    return maybe_entry;
                }
            }
            return none<Container_Entry_t*>();
        } else {
            return none<Container_Entry_t*>();
        }
    }

    sp32 Container_c::Entry_Count(some<Bound_Object_t*> bound_object)
    {
        SKYLIB_ASSERT_SOME(bound_object);

        maybe<Container_Entry_t*> maybe_entry = Maybe_Entry(bound_object);
        if (maybe_entry) {
            return maybe_entry->Count();
        } else {
            return 0;
        }
    }

    void Container_c::Container_Add_Items_To(some<Reference_t*> reference)
    {
        SKYLIB_ASSERT_SOME(reference);

        if (this->container_entries) {
            for (size_t idx = 0, end = this->container_entry_count; idx < end; idx += 1) {
                maybe<Container_Entry_t*> container_entry = this->container_entries[idx];
                if (container_entry) {
                    container_entry->Add_Item_To(reference);
                }
            }
        }
    }

}

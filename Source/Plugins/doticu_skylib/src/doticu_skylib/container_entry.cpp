/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/container_entry.h"
#include "doticu_skylib/reference.h"

namespace doticu_skylib {

    sp32 Container_Entry_t::Count()
    {
        return this->count;
    }

    void Container_Entry_t::Count(sp32 count)
    {
        this->count = count;
    }

    void Container_Entry_t::Add_Item_To(some<Reference_t*> reference)
    {
        SKYLIB_ASSERT_SOME(reference);

        if (this->bound_object && this->count > 0) {
            reference->Add_Item(bound_object(), none<Extra_List_t*>(), this->count, none<Reference_t*>());
        }
    }

}

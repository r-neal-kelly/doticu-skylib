/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/outfit.h"
#include "doticu_skylib/reference.h"

namespace doticu_skylib {

    void Outfit_t::Add_Items_To(some<Reference_t*> reference)
    {
        SKYLIB_ASSERT_SOME(reference);

        for (size_t idx = 0, end = this->entries.Count(); idx < end; idx += 1) {
            maybe<Bound_Object_t*> bound_object = this->entries[idx];
            if (bound_object) {
                reference->Add_Item(bound_object(), none<Extra_List_t*>(), 1, none<Reference_t*>());
            }
        }
    }

}

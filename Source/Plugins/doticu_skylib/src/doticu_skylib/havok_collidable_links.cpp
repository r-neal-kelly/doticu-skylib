/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/havok_collidable_links.h"

namespace doticu_skylib {

    Bool_t Havok_Collidable_Links_t::Has(some<Havok_Collidable_Links_t*> collidable_links)
    {
        SKYLIB_ASSERT_SOME(collidable_links);

        if (this->entries) {
            for (size_t idx = 0, end = this->count; idx < end; idx += 1) {
                Havok_Collidable_Link_t& collidable_link = this->entries[idx];
                if (collidable_link.collidable_links == collidable_links) {
                    return true;
                }
            }
            return false;
        } else {
            return false;
        }
    }

}

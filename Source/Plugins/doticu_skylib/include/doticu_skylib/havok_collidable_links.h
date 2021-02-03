/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/havok_array.h"
#include "doticu_skylib/havok_collidable.h"
#include "doticu_skylib/havok_collidable_link.h"

namespace doticu_skylib {

    class Havok_Collidable_Links_t :                    // hkpLinkedCollidable
        public Havok_Collidable_t,                      // 00
        public Havok_Array_t<Havok_Collidable_Link_t>   // 70
    {
    public:
        Bool_t Has(some<Havok_Collidable_Links_t*> collidable_links);
    };
    STATIC_ASSERT(sizeof(Havok_Collidable_Links_t) == 0x80);

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/havok_array.h"
#include "doticu_skylib/havok_collidable.h"

namespace doticu_skylib {

    class Havok_Collidable_Links_t;

    class Havok_Collidable_Link_t // hkpLinkedCollidable::CollisionEntry
    {
    public:
        void*                               unk_0;              // 0
        maybe<Havok_Collidable_Links_t*>    collidable_links;   // 8
    };
    STATIC_ASSERT(sizeof(Havok_Collidable_Link_t) == 0x10);

}

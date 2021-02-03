/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"

#include "doticu_skylib/havok_collidable.h"
#include "doticu_skylib/havok_quad.h"

namespace doticu_skylib {

    class Havok_Collision_t // hkpRootCdPoint
    {
    public:
        Havok_Quad_t                contact_position;   // 00
        Havok_Quad_t                unk_10;             // 10
        maybe<Havok_Collidable_t*>  collidable_a;       // 20
        u32                         shape_a_key;        // 28
        u32                         pad_2C;             // 2C
        maybe<Havok_Collidable_t*>  collidable_b;       // 30
        u32                         shape_b_key;        // 38
        u32                         pad_3C;             // 3C
    };
    STATIC_ASSERT(sizeof(Havok_Collision_t) == 0x40);

}

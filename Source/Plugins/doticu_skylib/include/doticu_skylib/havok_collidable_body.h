/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Havok_Collidable_Body_t // hkpCdBody
    {
    public:
        void*                       shape;                  // 00
        u32                         shape_key;              // 08
        u32                         pad_0C;                 // 0C
        void*                       motion;                 // 10
        Havok_Collidable_Body_t*    parent_collidable_base; // 18
    };
    STATIC_ASSERT(sizeof(Havok_Collidable_Body_t) == 0x20);

}

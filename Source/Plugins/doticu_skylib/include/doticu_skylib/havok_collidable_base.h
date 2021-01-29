/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_havok_collidable_base_flags.h"

#include "doticu_skylib/ni_collidable.h"

namespace doticu_skylib {

    class Havok_Body_t;
    class Havok_Body_Base_t;

    class Havok_Collidable_Base_t : // bhkNiCollisionObject
        public NI_Collidable_t      // 00
    {
    public:
        virtual ~Havok_Collidable_Base_t(); // 00

    public:
        Havok_Collidable_Base_Flags_e   collidable_base_flags;  // 18
        u32                             pad_1C;                 // 1C
        maybe<Havok_Body_Base_t*>       body_base;              // 20

    public:
        maybe<Havok_Body_t*> Body();
    };
    STATIC_ASSERT(sizeof(Havok_Collidable_Base_t) == 0x28);

}

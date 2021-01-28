/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/havok_linked_collidable.h"
#include "doticu_skylib/havok_referenced_object.h"

namespace doticu_skylib {

    class Havok_Bound_Object_t :            // hkpWorldObject
        public Havok_Referenced_Object_t
    {
    public:
        virtual ~Havok_Bound_Object_t(); // 0

    public:
        void*                       world;              // 10
        u64                         unk_18;             // 18
        Havok_Linked_Collidable_t   linked_collidable;  // 20
        Byte_t                      data_A0[0x30];      // A0
    };
    STATIC_ASSERT(sizeof(Havok_Bound_Object_t) == 0xD0);

}

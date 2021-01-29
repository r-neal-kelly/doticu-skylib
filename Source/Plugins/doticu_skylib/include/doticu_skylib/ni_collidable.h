/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"

#include "doticu_skylib/enum_collision_layer_type.h"

#include "doticu_skylib/ni_object.h"

namespace doticu_skylib {

    class NI_3D_t;

    class NI_Collidable_t : // NiCollisionObject
        public NI_Object_t  // 00
    {
    public:
        virtual ~NI_Collidable_t(); // 00

    public:
        maybe<NI_3D_t*> ni_3d; // 10

    public:
        Collision_Layer_Type_e  Collision_Layer_Type();
        void                    Collision_Layer_Type(Collision_Layer_Type_e collision_layer_type);
    };
    STATIC_ASSERT(sizeof(NI_Collidable_t) == 0x18);

}

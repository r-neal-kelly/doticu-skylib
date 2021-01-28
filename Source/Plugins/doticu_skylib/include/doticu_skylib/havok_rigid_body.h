/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/havok_entity.h"

namespace doticu_skylib {

    class Havok_Rigid_Body_t :  // hkpRigidBody
        public Havok_Entity_t   // 000
    {
    public:
        virtual ~Havok_Rigid_Body_t(); // 0
    };
    STATIC_ASSERT(sizeof(Havok_Rigid_Body_t) == 0x2D0);

}

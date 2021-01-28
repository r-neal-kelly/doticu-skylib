/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/havok_bound_object.h"

namespace doticu_skylib {

    class Havok_Entity_t :          // hkpEntity
        public Havok_Bound_Object_t // 000
    {
    public:
        virtual ~Havok_Entity_t(); // 0

    public:
        Byte_t data_0D0[0x200]; // D0
    };
    STATIC_ASSERT(sizeof(Havok_Entity_t) == 0x2D0);

}

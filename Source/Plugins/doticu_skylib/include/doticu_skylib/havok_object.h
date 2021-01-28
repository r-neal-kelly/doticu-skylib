/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Havok_Object_t // hkBaseObject
    {
    public:
        virtual ~Havok_Object_t(); // 0
    };
    STATIC_ASSERT(sizeof(Havok_Object_t) == 0x8);

}

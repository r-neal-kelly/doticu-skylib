/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/bound_object.h"

namespace doticu_skylib {

    class Animated_Object_t :   // TESBoundAnimObject
        public Bound_Object_t   // 00
    {
    public:
        virtual ~Animated_Object_t();
    };
    STATIC_ASSERT(sizeof(Animated_Object_t) == 0x30);

}

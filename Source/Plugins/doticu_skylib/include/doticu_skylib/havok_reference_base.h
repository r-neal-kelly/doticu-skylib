/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"

#include "doticu_skylib/ni_object.h"

namespace doticu_skylib {

    class Havok_Reference_t;

    class Havok_Reference_Base_t :  // bhkRefObject
        public NI_Object_t          // 00
    {
    public:
        virtual ~Havok_Reference_Base_t(); // 00

    public:
        maybe<Havok_Reference_t*> reference; // 10
    };
    STATIC_ASSERT(sizeof(Havok_Reference_Base_t) == 0x18);

}

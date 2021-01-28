/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/havok_object.h"

namespace doticu_skylib {

    class Havok_Referenced_Object_t : // hkReferencedObject
        public Havok_Object_t
    {
    public:
        virtual ~Havok_Referenced_Object_t(); // 0

    public:
        u16             unk_08;             // 08
        volatile s16    reference_count;    // 0A
        u32             pad_0C;             // 0C
    };
    STATIC_ASSERT(sizeof(Havok_Referenced_Object_t) == 0x10);

}

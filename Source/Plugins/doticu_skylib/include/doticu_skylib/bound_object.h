/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"

#include "doticu_skylib/object.h"

namespace doticu_skylib {

    class Bound_Object_t : public Object_t
    {
    public:
        virtual ~Bound_Object_t();

        s16_xyz bound_min;  // 20
        s16_xyz bound_max;  // 26
        u32     pad_2C;     // 2C
    };
    STATIC_ASSERT(sizeof(Bound_Object_t) == 0x30);

}
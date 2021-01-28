/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/dynatomic_count.h"

namespace doticu_skylib {

    class NI_Object_t :             // NiObject
        public Dynatomic_Count_t    // 00
    {
    public:
        virtual ~NI_Object_t(); // 00
    };
    STATIC_ASSERT(sizeof(NI_Object_t) == 0x10);

}

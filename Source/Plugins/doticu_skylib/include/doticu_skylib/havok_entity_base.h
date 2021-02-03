/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/havok_body_base.h"

namespace doticu_skylib {

    class Havok_Entity_Base_t :     // bhkEntity
        public Havok_Body_Base_t    // 00
    {
    public:
        virtual ~Havok_Entity_Base_t(); // 00
    };
    STATIC_ASSERT(sizeof(Havok_Entity_Base_t) == 0x28);

}

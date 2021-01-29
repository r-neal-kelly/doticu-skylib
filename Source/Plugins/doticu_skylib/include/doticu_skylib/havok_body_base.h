/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/havok_saveable_base.h"

namespace doticu_skylib {

    class Havok_World_t;

    class Havok_Body_Base_t :           // bhkWorldObject
        public Havok_Saveable_Base_t    // 00
    {
    public:
        virtual ~Havok_Body_Base_t(); // 00

    public:
        maybe<Havok_World_t*> world; // 20
    };
    STATIC_ASSERT(sizeof(Havok_Body_Base_t) == 0x28);

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Havok_Entity_Listener_t // hkpEntityListener
    {
    public:
        virtual ~Havok_Entity_Listener_t(); // 0
    };
    STATIC_ASSERT(sizeof(Havok_Entity_Listener_t) == 0x8);

}

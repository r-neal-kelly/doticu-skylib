/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Actor_Values_Data_t // ActorValueStorage
    {
    public:
        Byte_t data[0x20]; // 00
    };
    STATIC_ASSERT(sizeof(Actor_Values_Data_t) == 0x20);

}

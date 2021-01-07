/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/actor.h"

namespace doticu_skylib {

    class Character_t : public Actor_t
    {
    public:
        virtual ~Character_t(); // 0
    };
    STATIC_ASSERT(sizeof(Character_t) == 0x2B0);

}

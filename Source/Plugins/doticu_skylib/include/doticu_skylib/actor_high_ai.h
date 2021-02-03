/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Actor_High_AI_t // HighProcessData
    {
    public:
        Byte_t data[0x478]; // 000
    };
    STATIC_ASSERT(sizeof(Actor_High_AI_t) == 0x478);

}

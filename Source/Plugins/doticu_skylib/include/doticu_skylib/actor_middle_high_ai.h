/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Havok_Actor_Controller_t;

    class Actor_Middle_High_AI_t // MiddleProcess, MiddleHighProcessData
    {
    public:
        Byte_t                              data_000[0x250];        // 000
        maybe<Havok_Actor_Controller_t*>    havok_actor_controller; // 250
        Byte_t                              data_258[0xE0];         // 258
    };
    STATIC_ASSERT(sizeof(Actor_Middle_High_AI_t) == 0x338);

}

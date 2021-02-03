/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Actor_Middle_Low_AI_t;
    class Actor_Middle_High_AI_t;
    class Actor_High_AI_t;

    class Actor_AI_t // ActorProcessManager, AIProcess
    {
    public:
        maybe<Actor_Middle_Low_AI_t*>   middle_low_ai;  // 000
        maybe<Actor_Middle_High_AI_t*>  middle_high_ai; // 008
        maybe<Actor_High_AI_t*>         high_ai;        // 010
        Byte_t                          data[0x128];    // 018
    };
    STATIC_ASSERT(sizeof(Actor_AI_t) == 0x140);

}

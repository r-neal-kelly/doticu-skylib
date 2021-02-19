/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/movement_ai_controller.h"

namespace doticu_skylib {

    class Movement_Actor_Controller_t : // MovementControllerNPC
        public Movement_AI_Controller_t // 000
        // ...
    {
    public:
    };
    STATIC_ASSERT(sizeof(Movement_AI_Controller_t) == 0x120);

}

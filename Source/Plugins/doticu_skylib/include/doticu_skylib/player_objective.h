/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"
#include "doticu_skylib/quest_objective_state.h"

namespace doticu_skylib {

    class Quest_Objective_t;

    class Player_Objective_t
    {
    public:
        maybe<Quest_Objective_t*>   objective;      // 0
        u32                         instance_id;    // 8
        Quest_Objective_State_e     state;          // C
        u8                          pad_D;          // D
        u16                         pad_E;          // E

    public:
        void    Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Player_Objective_t) == 0x10);

}

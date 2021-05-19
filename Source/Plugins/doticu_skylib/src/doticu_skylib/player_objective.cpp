/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/player_objective.h"
#include "doticu_skylib/quest_objective.h"

namespace doticu_skylib {

    void Player_Objective_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Player_Objective_t::Log");
        SKYLIB_LOG(indent + "{");

        if (this->objective) {
            this->objective->Log(indent + SKYLIB_TAB);
        }
        SKYLIB_LOG(indent + SKYLIB_TAB + "instance_id: %u", instance_id);
        SKYLIB_LOG(indent + SKYLIB_TAB + "state: %s", Quest_Objective_State_e::To_String(state));

        SKYLIB_LOG(indent + "}");
    }

}

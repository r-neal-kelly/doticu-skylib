/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/maybe.h"

#include "doticu_skylib/game.h"
#include "doticu_skylib/mod.h"
#include "doticu_skylib/player.h"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/quest_objective.h"

namespace doticu_skylib {

    void Player_Objective_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Player_Objective_t::Log");
        SKYLIB_LOG(indent + "{");

        if (objective) {
            objective->Log(indent + SKYLIB_TAB);
        }
        SKYLIB_LOG(indent + SKYLIB_TAB + "instance_id: 0x%X", instance_id);
        SKYLIB_LOG(indent + SKYLIB_TAB + "state: %s", Quest_Objective_State_e::To_String(state));

        SKYLIB_LOG(indent + "}");
    }

    some<Player_t*> Player_t::Self()
    {
        static maybe<Player_t*> self = static_cast<maybe<Player_t*>>
            (Game_t::Form(Mod_t::Skyrim(), 0x000014));

        SKYLIB_ASSERT(self);
        return self();
    }

    void Player_t::Log_Objectives(std::string indent)
    {
        SKYLIB_LOG(indent + "Player_t::Log_Objectives");
        SKYLIB_LOG(indent + "{");

        for (Index_t idx = 0, end = objectives.count; idx < end; idx += 1) {
            Player_Objective_t& player_objective = objectives.entries[idx];
            SKYLIB_LOG(indent + SKYLIB_TAB + "index: %i", idx);
            player_objective.Log(indent + SKYLIB_TAB SKYLIB_TAB);
        }

        SKYLIB_LOG(indent + "}");
    }

}

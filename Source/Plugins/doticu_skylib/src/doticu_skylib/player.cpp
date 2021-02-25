/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/maybe.h"

#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/game.inl"
#include "doticu_skylib/havok_actor_controller.h"
#include "doticu_skylib/havok_player.h"
#include "doticu_skylib/havok_player_controller.h"
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

    maybe<Havok_Player_t*> Player_t::Havok_Player()
    {
        maybe<Havok_Player_Controller_t*> player_controller = Havok_Player_Controller();
        if (player_controller) {
            return player_controller->player_base.Player();
        } else {
            return none<Havok_Player_t*>();
        }
    }

    maybe<Havok_Player_Controller_t*> Player_t::Havok_Player_Controller()
    {
        maybe<Havok_Actor_Controller_t*> actor_controller = Havok_Actor_Controller();
        if (actor_controller) {
            return Game_t::Runtime_Cast<Havok_Actor_Controller_t, Havok_Player_Controller_t>(actor_controller());
        } else {
            return none<Havok_Player_Controller_t*>();
        }
    }

    u32 Player_t::Teammate_Count()
    {
        return teammate_count.Atomic_Count();
    }

    u32 Player_t::Increment_Teammate_Count()
    {
        return teammate_count.Increment_Atomic();
    }

    u32 Player_t::Decrement_Teammate_Count()
    {
        return teammate_count.Decrement_Atomic();
    }

    void Player_t::Log_Objectives(std::string indent)
    {
        SKYLIB_LOG(indent + "Player_t::Log_Objectives");
        SKYLIB_LOG(indent + "{");

        for (Index_t idx = 0, end = objectives.Count(); idx < end; idx += 1) {
            Player_Objective_t& player_objective = objectives[idx];
            SKYLIB_LOG(indent + SKYLIB_TAB + "index: %i", idx);
            player_objective.Log(indent + SKYLIB_TAB SKYLIB_TAB);
        }

        SKYLIB_LOG(indent + "}");
    }

}

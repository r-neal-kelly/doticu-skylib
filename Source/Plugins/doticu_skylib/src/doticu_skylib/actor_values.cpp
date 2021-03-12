/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/actor_values.h"

namespace doticu_skylib {

    void Actor_Values_t::Log_Actor_Value(Actor_Value_Type_e actor_value_type, std::string indent)
    {
        SKYLIB_LOG(indent + "Actor_Values_t::Log_Actor_Value: %s", Actor_Value_Type_e::To_String(actor_value_type));
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "current: %16.8f", Get_Current_Actor_Value(actor_value_type));
        SKYLIB_LOG(indent + SKYLIB_TAB + "current_maximum: %16.8f", Get_Current_Maximum_Actor_Value(actor_value_type));
        SKYLIB_LOG(indent + SKYLIB_TAB + "base: %16.8f", Get_Base_Actor_Value(actor_value_type));
        SKYLIB_LOG(indent + SKYLIB_TAB + "is_player_values: %s", Get_Is_Player_Values() ? "true" : "false");

        SKYLIB_LOG(indent + "}");
    }

}

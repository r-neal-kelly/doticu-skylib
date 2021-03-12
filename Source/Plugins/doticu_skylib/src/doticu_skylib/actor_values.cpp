/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/actor_values.h"
#include "doticu_skylib/math.h"

namespace doticu_skylib {

    void Actor_Values_t::Damage_Actor_Value(Actor_Value_Type_e actor_value_type, Float_t amount)
    {
        Do_Mod_Current_Actor_Value(Actor_Value_Modifier_e::DAMAGE, actor_value_type, -abs(amount));
    }

    void Actor_Values_t::Restore_Actor_Value(Actor_Value_Type_e actor_value_type, Float_t amount)
    {
        Do_Mod_Current_Actor_Value(Actor_Value_Modifier_e::DAMAGE, actor_value_type, abs(amount));
    }

    void Actor_Values_t::Log_Actor_Value(Actor_Value_Type_e actor_value_type, std::string indent)
    {
        SKYLIB_LOG(indent + "Actor_Values_t::Log_Actor_Value: %s", Actor_Value_Type_e::To_String(actor_value_type));
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "current: %16.8f", Get_Current_Actor_Value(actor_value_type));
        SKYLIB_LOG(indent + SKYLIB_TAB + "maximum: %16.8f", Get_Maximum_Actor_Value(actor_value_type));
        SKYLIB_LOG(indent + SKYLIB_TAB + "default: %16.8f", Get_Default_Actor_Value(actor_value_type));

        SKYLIB_LOG(indent + "}");
    }

}

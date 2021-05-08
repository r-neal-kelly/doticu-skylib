/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/actor_state.h"

namespace doticu_skylib {

    Attack_State_e Actor_State_t::Attack_State()
    {
        return this->bits_a.attack_state;
    }

    Fly_State_e Actor_State_t::Fly_State()
    {
        return this->bits_a.fly_state;
    }

    Knock_State_e Actor_State_t::Knock_State()
    {
        return this->bits_a.knock_state;
    }

    Life_State_e Actor_State_t::Life_State()
    {
        return this->bits_a.life_state;
    }

    Sit_Sleep_State_e Actor_State_t::Sit_Sleep_State()
    {
        return this->bits_a.sit_sleep_state;
    }

    Weapon_State_e Actor_State_t::Weapon_State()
    {
        return this->bits_b.weapon_state;
    }

    Bool_t Actor_State_t::Is_Moving()
    {
        return
            this->bits_a.is_moving_forward ||
            this->bits_a.is_moving_left ||
            this->bits_a.is_moving_right ||
            this->bits_a.is_moving_back;
    }

    Bool_t Actor_State_t::Is_Sneaking()
    {
        return this->bits_a.is_sneaking;
    }

    Bool_t Actor_State_t::Is_Forced_To_Sneak()
    {
        return this->bits_b.is_forced_to_sneak;
    }

    Bool_t Actor_State_t::Has_Weapon_Drawn()
    {
        Weapon_State_e weapon_state = Weapon_State();
        return
            weapon_state == Weapon_State_e::DRAWN ||
            weapon_state == Weapon_State_e::DRAWING;
    }

    Bool_t Actor_State_t::Has_Weapon_Sheathed()
    {
        Weapon_State_e weapon_state = Weapon_State();
        return
            weapon_state == Weapon_State_e::SHEATHED ||
            weapon_state == Weapon_State_e::SHEATHING;
    }

}

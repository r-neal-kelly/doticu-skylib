/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.inl"
#include "doticu_skylib/havok_player.h"
#include "doticu_skylib/havok_player_base.h"
#include "doticu_skylib/havok_player_ex.h"

namespace doticu_skylib {

    maybe<Havok_Player_t*> Havok_Player_Base_t::Player()
    {
        if (this->reference) {
            return Game_t::Runtime_Cast<Havok_Reference_t, Havok_Player_t>(reference());
        } else {
            return none<Havok_Player_t*>();
        }
    }

    maybe<Havok_Player_Ex_t*> Havok_Player_Base_t::Player_Ex()
    {
        if (this->reference) {
            return Game_t::Runtime_Cast<Havok_Reference_t, Havok_Player_Ex_t>(reference());
        } else {
            return none<Havok_Player_Ex_t*>();
        }
    }

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.inl"
#include "doticu_skylib/havok_rigid_body.h"
#include "doticu_skylib/havok_rigid_body_base.h"

namespace doticu_skylib {

    maybe<Havok_Rigid_Body_t*> Havok_Rigid_Body_Base_t::Rigid_Body()
    {
        if (this->reference) {
            return Game_t::Runtime_Cast<Havok_Reference_t, Havok_Rigid_Body_t>(this->reference());
        } else {
            return nullptr;
        }
    }

}

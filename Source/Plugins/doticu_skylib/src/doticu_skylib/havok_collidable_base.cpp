/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.inl"
#include "doticu_skylib/havok_body.h"
#include "doticu_skylib/havok_body_base.h"
#include "doticu_skylib/havok_collidable_base.h"

namespace doticu_skylib {

    maybe<Havok_Body_t*> Havok_Collidable_Base_t::Body()
    {
        if (this->body_base) {
            maybe<Havok_Reference_t*> reference = this->body_base->reference;
            if (reference) {
                return Game_t::Runtime_Cast<Havok_Reference_t, Havok_Body_t>(reference());
            } else {
                return none<Havok_Body_t*>();
            }
        } else {
            return none<Havok_Body_t*>();
        }
    }

}

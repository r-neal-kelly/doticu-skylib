/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.inl"
#include "doticu_skylib/ni_collidable.h"

#include "doticu_skylib/havok_body.h"
#include "doticu_skylib/havok_body_base.h"
#include "doticu_skylib/havok_collidable_base.h"

namespace doticu_skylib {

    Collision_Layer_Type_e NI_Collidable_t::Collision_Layer_Type()
    {
        maybe<Havok_Collidable_Base_t*> havok_collidable_base = As_Havok_Collidable_Base();
        if (havok_collidable_base) {
            maybe<Havok_Body_t*> havok_body = havok_collidable_base->Body();
            if (havok_body) {
                return havok_body->Collision_Layer_Type();
            } else {
                return Collision_Layer_Type_e::_NONE_;
            }
        } else {
            return Collision_Layer_Type_e::_NONE_;
        }
    }

    void NI_Collidable_t::Collision_Layer_Type(Collision_Layer_Type_e collision_layer_type)
    {
        maybe<Havok_Collidable_Base_t*> havok_collidable_base = As_Havok_Collidable_Base();
        if (havok_collidable_base) {
            maybe<Havok_Body_t*> havok_body = havok_collidable_base->Body();
            if (havok_body) {
                havok_body->Collision_Layer_Type(collision_layer_type);
            }
        }
    }

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.inl"

#include "doticu_skylib/extra_collision_layer.h"
#include "doticu_skylib/extra_data.inl"

namespace doticu_skylib {

    some<Collision_Layer_x*> Collision_Layer_x::Create()
    {
        return Data_x::Create<Collision_Layer_x>();
    }

    void Collision_Layer_x::Destroy(some<Collision_Layer_x*> collision_layer_x)
    {
        SKYLIB_ASSERT_SOME(collision_layer_x);
        Data_x::Destroy<Collision_Layer_x>(collision_layer_x);
    }

    Collision_Layer_Type_e Collision_Layer_x::Collision_Layer_Type()
    {
        if (this->collision_layer_type) {
            return *this->collision_layer_type;
        } else {
            return Collision_Layer_Type_e::_NONE_;
        }
    }

    void Collision_Layer_x::Collision_Layer_Type(Collision_Layer_Type_e collision_layer_type)
    {
        if (!this->collision_layer_type) {
            this->collision_layer_type = Game_t::Allocate<Collision_Layer_Type_e>()();
        }
        *this->collision_layer_type = collision_layer_type;
    }

    void Collision_Layer_x::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Collision_Layer_x::Log");
        SKYLIB_LOG(indent + "{");

        if (collision_layer_type) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "collision_layer_type: %d", *collision_layer_type);
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "collision_layer_type: (nullptr)");
        }

        SKYLIB_LOG(indent + "}");
    }

}

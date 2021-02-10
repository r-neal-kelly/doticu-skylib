/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.inl"

#include "doticu_skylib/extra_collision_layer.h"
#include "doticu_skylib/extra_data.inl"

namespace doticu_skylib {

    some<Extra_Collision_Layer_t*> Extra_Collision_Layer_t::Create()
    {
        some<Extra_Collision_Layer_t*> x_collision_layer = Extra_Data_t::Create<Extra_Collision_Layer_t>();

        x_collision_layer->collision_layer_type = none<Collision_Layer_Type_e*>();

        return x_collision_layer;
    }

    some<Extra_Collision_Layer_t*> Extra_Collision_Layer_t::Create(Collision_Layer_Type_e collision_layer_type)
    {
        some<Extra_Collision_Layer_t*> x_collision_layer = Extra_Data_t::Create<Extra_Collision_Layer_t>();

        x_collision_layer->collision_layer_type = none<Collision_Layer_Type_e*>();
        x_collision_layer->Collision_Layer_Type(collision_layer_type);

        return x_collision_layer;
    }

    void Extra_Collision_Layer_t::Destroy(some<Extra_Collision_Layer_t*> collision_layer_x)
    {
        SKYLIB_ASSERT_SOME(collision_layer_x);

        collision_layer_x->Collision_Layer_Type(Collision_Layer_Type_e::_NONE_);

        Extra_Data_t::Destroy<Extra_Collision_Layer_t>(collision_layer_x);
    }

    Collision_Layer_Type_e Extra_Collision_Layer_t::Collision_Layer_Type()
    {
        if (this->collision_layer_type) {
            return *this->collision_layer_type;
        } else {
            return Collision_Layer_Type_e::_NONE_;
        }
    }

    void Extra_Collision_Layer_t::Collision_Layer_Type(Collision_Layer_Type_e collision_layer_type)
    {
        if (collision_layer_type != Collision_Layer_Type_e::_NONE_) {
            if (!this->collision_layer_type) {
                this->collision_layer_type = Game_t::Allocate<Collision_Layer_Type_e>()();
            }
            *this->collision_layer_type = collision_layer_type;
        } else {
            if (this->collision_layer_type) {
                Game_t::Deallocate<Collision_Layer_Type_e>(this->collision_layer_type());
                this->collision_layer_type = none<Collision_Layer_Type_e*>();
            }
        }
    }

    void Extra_Collision_Layer_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Extra_Collision_Layer_t::Log");
        SKYLIB_LOG(indent + "{");

        if (collision_layer_type) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "collision_layer_type: %d", *collision_layer_type);
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "collision_layer_type: (nullptr)");
        }

        SKYLIB_LOG(indent + "}");
    }

}

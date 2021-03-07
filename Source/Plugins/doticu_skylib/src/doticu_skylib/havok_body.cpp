/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/havok_body.h"

namespace doticu_skylib {

    Collision_Layer_Type_e Havok_Body_t::Collision_Layer_Type()
    {
        return collidable_links.broad_phase_handle.collidable_flags() & Havok_Collidable_Flags_e::COLLISION_LAYER_MASK;
    }

    void Havok_Body_t::Collision_Layer_Type(Collision_Layer_Type_e collision_layer_type)
    {
        collidable_links.broad_phase_handle.collidable_flags =
            (collidable_links.broad_phase_handle.collidable_flags() & ~Havok_Collidable_Flags_e::COLLISION_LAYER_MASK) |
            (collision_layer_type() & Havok_Collidable_Flags_e::COLLISION_LAYER_MASK);
    }

}

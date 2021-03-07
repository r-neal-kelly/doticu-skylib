/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/actor_ai.h"
#include "doticu_skylib/actor_middle_high_ai.h"
#include "doticu_skylib/atomic_number.inl"
#include "doticu_skylib/game.h"

namespace doticu_skylib {

    void Actor_AI_t::Flag_Update_3D(Update_3D_Flags_e flag)
    {
        if (this->middle_high_ai) {
            this->middle_high_ai->update_3d_flags.Flag(flag);
        }
    }

    void Actor_AI_t::Unflag_Update_3D(Update_3D_Flags_e flag)
    {
        if (this->middle_high_ai) {
            this->middle_high_ai->update_3d_flags.Unflag(flag);
        }
    }

    void Actor_AI_t::Update_3D(some<Actor_t*> owning_actor)
    {
        static auto update_3d = reinterpret_cast
            <void(*)(Actor_AI_t*, Actor_t*)>
            (Game_t::Base_Address() + Offset_e::UPDATE_3D);

        SKYLIB_ASSERT_SOME(owning_actor);

        return update_3d(this, owning_actor());
    }

}

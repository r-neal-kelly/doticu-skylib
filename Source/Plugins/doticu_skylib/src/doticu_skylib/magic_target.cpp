/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.h"
#include "doticu_skylib/magic_target.h"

namespace doticu_skylib {

    Bool_t Magic_Target_t::Has_Magic_Effect(some<Magic_Effect_t*> magic_effect)
    {
        static auto has_magic_effect = reinterpret_cast
            <Bool_t(*)(Magic_Target_t*, Magic_Effect_t*)>
            (Game_t::Base_Address() + Offset_e::HAS_MAGIC_EFFECT);

        SKYLIB_ASSERT_SOME(magic_effect);
        return has_magic_effect(this, magic_effect());
    }

}

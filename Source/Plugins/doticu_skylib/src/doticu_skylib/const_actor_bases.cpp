/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/const_actor_bases.h"
#include "doticu_skylib/const_mods.h"
#include "doticu_skylib/game_macros.h"

namespace doticu_skylib { namespace Const { namespace Actor_Base {

    some<Actor_Base_t*> Player()    { DEFINE_FORM(Const::Mod::Skyrim(), Actor_Base_t, 0x000007); }

}}}

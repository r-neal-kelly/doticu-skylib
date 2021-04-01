/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/const_actors.h"
#include "doticu_skylib/const_mods.h"
#include "doticu_skylib/game_macros.h"

namespace doticu_skylib { namespace Const { namespace Actor {

    some<Actor_t*>  Player()    { DEFINE_FORM(Const::Mod::Skyrim(), Actor_t, 0x000014); }

}}}

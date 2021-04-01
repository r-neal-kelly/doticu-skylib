/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/const_mods.h"
#include "doticu_skylib/game_macros.h"
#include "doticu_skylib/mod.h"

namespace doticu_skylib { namespace Const { namespace Mod {

    some<Mod_t*>    Dawnguard()     { DEFINE_SOME_MOD("Dawnguard.esm"); }
    some<Mod_t*>    Dragonborn()    { DEFINE_SOME_MOD("Dragonborn.esm"); }
    some<Mod_t*>    Hearthfires()   { DEFINE_SOME_MOD("HearthFires.esm"); }
    some<Mod_t*>    Skyrim()        { DEFINE_SOME_MOD("Skyrim.esm"); }
    some<Mod_t*>    Update()        { DEFINE_SOME_MOD("Update.esm"); }

}}}

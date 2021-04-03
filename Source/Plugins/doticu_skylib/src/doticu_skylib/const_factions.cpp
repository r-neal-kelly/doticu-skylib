/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/const_factions.h"
#include "doticu_skylib/const_mods.h"
#include "doticu_skylib/faction.h"
#include "doticu_skylib/game_macros.h"

namespace doticu_skylib { namespace Const { namespace Faction {

    some<Faction_t*>    Player()    { DEFINE_FORM(Const::Mod::Skyrim(), Faction_t, 0x000DB1); }

}}}

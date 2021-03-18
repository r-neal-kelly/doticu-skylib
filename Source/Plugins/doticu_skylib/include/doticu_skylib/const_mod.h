/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Mod_t;

}

namespace doticu_skylib { namespace Const { namespace Mod {

    some<Mod_t*> Dawnguard();
    some<Mod_t*> Dragonborn();
    some<Mod_t*> Hearthfires();
    some<Mod_t*> Skyrim();
    some<Mod_t*> Update();

}}}

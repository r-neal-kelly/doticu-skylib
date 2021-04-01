/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Spell_t;

}

namespace doticu_skylib { namespace Const { namespace Spell {

    some<Spell_t*> Ghost_Ability();
    some<Spell_t*> Ghost_Ability_Fire();
    some<Spell_t*> Ghost_Ability_Fire_No_Alpha();
    some<Spell_t*> Ghost_Ability_Frost();
    some<Spell_t*> Ghost_Ability_Lost_To_The_Ages();
    some<Spell_t*> Ghost_Ability_Mages_Guild();
    some<Spell_t*> Ghost_Ability_New();
    some<Spell_t*> Ghost_Ability_Soul_Cairn();
    some<Spell_t*> Ghost_Ability_Storm();
    some<Spell_t*> Ghost_Ability_Violet();

}}}

namespace doticu_skylib { namespace Const { namespace Spells {

    Vector_t<some<Spell_t*>> Ghost_Abilities();

}}}

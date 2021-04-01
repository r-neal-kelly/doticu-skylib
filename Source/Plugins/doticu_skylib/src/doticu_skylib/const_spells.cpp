/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/const_mods.h"
#include "doticu_skylib/const_spells.h"
#include "doticu_skylib/game_macros.h"
#include "doticu_skylib/spell.h"

namespace doticu_skylib { namespace Const { namespace Spell {

    some<Spell_t*>  Ghost_Ability()                     { DEFINE_FORM(Const::Mod::Skyrim(),     Spell_t, 0x05030B); }
    some<Spell_t*>  Ghost_Ability_Fire()                { DEFINE_FORM(Const::Mod::Skyrim(),     Spell_t, 0x0D2064); }
    some<Spell_t*>  Ghost_Ability_Fire_No_Alpha()       { DEFINE_FORM(Const::Mod::Skyrim(),     Spell_t, 0x10F5A7); }
    some<Spell_t*>  Ghost_Ability_Frost()               { DEFINE_FORM(Const::Mod::Skyrim(),     Spell_t, 0x0D339B); }
    some<Spell_t*>  Ghost_Ability_Lost_To_The_Ages()    { DEFINE_FORM(Const::Mod::Dawnguard(),  Spell_t, 0x00CFAB); }
    some<Spell_t*>  Ghost_Ability_Mages_Guild()         { DEFINE_FORM(Const::Mod::Skyrim(),     Spell_t, 0x06A157); }
    some<Spell_t*>  Ghost_Ability_New()                 { DEFINE_FORM(Const::Mod::Skyrim(),     Spell_t, 0x0D2056); }
    some<Spell_t*>  Ghost_Ability_Soul_Cairn()          { DEFINE_FORM(Const::Mod::Dawnguard(),  Spell_t, 0x019AB2); }
    some<Spell_t*>  Ghost_Ability_Storm()               { DEFINE_FORM(Const::Mod::Skyrim(),     Spell_t, 0x0D339F); }
    some<Spell_t*>  Ghost_Ability_Violet()              { DEFINE_FORM(Const::Mod::Skyrim(),     Spell_t, 0x1034CC); }

}}}

namespace doticu_skylib { namespace Const { namespace Spells {

    Vector_t<some<Spell_t*>> Ghost_Abilities()
    {
        Vector_t<some<Spell_t*>> results;

        results.reserve(10);
        results.push_back(Spell::Ghost_Ability());
        results.push_back(Spell::Ghost_Ability_Fire());
        results.push_back(Spell::Ghost_Ability_Fire_No_Alpha());
        results.push_back(Spell::Ghost_Ability_Frost());
        results.push_back(Spell::Ghost_Ability_Lost_To_The_Ages());
        results.push_back(Spell::Ghost_Ability_Mages_Guild());
        results.push_back(Spell::Ghost_Ability_New());
        results.push_back(Spell::Ghost_Ability_Soul_Cairn());
        results.push_back(Spell::Ghost_Ability_Storm());
        results.push_back(Spell::Ghost_Ability_Violet());

        return results;
    }

}}}

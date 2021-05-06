/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/ammo.h"
#include "doticu_skylib/const_ammos.h"
#include "doticu_skylib/const_mods.h"
#include "doticu_skylib/game_macros.h"

namespace doticu_skylib { namespace Const { namespace Ammo {

    some<Ammo_t*>   Arrow_Ancient_Nordic()                              { DEFINE_FORM(Const::Mod::Skyrim(),         Ammo_t, 0x034182); }
    some<Ammo_t*>   Arrow_Ancient_Nordic_Hero()                         { DEFINE_FORM(Const::Mod::Skyrim(),         Ammo_t, 0x0EAFDF); }
    some<Ammo_t*>   Arrow_Bound()                                       { DEFINE_FORM(Const::Mod::Skyrim(),         Ammo_t, 0x10B0A7); }
    some<Ammo_t*>   Arrow_Daedric()                                     { DEFINE_FORM(Const::Mod::Skyrim(),         Ammo_t, 0x0139C0); }
    some<Ammo_t*>   Arrow_Dragonbone()                                  { DEFINE_FORM(Const::Mod::Dawnguard(),      Ammo_t, 0x0176F4); }
    some<Ammo_t*>   Arrow_Dwarven()                                     { DEFINE_FORM(Const::Mod::Skyrim(),         Ammo_t, 0x0139BC); }
    some<Ammo_t*>   Arrow_Ebony()                                       { DEFINE_FORM(Const::Mod::Skyrim(),         Ammo_t, 0x0139BF); }
    some<Ammo_t*>   Arrow_Elven()                                       { DEFINE_FORM(Const::Mod::Skyrim(),         Ammo_t, 0x0139BD); }
    some<Ammo_t*>   Arrow_Elven_Bloodcursed()                           { DEFINE_FORM(Const::Mod::Dawnguard(),      Ammo_t, 0x0098A0); }
    some<Ammo_t*>   Arrow_Elven_Sunhallowed()                           { DEFINE_FORM(Const::Mod::Dawnguard(),      Ammo_t, 0x0098A1); }
    some<Ammo_t*>   Arrow_Falmer()                                      { DEFINE_FORM(Const::Mod::Skyrim(),         Ammo_t, 0x038341); }
    some<Ammo_t*>   Arrow_Forsworn()                                    { DEFINE_FORM(Const::Mod::Skyrim(),         Ammo_t, 0x0CEE9E); }
    some<Ammo_t*>   Arrow_Glass()                                       { DEFINE_FORM(Const::Mod::Skyrim(),         Ammo_t, 0x0139BE); }
    some<Ammo_t*>   Arrow_Iron()                                        { DEFINE_FORM(Const::Mod::Skyrim(),         Ammo_t, 0x01397D); }
    some<Ammo_t*>   Arrow_Nordic()                                      { DEFINE_FORM(Const::Mod::Dragonborn(),     Ammo_t, 0x02623B); }
    some<Ammo_t*>   Arrow_Orcish()                                      { DEFINE_FORM(Const::Mod::Skyrim(),         Ammo_t, 0x0139BB); }
    some<Ammo_t*>   Arrow_Riekling()                                    { DEFINE_FORM(Const::Mod::Dragonborn(),     Ammo_t, 0x017720); }
    some<Ammo_t*>   Arrow_Stalhrim()                                    { DEFINE_FORM(Const::Mod::Dragonborn(),     Ammo_t, 0x026239); }
    some<Ammo_t*>   Arrow_Steel()                                       { DEFINE_FORM(Const::Mod::Skyrim(),         Ammo_t, 0x01397F); }

    some<Ammo_t*>   Bolt_Dwarven()                                      { DEFINE_FORM(Const::Mod::Dawnguard(),      Ammo_t, 0x00D099); }
    some<Ammo_t*>   Bolt_Dwarven_Fire()                                 { DEFINE_FORM(Const::Mod::Dawnguard(),      Ammo_t, 0x00F1B1); }
    some<Ammo_t*>   Bolt_Dwarven_Frost()                                { DEFINE_FORM(Const::Mod::Dawnguard(),      Ammo_t, 0x00F1B7); }
    some<Ammo_t*>   Bolt_Dwarven_Shock()                                { DEFINE_FORM(Const::Mod::Dawnguard(),      Ammo_t, 0x00F1B9); }
    some<Ammo_t*>   Bolt_Steel()                                        { DEFINE_FORM(Const::Mod::Dawnguard(),      Ammo_t, 0x000BB3); }
    some<Ammo_t*>   Bolt_Steel_Fire()                                   { DEFINE_FORM(Const::Mod::Dawnguard(),      Ammo_t, 0x00F1A0); }
    some<Ammo_t*>   Bolt_Steel_Frost()                                  { DEFINE_FORM(Const::Mod::Dawnguard(),      Ammo_t, 0x00F1BB); }
    some<Ammo_t*>   Bolt_Steel_Shock()                                  { DEFINE_FORM(Const::Mod::Dawnguard(),      Ammo_t, 0x00F1BC); }

}}}

namespace doticu_skylib { namespace Const { namespace Ammos {

    Vector_t<some<Ammo_t*>> All()
    {
        Vector_t<some<Ammo_t*>> results;
        All(results);
        return results;
    }

    void All(Vector_t<some<Ammo_t*>>& results)
    {
        Arrow(results);
        Bolt(results);
    }

    Vector_t<some<Ammo_t*>> Arrow()
    {
        Vector_t<some<Ammo_t*>> results;
        Arrow(results);
        return results;
    }

    void Arrow(Vector_t<some<Ammo_t*>>& results)
    {
        results.push_back(Ammo::Arrow_Ancient_Nordic());
        results.push_back(Ammo::Arrow_Ancient_Nordic_Hero());
        results.push_back(Ammo::Arrow_Bound());
        results.push_back(Ammo::Arrow_Daedric());
        results.push_back(Ammo::Arrow_Dragonbone());
        results.push_back(Ammo::Arrow_Dwarven());
        results.push_back(Ammo::Arrow_Ebony());
        results.push_back(Ammo::Arrow_Elven());
        results.push_back(Ammo::Arrow_Elven_Bloodcursed());
        results.push_back(Ammo::Arrow_Elven_Sunhallowed());
        results.push_back(Ammo::Arrow_Falmer());
        results.push_back(Ammo::Arrow_Forsworn());
        results.push_back(Ammo::Arrow_Glass());
        results.push_back(Ammo::Arrow_Iron());
        results.push_back(Ammo::Arrow_Nordic());
        results.push_back(Ammo::Arrow_Orcish());
        results.push_back(Ammo::Arrow_Riekling());
        results.push_back(Ammo::Arrow_Stalhrim());
        results.push_back(Ammo::Arrow_Steel());
    }

    Vector_t<some<Ammo_t*>> Bolt()
    {
        Vector_t<some<Ammo_t*>> results;
        Bolt(results);
        return results;
    }

    void Bolt(Vector_t<some<Ammo_t*>>& results)
    {
        results.push_back(Ammo::Bolt_Dwarven());
        results.push_back(Ammo::Bolt_Dwarven_Fire());
        results.push_back(Ammo::Bolt_Dwarven_Frost());
        results.push_back(Ammo::Bolt_Dwarven_Shock());
        results.push_back(Ammo::Bolt_Steel());
        results.push_back(Ammo::Bolt_Steel_Fire());
        results.push_back(Ammo::Bolt_Steel_Frost());
        results.push_back(Ammo::Bolt_Steel_Shock());
    }

}}}

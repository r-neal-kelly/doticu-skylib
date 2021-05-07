/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Ammo_t;

}

namespace doticu_skylib { namespace Const { namespace Ammo {

    some<Ammo_t*>   Arrow_Ancient_Nordic();
    some<Ammo_t*>   Arrow_Ancient_Nordic_Hero();
    some<Ammo_t*>   Arrow_Bound();
    some<Ammo_t*>   Arrow_Daedric();
    some<Ammo_t*>   Arrow_Dragonbone();
    some<Ammo_t*>   Arrow_Dwarven();
    some<Ammo_t*>   Arrow_Ebony();
    some<Ammo_t*>   Arrow_Elven();
    some<Ammo_t*>   Arrow_Elven_Bloodcursed();
    some<Ammo_t*>   Arrow_Elven_Sunhallowed();
    some<Ammo_t*>   Arrow_Falmer();
    some<Ammo_t*>   Arrow_Forsworn();
    some<Ammo_t*>   Arrow_Glass();
    some<Ammo_t*>   Arrow_Iron();
    some<Ammo_t*>   Arrow_Nordic();
    some<Ammo_t*>   Arrow_Orcish();
    some<Ammo_t*>   Arrow_Riekling();
    some<Ammo_t*>   Arrow_Stalhrim();
    some<Ammo_t*>   Arrow_Steel();

    some<Ammo_t*>   Bolt_Dwarven();
    some<Ammo_t*>   Bolt_Dwarven_Fire();
    some<Ammo_t*>   Bolt_Dwarven_Frost();
    some<Ammo_t*>   Bolt_Dwarven_Shock();
    some<Ammo_t*>   Bolt_Steel();
    some<Ammo_t*>   Bolt_Steel_Fire();
    some<Ammo_t*>   Bolt_Steel_Frost();
    some<Ammo_t*>   Bolt_Steel_Shock();

}}}

namespace doticu_skylib { namespace Const { namespace Ammos {

    Vector_t<some<Ammo_t*>> All();
    void                    All(Vector_t<some<Ammo_t*>>& results);

    Vector_t<some<Ammo_t*>> Arrow();
    void                    Arrow(Vector_t<some<Ammo_t*>>& results);

    Vector_t<some<Ammo_t*>> Bolt();
    void                    Bolt(Vector_t<some<Ammo_t*>>& results);

}}}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/bound_object.h"
#include "doticu_skylib/game.inl"
#include "doticu_skylib/leveled_item.h"

namespace doticu_skylib {

    maybe<Leveled_Item_t*> Bound_Object_t::As_Leveled_Item()
    {
        return Game_t::Runtime_Cast<Bound_Object_t, Leveled_Item_t>(this);
    }

    Bool_t Bound_Object_t::Is_Leveled_Item()
    {
        return As_Leveled_Item() != none<Leveled_Item_t*>();
    }

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/alias_base.h"
#include "doticu_skylib/alias_reference.h"
#include "doticu_skylib/collections.h"
#include "doticu_skylib/game.inl"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/scrap_array.inl"
#include "doticu_skylib/virtual_arguments.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_machine.h"
#include "doticu_skylib/virtual_policy.h"
#include "doticu_skylib/virtual_variable.inl"

namespace doticu_skylib {

    Bool_t Alias_Base_t::Is_Alias_Reference()
    {
        return As_Alias_Reference() != none<Alias_Reference_t*>();
    }

    Bool_t Alias_Base_t::Is_Quest_Item()
    {
        return (this->alias_base_flags & Alias_Base_Flags_e::IS_QUEST_ITEM) != 0;
    }

    maybe<Alias_Reference_t*> Alias_Base_t::As_Alias_Reference()
    {
        return Game_t::Runtime_Cast<Alias_Base_t, Alias_Reference_t>(this);
    }

}

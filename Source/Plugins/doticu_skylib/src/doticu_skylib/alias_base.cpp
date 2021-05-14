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

    maybe<Alias_Reference_t*> Alias_Base_t::As_Alias_Reference()
    {
        return Game_t::Runtime_Cast<Alias_Base_t, Alias_Reference_t>(this);
    }

    Bool_t Alias_Base_t::Is_Protected()
    {
        return this->alias_base_flags.Is_Flagged(Alias_Base_Flags_e::IS_PROTECTED);
    }

    void Alias_Base_t::Is_Protected(Bool_t value)
    {
        if (value) {
            this->alias_base_flags.Flag(Alias_Base_Flags_e::IS_PROTECTED);
        } else {
            this->alias_base_flags.Unflag(Alias_Base_Flags_e::IS_PROTECTED);
        }
    }

    Bool_t Alias_Base_t::Is_Essential()
    {
        return this->alias_base_flags.Is_Flagged(Alias_Base_Flags_e::IS_ESSENTIAL);
    }

    void Alias_Base_t::Is_Essential(Bool_t value)
    {
        if (value) {
            this->alias_base_flags.Flag(Alias_Base_Flags_e::IS_ESSENTIAL);
        } else {
            this->alias_base_flags.Unflag(Alias_Base_Flags_e::IS_ESSENTIAL);
        }
    }

    Bool_t Alias_Base_t::Is_Quest_Item() const
    {
        return this->alias_base_flags.Is_Flagged(Alias_Base_Flags_e::IS_QUEST_ITEM);
    }

    void Alias_Base_t::Is_Quest_Item(Bool_t value)
    {
        if (value) {
            this->alias_base_flags.Flag(Alias_Base_Flags_e::IS_QUEST_ITEM);
        } else {
            this->alias_base_flags.Unflag(Alias_Base_Flags_e::IS_QUEST_ITEM);
        }
    }

    Bool_t Alias_Base_t::Do_Clear_Name_On_Remove() const
    {
        return this->alias_base_flags.Is_Flagged(Alias_Base_Flags_e::CLEARS_NAME_ON_REMOVE);
    }

    void Alias_Base_t::Do_Clear_Name_On_Remove(Bool_t value)
    {
        this->alias_base_flags.Is_Flagged(Alias_Base_Flags_e::CLEARS_NAME_ON_REMOVE, value);
    }

    Bool_t Alias_Base_t::Do_Store_Name() const
    {
        return this->alias_base_flags.Is_Flagged(Alias_Base_Flags_e::STORES_NAME);
    }

    void Alias_Base_t::Do_Store_Name(Bool_t value)
    {
        this->alias_base_flags.Is_Flagged(Alias_Base_Flags_e::STORES_NAME, value);
    }

}

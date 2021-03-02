/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/atomic_number.inl"
#include "doticu_skylib/component_actor_base_data.h"
#include "doticu_skylib/dynamic_array.inl"

namespace doticu_skylib {

    Bool_t Actor_Base_Data_c::Is_Male()
    {
        return !Is_Female();
    }

    Bool_t Actor_Base_Data_c::Is_Female()
    {
        return (actor_base_flags & Actor_Base_Flags_e::IS_FEMALE) != 0;
    }

    Bool_t Actor_Base_Data_c::Is_Unique()
    {
        return (actor_base_flags & Actor_Base_Flags_e::IS_UNIQUE) != 0;
    }

    Bool_t Actor_Base_Data_c::Is_Generic()
    {
        return !Is_Unique();
    }

    Bool_t Actor_Base_Data_c::Is_Ghost()
    {
        return (actor_base_flags & Actor_Base_Flags_e::IS_GHOST) != 0;
    }

    Bool_t Actor_Base_Data_c::Is_Mortal()
    {
        return !Is_Protected() && !Is_Essential() && !Is_Invulnerable();
    }

    void Actor_Base_Data_c::Is_Mortal(Bool_t value)
    {
        if (value) {
            this->actor_base_flags &= ~Actor_Base_Flags_e::IS_PROTECTED;
            this->actor_base_flags &= ~Actor_Base_Flags_e::IS_ESSENTIAL;
            this->actor_base_flags &= ~Actor_Base_Flags_e::IS_INVULNERABLE;
        }

        Component_Flag_Form_Change(Form_Change_Flags_e::ACTOR_BASE_DATA);
    }

    Bool_t Actor_Base_Data_c::Is_Protected()
    {
        return (actor_base_flags & Actor_Base_Flags_e::IS_PROTECTED) != 0;
    }

    void Actor_Base_Data_c::Is_Protected(Bool_t value)
    {
        if (value) {
            this->actor_base_flags |= Actor_Base_Flags_e::IS_PROTECTED;
            this->actor_base_flags &= ~Actor_Base_Flags_e::IS_ESSENTIAL;
            this->actor_base_flags &= ~Actor_Base_Flags_e::IS_INVULNERABLE;
        } else {
            this->actor_base_flags &= ~Actor_Base_Flags_e::IS_PROTECTED;
        }

        Component_Flag_Form_Change(Form_Change_Flags_e::ACTOR_BASE_DATA);
    }

    Bool_t Actor_Base_Data_c::Is_Essential()
    {
        return (actor_base_flags & Actor_Base_Flags_e::IS_ESSENTIAL) != 0;
    }

    void Actor_Base_Data_c::Is_Essential(Bool_t value)
    {
        if (value) {
            this->actor_base_flags &= ~Actor_Base_Flags_e::IS_PROTECTED;
            this->actor_base_flags |= Actor_Base_Flags_e::IS_ESSENTIAL;
            this->actor_base_flags &= ~Actor_Base_Flags_e::IS_INVULNERABLE;
        } else {
            this->actor_base_flags &= ~Actor_Base_Flags_e::IS_ESSENTIAL;
        }

        Component_Flag_Form_Change(Form_Change_Flags_e::ACTOR_BASE_DATA);
    }

    Bool_t Actor_Base_Data_c::Is_Invulnerable()
    {
        return (actor_base_flags & Actor_Base_Flags_e::IS_INVULNERABLE) != 0;
    }

    void Actor_Base_Data_c::Is_Invulnerable(Bool_t value)
    {
        if (value) {
            this->actor_base_flags &= ~Actor_Base_Flags_e::IS_PROTECTED;
            this->actor_base_flags &= ~Actor_Base_Flags_e::IS_ESSENTIAL;
            this->actor_base_flags |= Actor_Base_Flags_e::IS_INVULNERABLE;
        } else {
            this->actor_base_flags &= ~Actor_Base_Flags_e::IS_INVULNERABLE;
        }

        Component_Flag_Form_Change(Form_Change_Flags_e::ACTOR_BASE_DATA);
    }

    maybe<Raw_Faction_Rank_t> Actor_Base_Data_c::Faction_Rank(some<Faction_t*> faction)
    {
        SKYLIB_ASSERT(faction);

        return this->factions_and_ranks.Faction_Rank(faction);
    }

    void Actor_Base_Data_c::Faction_Rank(some<Faction_t*> faction, some<Raw_Faction_Rank_t> rank)
    {
        SKYLIB_ASSERT(faction);

        this->factions_and_ranks.Faction_Rank(faction, rank);

        Component_Flag_Form_Change(Form_Change_Flags_e::ACTOR_BASE_DATA);
        Component_Flag_Form_Change(Form_Change_Flags_e::FACTIONS);
    }

    Vector_t<Faction_And_Rank_t> Actor_Base_Data_c::Factions_And_Ranks(Bool_t remove_negatives)
    {
        Vector_t<Faction_And_Rank_t> results;
        Factions_And_Ranks(results, remove_negatives);
        return results;
    }

    void Actor_Base_Data_c::Factions_And_Ranks(Vector_t<Faction_And_Rank_t>& results, Bool_t remove_negatives)
    {
        Vector_t<Faction_And_Rank_t> buffer;
        Vector_t<Faction_And_Rank_t>* output;
        if (remove_negatives) {
            output = &buffer;
            buffer.reserve(factions_and_ranks.Count());
            results.reserve(factions_and_ranks.Count());
        } else {
            output = &results;
            results.reserve(factions_and_ranks.Count());
        }

        for (Index_t idx = 0, end = factions_and_ranks.Count(); idx < end; idx += 1) {
            Faction_And_Rank_t& faction_and_rank = factions_and_ranks[idx];
            if (faction_and_rank.Is_Valid()) {
                maybe<Index_t> output_idx = output->Index_Of(faction_and_rank, &Faction_And_Rank_t::Has_Same_Faction);
                if (output_idx) {
                    output->operator[](idx).rank = faction_and_rank.rank;
                } else {
                    output->push_back(faction_and_rank);
                }
            }
        }

        if (remove_negatives) {
            for (Index_t idx = 0, end = buffer.size(); idx < end; idx += 1) {
                Faction_And_Rank_t& faction_and_rank = buffer[idx];
                if (faction_and_rank.rank > -1) {
                    results.push_back(faction_and_rank);
                }
            }
        }
    }

    void Actor_Base_Data_c::Log_Factions_And_Ranks(std::string indent)
    {
        SKYLIB_LOG(indent + "Actor_Base_Data_c::Log_Factions_And_Ranks");
        SKYLIB_LOG(indent + "{");

        Vector_t<Faction_And_Rank_t> factions_and_ranks = Factions_And_Ranks();
        for (Index_t idx = 0, end = factions_and_ranks.size(); idx < end; idx += 1) {
            factions_and_ranks[idx].Log(indent + SKYLIB_TAB);
        }

        SKYLIB_LOG(indent + "}");
    }

}

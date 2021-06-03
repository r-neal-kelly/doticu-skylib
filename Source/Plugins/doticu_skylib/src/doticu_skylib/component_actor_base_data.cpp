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
        return this->actor_base_flags.Is_Flagged(Actor_Base_Flags_e::IS_FEMALE);
    }

    Bool_t Actor_Base_Data_c::Is_Unique()
    {
        return this->actor_base_flags.Is_Flagged(Actor_Base_Flags_e::IS_UNIQUE);
    }

    Bool_t Actor_Base_Data_c::Is_Generic()
    {
        return !Is_Unique();
    }

    Bool_t Actor_Base_Data_c::Is_Ghost()
    {
        return this->actor_base_flags.Is_Flagged(Actor_Base_Flags_e::IS_GHOST);
    }

    Bool_t Actor_Base_Data_c::Does_Respawn()
    {
        return this->actor_base_flags.Is_Flagged(Actor_Base_Flags_e::DOES_RESPAWN);
    }

    Bool_t Actor_Base_Data_c::Is_Mortal()
    {
        return !Is_Protected() && !Is_Essential() && !Is_Invulnerable();
    }

    void Actor_Base_Data_c::Is_Mortal(Bool_t value, Bool_t do_save)
    {
        if (value) {
            this->actor_base_flags.Unflag(Actor_Base_Flags_e::IS_PROTECTED);
            this->actor_base_flags.Unflag(Actor_Base_Flags_e::IS_ESSENTIAL);
            this->actor_base_flags.Unflag(Actor_Base_Flags_e::IS_INVULNERABLE);
        }

        if (do_save) {
            Component_Flag_Form_Change(Form_Change_Flags_e::ACTOR_BASE_DATA);
        }
    }

    Bool_t Actor_Base_Data_c::Is_Protected()
    {
        return this->actor_base_flags.Is_Flagged(Actor_Base_Flags_e::IS_PROTECTED);
    }

    void Actor_Base_Data_c::Is_Protected(Bool_t value, Bool_t do_save)
    {
        if (value) {
            this->actor_base_flags.Flag(Actor_Base_Flags_e::IS_PROTECTED);
            this->actor_base_flags.Unflag(Actor_Base_Flags_e::IS_ESSENTIAL);
        } else {
            this->actor_base_flags.Unflag(Actor_Base_Flags_e::IS_PROTECTED);
        }

        if (do_save) {
            Component_Flag_Form_Change(Form_Change_Flags_e::ACTOR_BASE_DATA);
        }
    }

    Bool_t Actor_Base_Data_c::Is_Essential()
    {
        return this->actor_base_flags.Is_Flagged(Actor_Base_Flags_e::IS_ESSENTIAL);
    }

    void Actor_Base_Data_c::Is_Essential(Bool_t value, Bool_t do_save)
    {
        if (value) {
            this->actor_base_flags.Unflag(Actor_Base_Flags_e::IS_PROTECTED);
            this->actor_base_flags.Flag(Actor_Base_Flags_e::IS_ESSENTIAL);
        } else {
            this->actor_base_flags.Unflag(Actor_Base_Flags_e::IS_ESSENTIAL);
        }

        if (do_save) {
            Component_Flag_Form_Change(Form_Change_Flags_e::ACTOR_BASE_DATA);
        }
    }

    Bool_t Actor_Base_Data_c::Is_Invulnerable()
    {
        return this->actor_base_flags.Is_Flagged(Actor_Base_Flags_e::IS_INVULNERABLE);
    }

    void Actor_Base_Data_c::Is_Invulnerable(Bool_t value, Bool_t do_save)
    {
        if (value) {
            this->actor_base_flags.Flag(Actor_Base_Flags_e::IS_INVULNERABLE);
        } else {
            this->actor_base_flags.Unflag(Actor_Base_Flags_e::IS_INVULNERABLE);
        }

        if (do_save) {
            Component_Flag_Form_Change(Form_Change_Flags_e::ACTOR_BASE_DATA);
        }
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

        for (size_t idx = 0, end = factions_and_ranks.Count(); idx < end; idx += 1) {
            Faction_And_Rank_t& faction_and_rank = factions_and_ranks[idx];
            if (faction_and_rank.Is_Valid()) {
                maybe<size_t> output_idx = output->Index_Of(faction_and_rank, &Faction_And_Rank_t::Has_Same_Faction);
                if (output_idx.Has_Value()) {
                    output->at(output_idx.Value()).rank = faction_and_rank.rank;
                } else {
                    output->push_back(faction_and_rank);
                }
            }
        }

        if (remove_negatives) {
            for (size_t idx = 0, end = buffer.size(); idx < end; idx += 1) {
                Faction_And_Rank_t& faction_and_rank = buffer[idx];
                if (faction_and_rank.rank > -1) {
                    results.push_back(faction_and_rank);
                }
            }
        }
    }

    some<Vitality_e> Actor_Base_Data_c::Vitality()
    {
        if (Is_Invulnerable()) {
            return Vitality_e::INVULNERABLE;
        } else if (Is_Essential()) {
            return Vitality_e::ESSENTIAL;
        } else if (Is_Protected()) {
            return Vitality_e::PROTECTED;
        } else {
            return Vitality_e::MORTAL;
        }
    }

    void Actor_Base_Data_c::Vitality(some<Vitality_e> vitality, Bool_t do_save)
    {
        SKYLIB_ASSERT_SOME(vitality);

        if (vitality == Vitality_e::INVULNERABLE) {
            Is_Invulnerable(true, do_save);
        } else if (vitality == Vitality_e::ESSENTIAL) {
            Is_Essential(true, do_save);
        } else if (vitality == Vitality_e::PROTECTED) {
            Is_Protected(true, do_save);
        } else {
            Is_Mortal(true, do_save);
        }
    }

    maybe<Voice_Type_t*> Actor_Base_Data_c::Voice_Type()
    {
        return this->voice_type;
    }

    void Actor_Base_Data_c::Voice_Type(maybe<Voice_Type_t*> voice_type)
    {
        this->voice_type = voice_type;
    }

    void Actor_Base_Data_c::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Actor_Base_Data_c::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "actor_base_flags:");
        this->actor_base_flags.Log(indent + SKYLIB_TAB + SKYLIB_TAB);

        SKYLIB_LOG(indent + SKYLIB_TAB + "actor_base_template_flags:");
        this->actor_base_template_flags.Log(indent + SKYLIB_TAB + SKYLIB_TAB);

        if (this->template_form) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "template_form:");
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_TAB + "form_type: %s, form_id: %s, component_name: %s",
                       Form_Type_e::To_String(this->template_form->form_type),
                       this->template_form->Form_ID_String(),
                       this->template_form->Component_Name());
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "template_form: (none)");
        }

        SKYLIB_LOG(indent + SKYLIB_TAB + "unk_38: 0x%X", this->unk_38);
        SKYLIB_LOG(indent + SKYLIB_TAB + "unk_3C: 0x%X", this->unk_3C);

        SKYLIB_LOG(indent + "}");
    }

    void Actor_Base_Data_c::Log_Factions_And_Ranks(std::string indent)
    {
        SKYLIB_LOG(indent + "Actor_Base_Data_c::Log_Factions_And_Ranks");
        SKYLIB_LOG(indent + "{");

        Vector_t<Faction_And_Rank_t> factions_and_ranks = Factions_And_Ranks();
        for (size_t idx = 0, end = factions_and_ranks.size(); idx < end; idx += 1) {
            factions_and_ranks[idx].Log(indent + SKYLIB_TAB);
        }

        SKYLIB_LOG(indent + "}");
    }

    void Actor_Base_Data_c::Log_Template_Form(std::string indent) const
    {
        if (this->template_form) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "template_form:");
            this->template_form->Log_Name_And_Type(indent + SKYLIB_TAB + SKYLIB_TAB);
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "template_form: (none)");
        }
    }

}

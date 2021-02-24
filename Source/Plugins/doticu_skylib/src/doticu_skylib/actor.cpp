/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_ai.h"
#include "doticu_skylib/actor_ai_cached_values.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/actor_middle_high_ai.h"
#include "doticu_skylib/atomic_number.inl"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/extra_factions_and_ranks.h"
#include "doticu_skylib/extra_list.inl"
#include "doticu_skylib/game.inl"
#include "doticu_skylib/havok_actor_controller.h"
#include "doticu_skylib/havok_actor_rigid_body_controller.h"
#include "doticu_skylib/interface.h"
#include "doticu_skylib/keyword.h"
#include "doticu_skylib/leveled_actor_base.h"
#include "doticu_skylib/location.h"
#include "doticu_skylib/player.h"
#include "doticu_skylib/race.h"
#include "doticu_skylib/worldspace.h"

namespace doticu_skylib {

    Vector_t<Actor_t*> Actor_t::Loaded_Actors()
    {
        Vector_t<Actor_t*> loaded_actors;
        Loaded_Actors(loaded_actors);
        return loaded_actors;
    }

    void Actor_t::Loaded_Actors(Vector_t<Actor_t*>& results)
    {
        results.reserve(2048);

        Vector_t<Cell_t*> loaded_cells = Cell_t::Loaded_Cells();
        for (Index_t idx = 0, end = loaded_cells.size(); idx < end; idx += 1) {
            Cell_t* cell = loaded_cells[idx];
            class Iterator_t : public Iterator_i<void, Reference_t*>
            {
            public:
                Vector_t<Actor_t*>& results;
                Iterator_t(Vector_t<Actor_t*>& results) :
                    results(results)
                {
                }
                void operator()(Reference_t* reference)
                {
                    if (reference && reference->Is_Valid() && reference->form_type == Form_Type_e::ACTOR) {
                        Actor_t* actor = static_cast<Actor_t*>(reference);
                        if (!results.Has(actor)) {
                            results.push_back(actor);
                        }
                    }
                }
            } iterator(results);
            cell->References(iterator);
        }
    }

    maybe<Actor_t*> Actor_t::Create(some<Form_t*> base, Bool_t do_persist, Bool_t do_uncombative)
    {
        SKYLIB_ASSERT_SOME(base);

        if (base->Is_Valid()) {
            Actor_t* actor = static_cast<Actor_t*>
                (Reference_t::Create(base, 1, Player_t::Self(), do_persist, false));
            if (actor && actor->Is_Valid()) {
                if (do_uncombative) {
                    actor->Set_Actor_Value(Actor_Value_e::AGGRESSION, 0.0f);
                }
                return actor;
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    maybe<Actor_t*> Actor_t::Create(some<Actor_Base_t*> base, Bool_t do_persist, Bool_t do_uncombative, Bool_t do_static)
    {
        SKYLIB_ASSERT_SOME(base);

        if (do_static) {
            if (base->Is_Valid()) {
                return Create(static_cast<Form_t*>(base->Root_Base()), do_persist, do_uncombative);
            } else {
                return nullptr;
            }
        } else {
            return Create(static_cast<some<Form_t*>>(base), do_persist, do_uncombative);
        }
    }

    maybe<Actor_t*> Actor_t::Create(some<Leveled_Actor_Base_t*> base, Bool_t do_persist, Bool_t do_uncombative, Bool_t do_static)
    {
        SKYLIB_ASSERT_SOME(base);

        if (do_static) {
            if (base->Is_Valid()) {
                Actor_t* actor = static_cast<Actor_t*>
                    (Reference_t::Create(base, 1, Player_t::Self(), false, true));
                if (actor && actor->Is_Valid()) {
                    maybe<Actor_Base_t*> actor_base = static_cast<maybe<Actor_Base_t*>>(actor->base_form);
                    actor->Mark_For_Delete();
                    if (actor_base) {
                        return Create(actor_base(), do_static, do_persist, do_uncombative);
                    } else {
                        return nullptr;
                    }
                } else {
                    return nullptr;
                }
            } else {
                return nullptr;
            }
        } else {
            return Create(static_cast<some<Form_t*>>(base), do_persist, do_uncombative);
        }
    }

    Bool_t Actor_t::Is_Unique()
    {
        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base) {
            return actor_base->Is_Unique();
        } else {
            return false;
        }
    }

    Bool_t Actor_t::Is_Generic()
    {
        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base) {
            return actor_base->Is_Generic();
        } else {
            return false;
        }
    }

    Bool_t Actor_t::Is_Vampire()
    {
        return Has_Keyword(Keyword_t::Vampire()());
    }

    Bool_t Actor_t::Isnt_Vampire()
    {
        return !Is_Vampire();
    }

    Bool_t Actor_t::Has_Mount()
    {
        return !!Mount();
    }

    Bool_t Actor_t::Has_Rider()
    {
        return !!Rider();
    }

    Bool_t Actor_t::Is_Owner_Of(some<Reference_t*> reference)
    {
        SKYLIB_ASSERT_SOME(reference);
        return reference->Has_Owner(this);
    }

    Bool_t Actor_t::Is_Potential_Thief_Of(some<Reference_t*> reference)
    {
        SKYLIB_ASSERT_SOME(reference);
        return reference->Has_Potential_Thief(this);
    }

    Sex_e Actor_t::Sex()
    {
        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base) {
            return actor_base->Sex();
        } else {
            return Sex_e::_NONE_;
        }
    }

    maybe<Race_t*> Actor_t::Race()
    {
        if (this->race) {
            return this->race;
        } else {
            maybe<Actor_Base_t*> actor_base = Actor_Base();
            if (actor_base) {
                return actor_base->Race();
            } else {
                return none<Race_t*>();
            }
        }
    }

    maybe<Actor_Base_t*> Actor_t::Actor_Base()
    {
        if (this->base_form) {
            return this->base_form->As_Actor_Base();
        } else {
            return none<Actor_Base_t*>();
        }
    }

    Actor_Base_t* Actor_t::Highest_Static_Actor_Base()
    {
        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base && actor_base->Is_Valid()) {
            return actor_base->Highest_Static();
        } else {
            return nullptr;
        }
    }

    Vector_t<Actor_Base_t*> Actor_t::Actor_Bases()
    {
        if (base_form && base_form->Is_Valid()) {
            Vector_t<Actor_Base_t*> results;
            results.reserve(4);
            Actor_Bases(results);
            return results;
        } else {
            return Vector_t<Actor_Base_t*>();
        }
    }

    void Actor_t::Actor_Bases(Vector_t<Actor_Base_t*>& results)
    {
        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base && base_form->Is_Valid()) {
            results.push_back(actor_base());
            actor_base->Templates(results);
        }
    }

    Vector_t<Faction_And_Rank_t> Actor_t::Factions_And_Ranks(Bool_t remove_negatives)
    {
        Vector_t<Faction_And_Rank_t> results;
        Factions_And_Ranks(results, remove_negatives);
        return results;
    }

    void Actor_t::Factions_And_Ranks(Vector_t<Faction_And_Rank_t>& results, Bool_t remove_negatives)
    {
        Array_t<Faction_And_Rank_t>* base_factions_and_ranks = nullptr;
        Array_t<Faction_And_Rank_t>* reference_factions_and_ranks = nullptr;
        size_t reserve_count = 0;

        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base && actor_base->Is_Valid()) {
            base_factions_and_ranks = &actor_base->factions_and_ranks;
            reserve_count += base_factions_and_ranks->count;
        }

        maybe<Extra_Factions_And_Ranks_t*> xfactions_and_ranks = x_list.Get<Extra_Factions_And_Ranks_t>();
        if (xfactions_and_ranks) {
            reference_factions_and_ranks = &xfactions_and_ranks->factions_and_ranks;
            reserve_count += reference_factions_and_ranks->count;
        }

        Vector_t<Faction_And_Rank_t> buffer;
        Vector_t<Faction_And_Rank_t>* output;
        if (remove_negatives) {
            output = &buffer;
            buffer.reserve(reserve_count);
            results.reserve(reserve_count);
        } else {
            output = &results;
            results.reserve(reserve_count);
        }

        if (base_factions_and_ranks) {
            for (Index_t idx = 0, end = base_factions_and_ranks->count; idx < end; idx += 1) {
                Faction_And_Rank_t& faction_and_rank = base_factions_and_ranks->entries[idx];
                if (faction_and_rank.Is_Valid()) {
                    maybe<Index_t> output_idx = output->Index_Of(faction_and_rank, &Faction_And_Rank_t::Has_Same_Faction);
                    if (output_idx) {
                        output->operator[](idx).rank = faction_and_rank.rank;
                    } else {
                        output->push_back(faction_and_rank);
                    }
                }
            }
        }

        if (reference_factions_and_ranks) {
            for (Index_t idx = 0, end = reference_factions_and_ranks->count; idx < end; idx += 1) {
                Faction_And_Rank_t& faction_and_rank = reference_factions_and_ranks->entries[idx];
                if (faction_and_rank.Is_Valid()) {
                    maybe<Index_t> output_idx = output->Index_Of(faction_and_rank, &Faction_And_Rank_t::Has_Same_Faction);
                    if (output_idx) {
                        output->operator[](idx).rank = faction_and_rank.rank;
                    } else {
                        output->push_back(faction_and_rank);
                    }
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

    maybe<Havok_Actor_Controller_t*> Actor_t::Havok_Actor_Controller()
    {
        if (this->actor_ai && this->actor_ai->middle_high_ai) {
            return this->actor_ai->middle_high_ai->havok_actor_controller;
        } else {
            return none<Havok_Actor_Controller_t*>();
        }
    }

    maybe<Havok_Actor_Rigid_Body_Controller_t*> Actor_t::Havok_Actor_Rigid_Body_Controller()
    {
        maybe<Havok_Actor_Controller_t*> actor_controller = Havok_Actor_Controller();
        if (actor_controller) {
            return Game_t::Runtime_Cast<Havok_Actor_Controller_t, Havok_Actor_Rigid_Body_Controller_t>(actor_controller());
        } else {
            return nullptr;
        }
    }

    Vector_t<Keyword_t*> Actor_t::Keywords(Bool_t include_templates)
    {
        Vector_t<Keyword_t*> results;
        Keywords(results, include_templates);
        return results;
    }

    void Actor_t::Keywords(Vector_t<Keyword_t*>& results, Bool_t include_templates)
    {
        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base && actor_base->Is_Valid()) {
            actor_base->Keywords(results, include_templates);
        }
    }

    maybe<Actor_t*> Actor_t::Mount()
    {
        return this->x_list.Reference_Interactor_A();
    }

    maybe<Actor_t*> Actor_t::Rider()
    {
        return this->x_list.Reference_Interactor_B();
    }

    const char* Actor_t::Base_Name()
    {
        if (base_form) {
            return static_cast<maybe<Actor_Base_t*>>(base_form)->Name();
        } else {
            return "";
        }
    }

    String_t Actor_t::Any_Name()
    {
        const char* name = Name();
        if (!name || !name[0]) {
            name = Base_Name();
            if (!name || !name[0]) {
                name = Get_Editor_ID();
                if (!name || !name[0]) {
                    return Form_ID_String();
                } else {
                    return name;
                }
            } else {
                return name;
            }
        } else {
            return name;
        }
    }

    Bool_t Actor_t::Is_Player_Teammate()
    {
        return (actor_flags_1 & Actor_Flags_1_e::IS_PLAYER_TEAMMATE) != 0;
    }

    void Actor_t::Is_Player_Teammate(Bool_t value)
    {
        some<Player_t*> player = Player_t::Self();
        if (this != player()) {
            if (value) {
                if (!Is_Player_Teammate()) {
                    this->actor_flags_1 |= Actor_Flags_1_e::IS_PLAYER_TEAMMATE;
                    player->Increment_Teammate_Count();
                }
            } else {
                if (Is_Player_Teammate()) {
                    this->actor_flags_1 &= ~Actor_Flags_1_e::IS_PLAYER_TEAMMATE;
                    player->Decrement_Teammate_Count();
                }
            }
        }
    }

    Bool_t Actor_t::Can_Do_Favors()
    {
        return (actor_flags_2 & Actor_Flags_2_e::CAN_DO_FAVORS) != 0;
    }

    void Actor_t::Can_Do_Favors(Bool_t value)
    {
        if (value) {
            this->actor_flags_2 |= Actor_Flags_2_e::CAN_DO_FAVORS;
        } else {
            this->actor_flags_2 &= ~Actor_Flags_2_e::CAN_DO_FAVORS;
        }
    }

    Bool_t Actor_t::Can_Talk_To_Player()
    {
        Boolean_e can_talk_to_player = this->x_list.Can_Talk_To_Player();
        if (can_talk_to_player != Boolean_e::NEITHER) {
            return can_talk_to_player();
        } else {
            maybe<Race_t*> race = Race();
            if (race) {
                return race->Can_Talk_To_Player();
            } else {
                return false;
            }
        }
    }

    void Actor_t::Can_Talk_To_Player(Bool_t value)
    {
        if (Can_Talk_To_Player() != value) {
            this->x_list.Can_Talk_To_Player(value);
        }
    }

    Bool_t Actor_t::Ignores_Friendly_Hits()
    {
        return (this->form_flags & Form_Flags_e::IGNORES_FRIENDLY_HITS) != 0;
    }

    void Actor_t::Ignores_Friendly_Hits(Bool_t value)
    {
        if (value) {
            this->form_flags |= Form_Flags_e::IGNORES_FRIENDLY_HITS;
        } else {
            this->form_flags &= ~Form_Flags_e::IGNORES_FRIENDLY_HITS;
        }
        Flag_Form_Change(Form_Change_Flags_e::FORM_FLAGS);
    }

    Bool_t Actor_t::Is_Hidden_From_Stealth_Eye()
    {
        return (this->actor_flags_2 & Actor_Flags_2_e::IS_HIDDEN_FROM_STEALTH_EYE) != 0;
    }

    void Actor_t::Is_Hidden_From_Stealth_Eye(Bool_t value)
    {
        if (value) {
            this->actor_flags_2 |= Actor_Flags_2_e::IS_HIDDEN_FROM_STEALTH_EYE;
        } else {
            this->actor_flags_2 &= ~Actor_Flags_2_e::IS_HIDDEN_FROM_STEALTH_EYE;
        }
    }

    Bool_t Actor_t::Has_AI()
    {
        return (this->actor_flags_1 & Actor_Flags_1_e::DO_PROCESS_AI) != 0;
    }

    void Actor_t::Has_AI(Bool_t value)
    {
        if (value) {
            this->actor_flags_1 |= Actor_Flags_1_e::DO_PROCESS_AI;
        } else {
            this->actor_flags_1 &= ~Actor_Flags_1_e::DO_PROCESS_AI;
        }
    }

    void Actor_t::Reset_AI()
    {
        Evaluate_Package(true, true);
    }

    Bool_t Actor_t::Is_Ghost()
    {
        Boolean_e is_ghost = this->x_list.Is_Ghost();
        if (is_ghost != Boolean_e::NEITHER) {
            return is_ghost();
        } else {
            maybe<Actor_Base_t*> actor_base = Actor_Base();
            if (actor_base) {
                return actor_base->Is_Ghost();
            } else {
                return false;
            }
        }
    }

    void Actor_t::Is_Ghost(Bool_t value)
    {
        if (Is_Ghost() != value) {
            this->x_list.Is_Ghost(value);
            if (this->actor_ai && this->actor_ai->cached_values) {
                this->actor_ai->cached_values->Is_Ghost(value);
            }
        }
    }

    void Actor_t::Evaluate_Package(Bool_t do_immediately, Bool_t do_reset_ai)
    {
        static auto evaluate_package = reinterpret_cast
            <void(*)(Actor_t*, Bool_t, Bool_t)>
            (Game_t::Base_Address() + Offset_e::EVALUATE_PACKAGE);

        return evaluate_package(this, do_immediately, do_reset_ai);
    }

    void Actor_t::Queue_NI_Node_Update(Bool_t do_update_weight)
    {
        static auto queue_ni_node_update = reinterpret_cast
            <void(*)(Actor_t*, Bool_t)>
            (Game_t::Base_Address() + Offset_e::QUEUE_NI_NODE_UPDATE);

        return queue_ni_node_update(this, do_update_weight);
    }

    void Actor_t::Log_Factions_And_Ranks(std::string indent)
    {
        SKYLIB_LOG(indent + "Actor_t::Log_Factions_And_Ranks: %s", Any_Name());
        SKYLIB_LOG(indent + "{");

        Vector_t<Faction_And_Rank_t> factions_and_ranks = Factions_And_Ranks();
        for (Index_t idx = 0, end = factions_and_ranks.size(); idx < end; idx += 1) {
            factions_and_ranks[idx].Log(indent + SKYLIB_TAB);
        }

        SKYLIB_LOG(indent + "}");
    }

}

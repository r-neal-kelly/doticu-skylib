/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/interface.h"

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/leveled_actor_base.h"
#include "doticu_skylib/location.h"
#include "doticu_skylib/player.h"
#include "doticu_skylib/worldspace.h"

#include "doticu_skylib/extra_factions_and_ranks.h"
#include "doticu_skylib/extra_list.inl"

namespace doticu_skylib {

    Vector_t<Loaded_Actor_t> Actor_t::Loaded_Actors()
    {
        Vector_t<Loaded_Actor_t> loaded_actors;
        loaded_actors.reserve(2048);
        Loaded_Actors(loaded_actors);
        return loaded_actors;
    }

    void Actor_t::Loaded_Actors(Vector_t<Loaded_Actor_t>& results)
    {
        Vector_t<Cell_t*> loaded_cells = Cell_t::Loaded_Cells();
        for (Index_t idx = 0, end = loaded_cells.size(); idx < end; idx += 1) {
            Cell_t* cell = loaded_cells[idx];
            class Iterator_t : public Iterator_i<void, Reference_t*>
            {
            public:
                Vector_t<Loaded_Actor_t>& results;
                Cell_t* cell;
                Iterator_t(Vector_t<Loaded_Actor_t>& results, Cell_t* cell) :
                    results(results), cell(cell)
                {
                }
                void operator()(Reference_t* reference)
                {
                    if (reference->form_type == Form_Type_e::ACTOR) {
                        Loaded_Actor_t loaded_actor(static_cast<Actor_t*>(reference), cell);
                        if (loaded_actor.Is_Valid() && !results.Has(loaded_actor)) {
                            results.push_back(loaded_actor);
                        }
                    }
                }
            } iterator(results, cell);
            cell->References(iterator);
        }
    }

    void Actor_t::Log_Loaded_Actors()
    {
        #define TAB "    "

        Vector_t<Loaded_Actor_t> loaded_actors = Loaded_Actors();
        _MESSAGE("Log_Loaded_Actors {");
        for (size_t idx = 0, end = loaded_actors.size(); idx < end; idx += 1) {
            Actor_t* actor = loaded_actors[idx].actor;
            Cell_t* cell = loaded_actors[idx].cell;
            Location_t* location = cell->Location();
            const char* name = actor->Name();
            if (!name || !name[0]) {
                name = actor->Base_Name();
            }
            _MESSAGE(TAB "index: %6zu", idx);
            _MESSAGE(TAB TAB "actor: %8.8X %s, ref_count: %i", actor->form_id, name, actor->Reference_Count());
            if (cell->Is_Interior()) {
                _MESSAGE(TAB TAB "interior cell: %8.8X %s, location: %s",
                         cell->form_id, cell->Get_Editor_ID(), location ? location->Any_Name() : "");
            } else {
                Worldspace_t* worldspace = cell->worldspace;
                SKYLIB_ASSERT(worldspace);
                _MESSAGE(TAB TAB "exterior cell: %8.8X %s, location: %s",
                         cell->form_id, cell->Get_Editor_ID(), location ? location->Any_Name() : "");
                _MESSAGE(TAB TAB "worldspace: %8.8X %s", worldspace->form_id, worldspace->Get_Editor_ID());
            }
        }
        _MESSAGE("}");

        #undef TAB
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
            return Create(static_cast<Form_t*>(base), do_persist, do_uncombative);
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
                    Actor_Base_t* actor_base = static_cast<Actor_Base_t*>(actor->base_form);
                    actor->Mark_For_Delete();
                    return Create(actor_base, do_static, do_persist, do_uncombative);
                } else {
                    return nullptr;
                }
            } else {
                return nullptr;
            }
        } else {
            return Create(static_cast<Form_t*>(base), do_persist, do_uncombative);
        }
    }

    Sex_e Actor_t::Sex()
    {
        if (base_form) {
            return static_cast<Actor_Base_t*>(base_form)->Sex();
        } else {
            return Sex_e::NONE;
        }
    }

    Race_t* Actor_t::Race()
    {
        if (base_form) {
            return static_cast<Actor_Base_t*>(base_form)->Race();
        } else {
            return nullptr;
        }
    }

    Actor_Base_t* Actor_t::Actor_Base()
    {
        return static_cast<Actor_Base_t*>(base_form);
    }

    Actor_Base_t* Actor_t::Highest_Static_Actor_Base()
    {
        Actor_Base_t* actor_base = Actor_Base();
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
        Actor_Base_t* actor_base = Actor_Base();
        if (actor_base && base_form->Is_Valid()) {
            results.push_back(actor_base);
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

        Actor_Base_t* actor_base = Actor_Base();
        if (actor_base && actor_base->Is_Valid()) {
            base_factions_and_ranks = &actor_base->factions_and_ranks;
            reserve_count += base_factions_and_ranks->count;
        }

        Factions_And_Ranks_x* xfactions_and_ranks = xlist.Get<Factions_And_Ranks_x>();
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

    Vector_t<Keyword_t*> Actor_t::Keywords(Bool_t include_templates)
    {
        Vector_t<Keyword_t*> results;
        Keywords(results, include_templates);
        return results;
    }

    void Actor_t::Keywords(Vector_t<Keyword_t*>& results, Bool_t include_templates)
    {
        Actor_Base_t* actor_base = Actor_Base();
        if (actor_base && actor_base->Is_Valid()) {
            actor_base->Keywords(results, include_templates);
        }
    }

    const char* Actor_t::Base_Name()
    {
        if (base_form) {
            return static_cast<Actor_Base_t*>(base_form)->Name();
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

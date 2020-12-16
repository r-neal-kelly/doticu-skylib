/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <fstream>
#include <iomanip>

#include "doticu_skylib/interface.h"

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/keyword.h"
#include "doticu_skylib/player.h"
#include "doticu_skylib/reference.h"

namespace doticu_skylib {

    size_t Actor_Base_t::Actor_Base_Count()
    {
        return Game_t::Self()->Actor_Bases().count;
    }

    Vector_t<Actor_Base_t*> Actor_Base_t::Actor_Bases()
    {
        Vector_t<Actor_Base_t*> results;
        results.reserve(Actor_Base_Count());
        Actor_Bases(results);
        return results;
    }

    void Actor_Base_t::Actor_Bases(Vector_t<Actor_Base_t*>& results)
    {
        auto& actor_bases = Game_t::Self()->Actor_Bases();
        for (Index_t idx = 0, end = actor_bases.count; idx < end; idx += 1) {
            Actor_Base_t* actor_base = reinterpret_cast<Actor_Base_t*>(actor_bases.entries[idx]);
            if (actor_base) {
                results.push_back(actor_base);
            }
        }
    }

    Vector_t<Actor_Base_t*> Actor_Base_t::Dynamic_Actor_Bases()
    {
        Vector_t<Actor_Base_t*> results;
        results.reserve(64);
        Dynamic_Actor_Bases(results);
        return results;
    }

    void Actor_Base_t::Dynamic_Actor_Bases(Vector_t<Actor_Base_t*>& results)
    {
        Vector_t<Cell_t*> loaded_cells = Cell_t::Loaded_Cells();
        for (Index_t idx = 0, end = loaded_cells.size(); idx < end; idx += 1) {
            Cell_t* cell = loaded_cells[idx];
            class Iterator_t : public Iterator_i<void, Reference_t*>
            {
            public:
                Vector_t<Actor_Base_t*>& results;
                Cell_t* cell;
                Iterator_t(Vector_t<Actor_Base_t*>& results, Cell_t* cell) :
                    results(results), cell(cell)
                {
                }
                void operator()(Reference_t* reference)
                {
                    if (reference && reference->Is_Valid() && reference->form_type == Form_Type_e::ACTOR) {
                        Actor_Base_t* actor_base = static_cast<Actor_Base_t*>(reference->base_form);
                        if (actor_base && actor_base->Is_Valid() && actor_base->Is_Dynamic()) {
                            if (!results.Has(actor_base)) {
                                results.push_back(actor_base);
                            }
                        }
                    }
                }
            } iterator(results, cell);
            cell->References(iterator);
        }
    }

    void Actor_Base_t::Log_Actor_Bases()
    {
        #define TAB "    "

        Vector_t<Actor_Base_t*> actor_bases = Actor_Bases();
        _MESSAGE("Log_Actor_Bases {");
        for (size_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
            Actor_Base_t* actor_base = actor_bases[idx];
            _MESSAGE(TAB "index: %6zu, actor_base: %8.8X %s", idx, actor_base->form_id, actor_base->Any_Name());
        }
        _MESSAGE("}");

        #undef TAB
    }

    void Actor_Base_t::Log_Dynamic_Actor_Bases()
    {
        #define TAB "    "

        Vector_t<Actor_Base_t*> actor_bases = Dynamic_Actor_Bases();
        _MESSAGE("Log_Dynamic_Actor_Bases {");
        for (size_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
            Actor_Base_t* actor_base = actor_bases[idx];
            _MESSAGE(TAB "index: %6zu, actor_base: %8.8X %s", idx, actor_base->form_id, actor_base->Any_Name());
            SKYLIB_ASSERT(actor_base->template_list);
            for (Actor_Base_t* it = actor_base->template_list; it != nullptr; it = it->template_list) {
                _MESSAGE(TAB TAB "template: %8.8X %s", it->form_id, it->Any_Name());
            }
        }
        _MESSAGE("}");

        #undef TAB
    }

    void Actor_Base_t::Stream_Actor_Bases(Vector_t<some<Actor_Base_t*>>& actor_bases, std::fstream& fstream)
    {
        static constexpr const char* SPACE  = "     ";
        static constexpr const char* TAB    = "    ";

        if (fstream && fstream.is_open()) {
            size_t actor_bases_count = actor_bases.size();
            fstream << "Printing " << std::to_string(actor_bases_count) << " actor bases." << std::endl;

            size_t index_fill =
                actor_bases_count < 10 ? 1 :
                actor_bases_count < 100 ? 2 :
                actor_bases_count < 1000 ? 3 :
                actor_bases_count < 10000 ? 4 :
                actor_bases_count < 100000 ? 5 :
                6;

            for (Index_t idx = 0, end = actor_bases_count; idx < end; idx += 1) {
                some<Actor_Base_t*> actor_base = actor_bases[idx];
                SKYLIB_ASSERT_SOME(actor_base);

                String_t name = actor_base->Name();
                if (!name) {
                    name = "(none)";
                }

                const char* form_id = actor_base->Form_ID_String().data + 2;

                fstream << "index: "
                    << std::left
                    << std::setfill(' ')
                    << std::setw(index_fill)
                    << std::dec
                    << idx
                    << TAB;
                fstream << "form_id: "
                    << form_id
                    << TAB;
                fstream << "name: "
                    << name.data
                    << std::endl;
            }
        }
    }

    Int_t Actor_Base_t::Compare_Names(some<Actor_Base_t*>* a, some<Actor_Base_t*>* b)
    {
        if (!a || !*a) {
            return Comparator_e::IS_UNORDERED;
        } else if (!b || !*b) {
            return Comparator_e::IS_ORDERED;
        } else {
            Comparator_e result = Form_t::Compare_Names(
                (*a)->Any_Name(),
                (*b)->Any_Name()
            );
            if (result == Comparator_e::IS_EQUAL) {
                return (*a)->form_id - (*b)->form_id;
            } else {
                return result;
            }
        }
    }

    Bool_t Actor_Base_t::Has_Template_FF000800()
    {
        for (Actor_Base_t* it = template_list; it != nullptr; it = it->template_list) {
            if (it->form_id == 0xFF000800) {
                return true;
            }
        }
        return false;
    }

    Sex_e Actor_Base_t::Sex()
    {
        return Is_Female() ? Sex_e::FEMALE : Sex_e::MALE;
    }

    Rarity_e Actor_Base_t::Rarity()
    {
        return Is_Unique() ? Rarity_e::UNIQUE : Rarity_e::GENERIC;
    }

    Race_t* Actor_Base_t::Race()
    {
        return race;
    }

    Vector_t<Actor_Base_t*> Actor_Base_t::Templates()
    {
        if (template_list) {
            Vector_t<Actor_Base_t*> results;
            results.reserve(4);
            Templates(results);
            return results;
        } else {
            return Vector_t<Actor_Base_t*>();
        }
    }

    void Actor_Base_t::Templates(Vector_t<Actor_Base_t*>& results)
    {
        for (Actor_Base_t* it = template_list; it != nullptr; it = it->template_list) {
            results.push_back(it);
        }
    }

    Vector_t<Faction_And_Rank_t> Actor_Base_t::Factions_And_Ranks(Bool_t remove_negatives)
    {
        Vector_t<Faction_And_Rank_t> results;
        Factions_And_Ranks(results, remove_negatives);
        return results;
    }

    void Actor_Base_t::Factions_And_Ranks(Vector_t<Faction_And_Rank_t>& results, Bool_t remove_negatives)
    {
        Vector_t<Faction_And_Rank_t> buffer;
        Vector_t<Faction_And_Rank_t>* output;
        if (remove_negatives) {
            output = &buffer;
            buffer.reserve(factions_and_ranks.count);
            results.reserve(factions_and_ranks.count);
        } else {
            output = &results;
            results.reserve(factions_and_ranks.count);
        }

        for (Index_t idx = 0, end = factions_and_ranks.count; idx < end; idx += 1) {
            Faction_And_Rank_t& faction_and_rank = factions_and_ranks.entries[idx];
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

    Vector_t<Keyword_t*> Actor_Base_t::Keywords(Bool_t include_templates)
    {
        Vector_t<Keyword_t*> results;
        Keywords(results, include_templates);
        return results;
    }

    void Actor_Base_t::Keywords(Vector_t<Keyword_t*>& results, Bool_t include_templates)
    {
        if (include_templates) {
            size_t reserve_count = keyword_count;
            for (Actor_Base_t* it = template_list; it != nullptr; it = it->template_list) {
                reserve_count += it->keyword_count;
            }
            results.reserve(reserve_count);
        } else {
            results.reserve(keyword_count);
        }

        if (keywords) {
            for (Index_t idx = 0, end = keyword_count; idx < end; idx += 1) {
                Keyword_t* keyword = keywords[idx];
                if (keyword && keyword->Is_Valid() && !results.Has(keyword)) {
                    results.push_back(keyword);
                }
            }
        }

        if (include_templates) {
            for (Actor_Base_t* it = template_list; it != nullptr; it = it->template_list) {
                if (it->keywords) {
                    for (Index_t idx = 0, end = it->keyword_count; idx < end; idx += 1) {
                        Keyword_t* keyword = it->keywords[idx];
                        if (keyword && keyword->Is_Valid() && !results.Has(keyword)) {
                            results.push_back(keyword);
                        }
                    }
                }
            }
        }
    }

    Actor_Base_t* Actor_Base_t::Highest_Static()
    {
        if (Is_Static()) {
            return this;
        } else {
            for (Actor_Base_t* it = template_list; it != nullptr; it = it->template_list) {
                if (it->Is_Static()) {
                    return it;
                }
            }
            return nullptr;
        }
    }

    Actor_Base_t* Actor_Base_t::Root_Template()
    {
        if (template_list) {
            Actor_Base_t* it = template_list;
            for (; it->template_list != nullptr; it = it->template_list) {
            }
            return it;
        } else {
            return this;
        }
    }

    Actor_Base_t* Actor_Base_t::Root_Base()
    {
        Actor_Base_t* base = this;
        for (size_t recursions = 0; recursions < 8; recursions += 1) {
            if (base && base->Is_Valid()) {
                Actor_Base_t* root = base->Root_Template();
                if (root && root->Is_Valid()) {
                    if (root->Is_Dynamic()) {
                        Actor_t* actor = static_cast<Actor_t*>
                            (Reference_t::Create(base, 1, Player_t::Self(), false, false));
                        base = actor->Actor_Base();
                        actor->Mark_For_Delete();
                    } else {
                        return root;
                    }
                } else {
                    return nullptr;
                }
            } else {
                return nullptr;
            }
        }
        return nullptr;
    }

    String_t Actor_Base_t::Any_Name()
    {
        const char* name = Name();
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
    }

    void Actor_Base_t::Log_Factions_And_Ranks(std::string indent)
    {
        SKYLIB_LOG(indent + "Actor_Base_t::Log_Factions_And_Ranks: %s", Any_Name());
        SKYLIB_LOG(indent + "{");

        Vector_t<Faction_And_Rank_t> factions_and_ranks = Factions_And_Ranks();
        for (Index_t idx = 0, end = factions_and_ranks.size(); idx < end; idx += 1) {
            factions_and_ranks[idx].Log(indent + SKYLIB_TAB);
        }

        SKYLIB_LOG(indent + "}");
    }

}

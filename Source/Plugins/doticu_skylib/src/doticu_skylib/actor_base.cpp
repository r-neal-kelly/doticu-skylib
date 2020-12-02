/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/interface.h"

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/game.h"
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

}

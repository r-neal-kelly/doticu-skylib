/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/utils.h"
#include "doticu_skylib/actor.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/location.h"
#include "doticu_skylib/worldspace.h"

namespace doticu_skylib {

    /* Loaded_Actor_t */

    Loaded_Actor_t::Loaded_Actor_t() :
        actor(nullptr), cell(nullptr)
    {
    }

    Loaded_Actor_t::Loaded_Actor_t(Actor_t* actor, Cell_t* cell) :
        actor(actor), cell(cell)
    {
        if (!actor || !cell) {
            actor = nullptr;
            cell = nullptr;
        }
    }

    Loaded_Actor_t::Loaded_Actor_t(Form_ID_t actor_form_id, Form_ID_t cell_form_id) :
        Loaded_Actor_t(static_cast<Actor_t*>(Game_t::Form(actor_form_id)),
                       static_cast<Cell_t*>(Game_t::Form(cell_form_id)))
    {
    }

    Loaded_Actor_t::Loaded_Actor_t(const Loaded_Actor_t& other) :
        Loaded_Actor_t(other.actor, other.cell)
    {
    }

    Loaded_Actor_t::Loaded_Actor_t(Loaded_Actor_t&& other) noexcept :
        actor(std::exchange(other.actor, nullptr)),
        cell(std::exchange(other.cell, nullptr))
    {
        if (!actor || !cell) {
            actor = nullptr;
            cell = nullptr;
        }
    }

    Loaded_Actor_t::~Loaded_Actor_t()
    {
        actor = nullptr;
        cell = nullptr;
    }

    Loaded_Actor_t& Loaded_Actor_t::operator=(const Loaded_Actor_t& other)
    {
        if (this != &other) {
            if (other.actor && other.cell) {
                actor = other.actor;
                cell = other.cell;
            } else {
                actor = nullptr;
                cell = nullptr;
            }
        }
        return *this;
    }

    Loaded_Actor_t& Loaded_Actor_t::operator=(Loaded_Actor_t&& other) noexcept
    {
        if (this != &other) {
            actor = std::exchange(other.actor, nullptr);
            cell = std::exchange(other.cell, nullptr);
            if (!actor || !cell) {
                actor = nullptr;
                cell = nullptr;
            }
        }
        return *this;
    }

    Bool_t Loaded_Actor_t::operator==(const Loaded_Actor_t& other)
    {
        return actor == other.actor && cell == other.cell;
    }

    Bool_t Loaded_Actor_t::operator!=(const Loaded_Actor_t& other)
    {
        return !operator==(other);
    }

    Bool_t Loaded_Actor_t::Is_Valid()
    {
        return actor && cell && actor->Is_Valid() && cell->Is_Valid();
    }

    Loaded_Actor_t::operator Bool_t()
    {
        return Is_Valid();
    }

    /* Actor_t */

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
                    if (reference->form_type == kFormType_Character) {
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

}

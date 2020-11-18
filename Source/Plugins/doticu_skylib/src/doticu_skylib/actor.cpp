/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/utils.h"
#include "doticu_skylib/actor.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/worldspace.h"

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
            class Iterator_t : public Iterator_i<Reference_t*>
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
                        results.push_back(Loaded_Actor_t(static_cast<Actor_t*>(reference), cell));
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
            const char* name = actor->Name();
            if (!name || !name[0]) {
                name = actor->Base_Name();
            }
            _MESSAGE(TAB "index: %6zu", idx);
            _MESSAGE(TAB TAB "actor: %8.8X %s", actor->form_id, name);
            if (cell->Is_Interior()) {
                _MESSAGE(TAB TAB "interior cell: %8.8X %s", cell->form_id, cell->Get_Editor_ID());
            } else {
                Worldspace_t* worldspace = cell->worldspace;
                SKYLIB_ASSERT(worldspace);
                _MESSAGE(TAB TAB "exterior cell: %8.8X %s", cell->form_id, cell->Get_Editor_ID());
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

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cell.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/worldspace.h"

namespace doticu_skylib {

    Vector_t<Worldspace_t*> Worldspace_t::Worldspaces()
    {
        auto worldspaces = Game_t::Self()->Worldspaces();

        Vector_t<Worldspace_t*> results;
        results.reserve(worldspaces.count);

        for (Index_t idx = 0, end = worldspaces.count; idx < end; idx += 1) {
            results.push_back(worldspaces.entries[idx]);
        }

        return results;
    }

    Bool_t Worldspace_t::Can_Fast_Travel()
    {
        return !Cant_Fast_Travel();
    }

    Bool_t Worldspace_t::Cant_Fast_Travel()
    {
        return (worldspace_flags & Worldspace_Flags_e::CANT_FAST_TRAVEL) != 0;
    }

    void Worldspace_t::Log()
    {
        #define TAB "    "

        _MESSAGE("worldspace: %8.8X, %s", form_id, Get_Editor_ID());
        {
            _MESSAGE(TAB "xy_to_cell capacity: %u", xy_to_cell.capacity);
            for (Index_t idx = 0, end = xy_to_cell.capacity; idx < end; idx += 1) {
                Hash_Map_t<s16_yx, Cell_t*>::Entry_t& entry = xy_to_cell.entries[idx];
                if (entry.chain) {
                    if (entry.second) {
                        _MESSAGE(TAB TAB "x: %5.i, y: %5.i, cell: %8.8X, %s",
                                 entry.first.x, entry.first.y,
                                 entry.second->form_id, entry.second->Get_Editor_ID());
                    } else {
                        _MESSAGE(TAB TAB "x: %5.i, y: %5.i, empty", entry.first.x, entry.first.y);
                    }
                }
            }
        }
        {
            if (persistent_cell) {
                _MESSAGE(TAB "persistent_cell: %8.8X, %s", persistent_cell->form_id, persistent_cell->Get_Editor_ID());
            } else {
                _MESSAGE(TAB "persistent_cell: empty");
            }
        }
        {
            auto& cell_xy_to_filtered_form_ids = form_id_maps.cell_xy_to_filtered_form_ids;
            _MESSAGE(TAB "cell_xy_to_filtered_form_ids capacity: %u", cell_xy_to_filtered_form_ids.capacity);
            for (Index_t idx = 0, end = cell_xy_to_filtered_form_ids.capacity; idx < end; idx += 1) {
                auto& entry = cell_xy_to_filtered_form_ids.entries[idx];
                if (entry.chain) {
                    auto& cell_xy = entry.first;
                    auto& arr = entry.second;
                    if (arr) {
                        _MESSAGE(TAB TAB "x: %5.i, y: %5.i, count: %u", cell_xy.x, cell_xy.y, arr->count);
                        for (Index_t idx = 0, end = arr->count; idx < end; idx += 1) {
                            Form_ID_t form_id = arr->At(idx);
                            Form_t* form = Game_t::Form(form_id);
                            if (form) {
                                _MESSAGE(TAB TAB TAB "form_id: %8.8X, form_type: %2.2X, editor_id: %s",
                                         form_id, form->form_type, form->Get_Editor_ID());
                            } else {
                                _MESSAGE(TAB TAB TAB "form_id: %8.8X, unloaded", form_id);
                            }
                        }
                    } else {
                        _MESSAGE(TAB TAB "x: %5.i, y: %5.i, empty", cell_xy.x, cell_xy.y);
                    }
                }
            }
        }

        #undef TAB
    }

}

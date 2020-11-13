/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/utils.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/worldspace.h"

namespace doticu_skylib {

    size_t Cell_t::Interior_Cell_Count()
    {
        return reinterpret_cast<Small_Array_t<Cell_t*>&>(Game_t::Data()->cellList).count;
    }

    size_t Cell_t::Loaded_Exterior_Cell_Count()
    {
        auto worldspaces = reinterpret_cast<tArray<Worldspace_t*>&>(Game_t::Data()->arrWRLD);
        size_t exterior_cell_count = 0;
        for (Index_t idx = 0, end = worldspaces.count; idx < end; idx += 1) {
            Worldspace_t* worldspace = worldspaces.entries[idx];
            if (worldspace) {
                if (worldspace->persistent_cell) {
                    exterior_cell_count += 1;
                }
                if (worldspace->xy_to_cell.capacity > 0) {
                    exterior_cell_count += worldspace->xy_to_cell.capacity - worldspace->xy_to_cell.free_count;
                }
            }
        }
        return exterior_cell_count;
    }

    static void Interior_Cells(Vector_t<Cell_t*>& accumulator)
    {
        Small_Array_t<Cell_t*>& interior_cells = reinterpret_cast<Small_Array_t<Cell_t*>&>(Game_t::Data()->cellList);
        for (Index_t idx = 0, end = interior_cells.count; idx < end; idx += 1) {
            Cell_t* cell = interior_cells.entries[idx];
            if (cell) {
                accumulator.push_back(cell);
            }
        }
    }

    static void Loaded_Exterior_Cells(Vector_t<Cell_t*>& accumulator)
    {
        auto worldspaces = reinterpret_cast<tArray<Worldspace_t*>&>(Game_t::Data()->arrWRLD);
        for (Index_t idx = 0, end = worldspaces.count; idx < end; idx += 1) {
            Worldspace_t* worldspace = worldspaces.entries[idx];
            if (worldspace) {
                if (worldspace->persistent_cell) {
                    accumulator.push_back(worldspace->persistent_cell);
                }
                for (Index_t idx = 0, end = worldspace->xy_to_cell.capacity; idx < end; idx += 1) {
                    Hash_Map_t<Cell_XY_t, Cell_t*>::Entry_t& entry = worldspace->xy_to_cell.entries[idx];
                    if (entry.chain && entry.tuple.value) {
                        accumulator.push_back(entry.tuple.value);
                    }
                }
            }
        }
    }

    Vector_t<Cell_t*> Cell_t::Interior_Cells()
    {
        Vector_t<Cell_t*> results;
        results.reserve(Interior_Cell_Count());
        doticu_skylib::Interior_Cells(results);
        return results;
    }

    Vector_t<Cell_t*> Cell_t::Loaded_Exterior_Cells()
    {
        Vector_t<Cell_t*> results;
        results.reserve(Loaded_Exterior_Cell_Count());
        doticu_skylib::Loaded_Exterior_Cells(results);
        return results;
    }

    Vector_t<Cell_t*> Cell_t::Loaded_Cells()
    {
        Vector_t<Cell_t*> results;
        results.reserve(Interior_Cell_Count() + Loaded_Exterior_Cell_Count());
        doticu_skylib::Interior_Cells(results);
        doticu_skylib::Loaded_Exterior_Cells(results);
        return results;
    }

    Bool_t Cell_t::Is_Interior()
    {
        return (cell_flags & static_cast<Cell_Flags_t>(Cell_Flags_e::IS_INTERIOR)) != 0;
    }

    Bool_t Cell_t::Is_Exterior()
    {
        return (cell_flags & static_cast<Cell_Flags_t>(Cell_Flags_e::IS_INTERIOR)) == 0;
    }

    void Cell_t::References(Iterator_i<Reference_t*>& iterator)
    {
        for (Index_t idx = 0, end = references.capacity; idx < end; idx += 1) {
            Set_t<Reference_t*>::Entry_t& entry = references.entries[idx];
            if (entry.chain && entry.key) {
                iterator.operator()(entry.key);
            }
        }
    }

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/utils.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/worldspace.h"
#include "doticu_skylib/location.h"
#include "doticu_skylib/xdata.h"
#include "doticu_skylib/xlist.h"

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

    Location_t* Cell_t::Location()
    {
        xlist.Validate();

        if (xlist.Has<XLocation_t>()) {
            XLocation_t* xlocation = xlist.Get<XLocation_t>();
            if (xlocation->location) {
                return xlocation->location;
            } else if (worldspace) {
                return worldspace->location;
            } else {
                return nullptr;
            }
        } else if (worldspace) {
            return worldspace->location;
        } else {
            return nullptr;
        }
    }

    Vector_t<Location_t*> Cell_t::Locations()
    {
        Vector_t<Location_t*> locations;
        locations.reserve(8);

        xlist.Validate();

        Location_t* xlocation_location = nullptr;
        if (xlist.Has<XLocation_t>()) {
            XLocation_t* xlocation = xlist.Get<XLocation_t>();
            xlocation_location = xlocation->location;
        }
        for (Location_t* it = xlocation_location; it != nullptr; it = it->parent_location) {
            locations.push_back(it);
        }

        Location_t* worldspace_location =
            worldspace ? worldspace->location : nullptr;
        for (Location_t* it = worldspace_location; it != nullptr; it = it->parent_location) {
            locations.push_back(it);
        }

        return locations;
    }

    Vector_t<String_t> Cell_t::Location_Names()
    {
        Vector_t<String_t> results;
        results.reserve(8);
        Location_Names(results);
        return results;
    }

    void Cell_t::Location_Names(Vector_t<String_t>& results)
    {
        xlist.Validate();

        Location_t* xlocation_location = nullptr;
        if (xlist.Has<XLocation_t>()) {
            XLocation_t* xlocation = xlist.Get<XLocation_t>();
            xlocation_location = xlocation->location;
        }
        for (Location_t* it = xlocation_location; it != nullptr; it = it->parent_location) {
            results.push_back(it->Any_Name());
        }

        Location_t* worldspace_location =
            worldspace ? worldspace->location : nullptr;
        for (Location_t* it = worldspace_location; it != nullptr; it = it->parent_location) {
            results.push_back(it->Any_Name());
        }
    }

    String_t Cell_t::Any_Name()
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

    void Cell_t::References(Iterator_i<void, Reference_t*>& iterator)
    {
        for (Index_t idx = 0, end = references.capacity; idx < end; idx += 1) {
            Set_t<Reference_t*>::Entry_t& entry = references.entries[idx];
            if (entry.chain && entry.key) {
                iterator.operator()(entry.key);
            }
        }
    }

}

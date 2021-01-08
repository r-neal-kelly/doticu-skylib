/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/collections.h"
#include "doticu_skylib/interface.h"

#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/encounter_zone.h"
#include "doticu_skylib/faction.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/game_ini.h"
#include "doticu_skylib/location.h"
#include "doticu_skylib/player.h"
#include "doticu_skylib/worldspace.h"

#include "doticu_skylib/extra_encounter_zone.h"
#include "doticu_skylib/extra_list.inl"
#include "doticu_skylib/extra_location.h"
#include "doticu_skylib/extra_owner.h"

namespace doticu_skylib {

    size_t Cell_t::Interior_Cell_Count()
    {
        return Game_t::Self()->interior_cells.count;
    }

    size_t Cell_t::Loaded_Exterior_Cell_Count()
    {
        auto worldspaces = Game_t::Self()->Worldspaces();
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
        Short_Array_t<Cell_t*>& interior_cells = Game_t::Self()->interior_cells;
        for (Index_t idx = 0, end = interior_cells.count; idx < end; idx += 1) {
            Cell_t* cell = interior_cells.entries[idx];
            if (cell) {
                accumulator.push_back(cell);
            }
        }
    }

    static void Loaded_Exterior_Cells(Vector_t<Cell_t*>& accumulator)
    {
        auto worldspaces = Game_t::Self()->Worldspaces();
        for (Index_t idx = 0, end = worldspaces.count; idx < end; idx += 1) {
            Worldspace_t* worldspace = worldspaces.entries[idx];
            if (worldspace) {
                if (worldspace->persistent_cell) {
                    accumulator.push_back(worldspace->persistent_cell);
                }
                for (Index_t idx = 0, end = worldspace->xy_to_cell.capacity; idx < end; idx += 1) {
                    Hash_Map_t<s16_yx, Cell_t*>::Entry_t& entry = worldspace->xy_to_cell.entries[idx];
                    if (entry.chain && entry.second) {
                        accumulator.push_back(entry.second);
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

    Vector_t<some<Cell_t*>> Cell_t::Cells_In_Grid()
    {
        Vector_t<some<Cell_t*>> results;
        Cells_In_Grid(results);
        return results;
    }

    void Cell_t::Cells_In_Grid(Vector_t<some<Cell_t*>>& results)
    {
        // we can't make this static as apparently the ini model can be updated mid-game???
        const u64 grids_to_load = Game_INI_t::INI_u32("uGridsToLoad:General");
        const u64 grid_radius = grids_to_load ? grids_to_load / 2 : 2;

        results.reserve(grids_to_load * grids_to_load);

        Cell_t* player_cell = Player_t::Self()->Cell();
        if (player_cell && player_cell->Is_Valid()) {
            results.push_back(player_cell);
            if (player_cell->Is_Exterior()) {
                Exterior_Cell_t* exterior_cell = player_cell->cellterior.exterior;
                if (exterior_cell) {
                    Worldspace_t* worldspace = player_cell->worldspace;
                    if (worldspace && worldspace->Is_Valid()) {
                        const s16_yx origin = static_cast<s16_yx>(exterior_cell->cell_xy);
                        const s16 begin_x = origin.x - grid_radius;
                        const s16 end_x = origin.x + grid_radius + 1;
                        const s16 begin_y = origin.y - grid_radius;
                        const s16 end_y = origin.y + grid_radius + 1;
                        if (begin_x < end_x && begin_y < end_y) {
                            for (s16 idx_x = begin_x; idx_x < end_x; idx_x += 1) {
                                for (s16 idx_y = begin_y; idx_y < end_y; idx_y += 1) {
                                    s16_yx cell_yx(idx_y, idx_x);
                                    auto entry = worldspace->xy_to_cell.Entry(cell_yx);
                                    if (entry) {
                                        Cell_t* cell = entry->second;
                                        if (cell && cell->Is_Valid() && cell->Is_Attached() && !results.Has(cell)) {
                                            results.push_back(cell);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Bool_t Cell_t::Is_Interior()
    {
        return (cell_flags & Cell_Flags_e::IS_INTERIOR) != 0;
    }

    Bool_t Cell_t::Is_Exterior()
    {
        return (cell_flags & Cell_Flags_e::IS_INTERIOR) == 0;
    }

    Bool_t Cell_t::Is_Attached()
    {
        return cell_state == Cell_State_e::IS_ATTACHED;
    }

    Bool_t Cell_t::Can_Travel_From()
    {
        return (cell_flags & Cell_Flags_e::CAN_TRAVEL_FROM) != 0;
    }

    Bool_t Cell_t::Has_Reference(some<Reference_t*> reference)
    {
        SKYLIB_ASSERT_SOME(reference);

        return references.Has(reference());
    }

    maybe<Actor_Base_t*> Cell_t::Actor_Base_Owner(Bool_t do_check_locations)
    {
        maybe<Form_t*> owner = Owner(do_check_locations);
        if (owner && owner->form_type == Form_Type_e::ACTOR_BASE) {
            return static_cast<maybe<Actor_Base_t*>>(owner);
        } else {
            return nullptr;
        }
    }

    maybe<Encounter_Zone_t*> Cell_t::Encounter_Zone(Bool_t do_check_locations)
    {
        if (this->attached_cell && this->attached_cell->encounter_zone) {
            return this->attached_cell->encounter_zone;
        } else {
            maybe<Encounter_Zone_x*> xencounter_zone = this->xlist.Get<Encounter_Zone_x>();
            if (xencounter_zone && xencounter_zone->encounter_zone) {
                return xencounter_zone->encounter_zone;
            } else {
                maybe<Worldspace_t*> worldspace = Worldspace(do_check_locations);
                if (worldspace) {
                    return worldspace->encounter_zone;
                } else {
                    return nullptr;
                }
            }
        }
    }

    maybe<Faction_t*> Cell_t::Faction_Owner(Bool_t do_check_locations)
    {
        maybe<Form_t*> owner = Owner(do_check_locations);
        if (owner && owner->form_type == Form_Type_e::FACTION) {
            return static_cast<maybe<Faction_t*>>(owner);
        } else {
            return nullptr;
        }
    }

    Location_t* Cell_t::Location()
    {
        xlist.Validate();

        if (xlist.Has<Location_x>()) {
            Location_x* xlocation = xlist.Get<Location_x>();
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
        Locations(locations);
        return locations;
    }

    void Cell_t::Locations(Vector_t<Location_t*>& results)
    {
        results.reserve(8);

        xlist.Validate();

        Location_t* xlocation_location = nullptr;
        if (xlist.Has<Location_x>()) {
            Location_x* xlocation = xlist.Get<Location_x>();
            xlocation_location = xlocation->location;
        }
        for (Location_t* it = xlocation_location; it != nullptr; it = it->parent_location) {
            if (!results.Has(it)) {
                results.push_back(it);
            }
        }

        Location_t* worldspace_location =
            worldspace ? worldspace->location : nullptr;
        for (Location_t* it = worldspace_location; it != nullptr; it = it->parent_location) {
            if (!results.Has(it)) {
                results.push_back(it);
            }
        }
    }

    Vector_t<String_t> Cell_t::Location_Names()
    {
        Vector_t<String_t> results;
        Location_Names(results);
        return results;
    }

    void Cell_t::Location_Names(Vector_t<String_t>& results)
    {
        results.reserve(8);

        xlist.Validate();

        Location_t* xlocation_location = nullptr;
        if (xlist.Has<Location_x>()) {
            Location_x* xlocation = xlist.Get<Location_x>();
            xlocation_location = xlocation->location;
        }
        for (Location_t* it = xlocation_location; it != nullptr; it = it->parent_location) {
            String_t name = it->Any_Name();
            if (!results.Has(name)) {
                results.push_back(name);
            }
        }

        Location_t* worldspace_location =
            worldspace ? worldspace->location : nullptr;
        for (Location_t* it = worldspace_location; it != nullptr; it = it->parent_location) {
            String_t name = it->Any_Name();
            if (!results.Has(name)) {
                results.push_back(name);
            }
        }
    }

    maybe<Form_t*> Cell_t::Owner(Bool_t do_check_locations)
    {
        maybe<Owner_x*> xowner = this->xlist.Get<Owner_x>();
        if (xowner && xowner->owner) {
            return xowner->owner;
        } else {
            maybe<Encounter_Zone_t*> encounter_zone = Encounter_Zone(do_check_locations);
            if (encounter_zone) {
                return encounter_zone->owner;
            } else {
                return nullptr;
            }
        }
    }

    maybe<Worldspace_t*> Cell_t::Worldspace(Bool_t do_check_locations)
    {
        if (worldspace) {
            return worldspace;
        } else if (do_check_locations) {
            Array_t<Worldspace_t*>& worldspaces = Game_t::Self()->Worldspaces();

            Vector_t<Location_t*> locations = Locations();
            for (Index_t idx = 0, end = locations.size(); idx < end; idx += 1) {
                Location_t* location = locations[idx];
                if (location && location->Is_Valid()) {
                    for (Index_t idx = 0, end = worldspaces.count; idx < end; idx += 1) {
                        Worldspace_t* worldspace = worldspaces.entries[idx];
                        if (worldspace && worldspace->Is_Valid()) {
                            if (worldspace->Has_Location(location)) {
                                return worldspace;
                            }
                        }
                    }
                }
            }

            return nullptr;
        } else {
            return nullptr;
        }
    }

    Vector_t<some<Worldspace_t*>> Cell_t::Worldspaces()
    {
        Vector_t<some<Worldspace_t*>> worldspaces;
        Worldspaces(worldspaces);
        return std::move(worldspaces);
    }

    void Cell_t::Worldspaces(Vector_t<some<Worldspace_t*>>& results)
    {
        results.reserve(2);

        for (maybe<Worldspace_t*> it = Worldspace(); it; it = it->parent_worldspace) {
            if (!results.Has(it())) {
                results.push_back(it());
            }
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
            if (entry.chain && entry.first) {
                iterator.operator()(entry.first);
            }
        }
    }

}

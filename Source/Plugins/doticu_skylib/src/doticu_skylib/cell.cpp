/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/collections.h"
#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/encounter_zone.h"
#include "doticu_skylib/extra_encounter_zone.h"
#include "doticu_skylib/extra_list.inl"
#include "doticu_skylib/extra_location.h"
#include "doticu_skylib/extra_owner.h"
#include "doticu_skylib/faction.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/game_ini.h"
#include "doticu_skylib/interface.h"
#include "doticu_skylib/location.h"
#include "doticu_skylib/player.h"
#include "doticu_skylib/worldspace.h"

namespace doticu_skylib {

    Vector_t<some<Cell_t*>> Cell_t::Interior_Cells_Dynamic()
    {
        Vector_t<some<Cell_t*>> results;
        Interior_Cells_Dynamic(results);
        return results;
    }

    void Cell_t::Interior_Cells_Dynamic(Vector_t<some<Cell_t*>>& results)
    {
        class Iterator :
            public Iterator_i<some<Form_t*>>
        {
        public:
            Vector_t<some<Cell_t*>>& results;

        public:
            Iterator(Vector_t<some<Cell_t*>>& results) :
                results(results)
            {
            }

        public:
            virtual Iterator_e operator ()(some<Form_t*> form) override
            {
                maybe<Cell_t*> cell = form->As_Cell();
                if (cell && cell->Is_Valid() && cell->Is_Interior()) {
                    this->results.push_back(cell());
                }
                return Iterator_e::CONTINUE;
            }
        };

        results.reserve(1024);

        Iterator iterator(results);

        Game_t::Iterate_Forms(iterator);
    }

    Vector_t<some<Cell_t*>> Cell_t::Interior_Cells_Static()
    {
        Vector_t<some<Cell_t*>> results;
        Interior_Cells_Static(results);
        return results;
    }

    void Cell_t::Interior_Cells_Static(Vector_t<some<Cell_t*>>& results)
    {
        Short_Array_t<maybe<Cell_t*>>& interior_cells = Game_t::Self()->interior_cells;

        results.reserve(interior_cells.count);

        for (size_t idx = 0, end = interior_cells.count; idx < end; idx += 1) {
            maybe<Cell_t*> cell = interior_cells.entries[idx];
            if (cell && cell->Is_Valid() && !results.Has(cell())) {
                results.push_back(cell());
            }
        }
    }

    Vector_t<some<Cell_t*>> Cell_t::Exterior_Cells()
    {
        Vector_t<some<Cell_t*>> results;
        Exterior_Cells(results);
        return results;
    }

    void Cell_t::Exterior_Cells(Vector_t<some<Cell_t*>>& results)
    {
        class Iterator :
            public Iterator_i<some<Form_t*>>
        {
        public:
            Vector_t<some<Cell_t*>>& results;

        public:
            Iterator(Vector_t<some<Cell_t*>>& results) :
                results(results)
            {
            }

        public:
            virtual Iterator_e operator ()(some<Form_t*> form) override
            {
                maybe<Cell_t*> cell = form->As_Cell();
                if (cell && cell->Is_Valid() && cell->Is_Exterior()) {
                    this->results.push_back(cell());
                }
                return Iterator_e::CONTINUE;
            }
        };

        results.reserve(1024);

        Iterator iterator(results);

        Game_t::Iterate_Forms(iterator);
    }

    Vector_t<some<Cell_t*>> Cell_t::Grid_Cells()
    {
        Vector_t<some<Cell_t*>> results;
        Grid_Cells(results);
        return results;
    }

    void Cell_t::Grid_Cells(Vector_t<some<Cell_t*>>& results)
    {
        const u64 grids_to_load = Game_INI_t::INI_u32("uGridsToLoad:General");
        const u64 grid_radius = grids_to_load ? grids_to_load / 2 : 2;

        results.reserve(grids_to_load * grids_to_load);

        maybe<Cell_t*> player_cell = Player_t::Self()->Cell(true);
        if (player_cell && player_cell->Is_Valid()) {
            results.push_back(player_cell());
            if (player_cell->Is_Exterior()) {
                maybe<Exterior_Cell_t*> exterior_cell = player_cell->cellterior.exterior;
                if (exterior_cell) {
                    maybe<Worldspace_t*> worldspace = player_cell->worldspace;
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
                                    auto entry = worldspace->yx_to_cell.Entry(cell_yx);
                                    if (entry) {
                                        maybe<Cell_t*> cell = entry->second;
                                        if (cell && cell->Is_Valid() && cell->Is_Attached() && !results.Has(cell())) {
                                            results.push_back(cell());
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

    Vector_t<some<Cell_t*>> Cell_t::Attached_Cells()
    {
        Vector_t<some<Cell_t*>> results;
        Attached_Cells(results);
        return results;
    }

    void Cell_t::Attached_Cells(Vector_t<some<Cell_t*>>& results)
    {
        class Iterator :
            public Iterator_i<some<Form_t*>>
        {
        public:
            Vector_t<some<Cell_t*>>& results;

        public:
            Iterator(Vector_t<some<Cell_t*>>& results) :
                results(results)
            {
            }

        public:
            virtual Iterator_e operator ()(some<Form_t*> form) override
            {
                maybe<Cell_t*> cell = form->As_Cell();
                if (cell && cell->Is_Valid() && cell->Is_Attached()) {
                    this->results.push_back(cell());
                }
                return Iterator_e::CONTINUE;
            }
        };

        results.reserve(64);

        Iterator iterator(results);

        Game_t::Iterate_Forms(iterator);
    }

    Vector_t<some<Cell_t*>> Cell_t::All_Cells()
    {
        Vector_t<some<Cell_t*>> results;
        All_Cells(results);
        return results;
    }

    void Cell_t::All_Cells(Vector_t<some<Cell_t*>>& results)
    {
        class Iterator :
            public Iterator_i<some<Form_t*>>
        {
        public:
            Vector_t<some<Cell_t*>>& results;

        public:
            Iterator(Vector_t<some<Cell_t*>>& results) :
                results(results)
            {
            }

        public:
            virtual Iterator_e operator ()(some<Form_t*> form) override
            {
                maybe<Cell_t*> cell = form->As_Cell();
                if (cell && cell->Is_Valid()) {
                    this->results.push_back(cell());
                }
                return Iterator_e::CONTINUE;
            }
        };

        results.reserve(2048);

        Iterator iterator(results);

        Game_t::Iterate_Forms(iterator);
    }

    size_t Cell_t::Interior_Cell_Dynamic_Count()
    {
        return Interior_Cells_Dynamic().size();
    }

    size_t Cell_t::Interior_Cell_Static_Count()
    {
        return Interior_Cells_Static().size();
    }

    size_t Cell_t::Exterior_Cell_Count()
    {
        return Exterior_Cells().size();
    }

    Bool_t Cell_t::Is_Attached()
    {
        return this->cell_state == Cell_State_e::IS_ATTACHED;
    }

    Bool_t Cell_t::Is_Exterior()
    {
        return !Is_Interior();
    }

    Bool_t Cell_t::Is_Interior()
    {
        return this->cell_flags.Is_Flagged(Cell_Flags_e::IS_INTERIOR);
    }

    Bool_t Cell_t::Can_Travel_From()
    {
        return this->cell_flags.Is_Flagged(Cell_Flags_e::CAN_TRAVEL_FROM);
    }

    Bool_t Cell_t::Has_Reference(some<Reference_t*> reference)
    {
        SKYLIB_ASSERT_SOME(reference);

        return references.Has(reference());
    }

    maybe<Encounter_Zone_t*> Cell_t::Encounter_Zone(Bool_t do_check_locations)
    {
        if (this->attached_cell && this->attached_cell->encounter_zone) {
            return this->attached_cell->encounter_zone;
        } else {
            maybe<Extra_Encounter_Zone_t*> xencounter_zone = this->x_list.Get<Extra_Encounter_Zone_t>();
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

    maybe<Location_t*> Cell_t::Location()
    {
        maybe<Location_t*> this_location = This_Location();
        if (this_location) {
            return this_location;
        } else {
            return Worldspace_Location();
        }
    }

    maybe<Location_t*> Cell_t::This_Location()
    {
        maybe<Extra_Location_t*> x_location = this->x_list.Get<Extra_Location_t>();
        if (x_location) {
            return x_location->location;
        } else {
            return none<Location_t*>();
        }
    }

    maybe<Location_t*> Cell_t::Worldspace_Location()
    {
        if (this->worldspace) {
            return this->worldspace->Location();
        } else {
            return none<Location_t*>();
        }
    }

    Vector_t<some<Location_t*>> Cell_t::Locations()
    {
        Vector_t<some<Location_t*>> locations;
        Locations(locations);
        return locations;
    }

    void Cell_t::Locations(Vector_t<some<Location_t*>>& results)
    {
        results.reserve(8);

        this->x_list.Validate();
        maybe<Extra_Location_t*> x_location = this->x_list.Get<Extra_Location_t>();
        if (x_location && x_location->location) {
            if (!results.Has(x_location->location())) {
                results.push_back(x_location->location());
            }
            x_location->location->Parents(results);
        }

        maybe<Location_t*> worldspace_location = Worldspace_Location();
        if (worldspace_location) {
            if (!results.Has(worldspace_location())) {
                results.push_back(worldspace_location());
            }
            worldspace_location->Parents(results);
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
        Vector_t<some<Location_t*>> locations = Locations();

        size_t location_count = locations.size();
        results.reserve(location_count);

        for (size_t idx = 0, end = location_count; idx < end; idx += 1) {
            String_t name = locations[idx]->Any_Name();
            if (!results.Has(name)) {
                results.push_back(name);
            }
        }
    }

    Form_Owner_t Cell_t::Owner(Bool_t do_check_locations)
    {
        maybe<Form_Owner_t> owner = this->x_list.Owner();
        if (owner.Has_Value()) {
            return owner.Value();
        } else {
            maybe<Encounter_Zone_t*> encounter_zone = Encounter_Zone(do_check_locations);
            if (encounter_zone) {
                return encounter_zone->owner;
            } else {
                return none<Form_t*>();
            }
        }
    }

    maybe<Actor_Base_t*> Cell_t::Actor_Base_Owner(Bool_t do_check_locations)
    {
        return Owner(do_check_locations).As_Actor_Base();
    }

    maybe<Faction_t*> Cell_t::Faction_Owner(Bool_t do_check_locations)
    {
        return Owner(do_check_locations).As_Faction();
    }

    maybe<Worldspace_t*> Cell_t::Worldspace(Bool_t do_search)
    {
        if (this->worldspace) {
            return this->worldspace;
        } else if (do_search && Is_Exterior()) {
            Array_t<maybe<Worldspace_t*>>& worldspaces = Game_t::Self()->Worldspaces();
            for (size_t idx = 0, end = worldspaces.Count(); idx < end; idx += 1) {
                maybe<Worldspace_t*> worldspace = worldspaces[idx];
                if (worldspace && worldspace->Has_Cell(this)) {
                    return worldspace;
                }
            }
            return none<Worldspace_t*>();
        } else {
            return none<Worldspace_t*>();
        }
    }

    Vector_t<some<Worldspace_t*>> Cell_t::Worldspaces()
    {
        Vector_t<some<Worldspace_t*>> results;
        Worldspaces(results);
        return results;
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

    void Cell_t::Iterate_References(Iterator_i<some<Reference_t*>>& iterator)
    {
        for (size_t idx = 0, end = this->references.capacity; idx < end; idx += 1) {
            Set_t<maybe<Reference_t*>>::Entry_t& entry = this->references.entries[idx];
            if (entry.chain && entry.first) {
                if (iterator(entry.first()) == Iterator_e::BREAK) {
                    return;
                }
            }
        }
    }

    void Cell_t::Log_Locations(std::string indent)
    {
        SKYLIB_LOG(indent + "Cell_t::Log_Locations");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "is_interior: %s", Is_Interior() ? "true" : "false");

        maybe<Location_t*> this_location = This_Location();
        if (this_location) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "this_location:");
            this_location->Log_Name_And_Type(indent + SKYLIB_TAB + SKYLIB_TAB);
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "this_location: (none)");
        }

        maybe<Location_t*> worldspace_location = Worldspace_Location();
        if (worldspace_location) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "worldspace_location:");
            worldspace_location->Log_Name_And_Type(indent + SKYLIB_TAB + SKYLIB_TAB);
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "worldspace_location: (none)");
        }

        SKYLIB_LOG(indent + SKYLIB_TAB + "has both locations: %s", this_location && worldspace_location ? "true" : "false");

        SKYLIB_LOG(indent + "}");
    }

}

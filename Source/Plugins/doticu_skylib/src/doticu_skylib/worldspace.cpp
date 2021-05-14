/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/atomic_number.inl"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/game.h"
#include "doticu_skylib/location.h"
#include "doticu_skylib/worldspace.h"

namespace doticu_skylib {

    Vector_t<some<Worldspace_t*>> Worldspace_t::Worldspaces_Dynamic()
    {
        Vector_t<some<Worldspace_t*>> results;
        Worldspaces_Dynamic(results);
        return results;
    }

    void Worldspace_t::Worldspaces_Dynamic(Vector_t<some<Worldspace_t*>>& results)
    {
        class Iterator :
            public Iterator_i<some<Form_t*>>
        {
        public:
            Vector_t<some<Worldspace_t*>>& results;

        public:
            Iterator(Vector_t<some<Worldspace_t*>>& results) :
                results(results)
            {
            }

        public:
            virtual Iterator_e operator ()(some<Form_t*> form) override
            {
                maybe<Worldspace_t*> worldspace = form->As_Worldspace();
                if (worldspace && worldspace->Is_Valid()) {
                    this->results.push_back(worldspace());
                }
                return Iterator_e::CONTINUE;
            }
        };

        results.reserve(128);

        Iterator iterator(results);

        Game_t::Iterate_Forms(iterator);
    }

    Vector_t<some<Worldspace_t*>> Worldspace_t::Worldspaces_Static()
    {
        Vector_t<some<Worldspace_t*>> results;
        Worldspaces_Static(results);
        return results;
    }

    void Worldspace_t::Worldspaces_Static(Vector_t<some<Worldspace_t*>>& results)
    {
        Array_t<maybe<Worldspace_t*>>& worldspaces = Game_t::Self()->Worldspaces();

        size_t worldspace_count = worldspaces.Count();
        results.reserve(worldspace_count);

        for (size_t idx = 0, end = worldspace_count; idx < end; idx += 1) {
            maybe<Worldspace_t*> worldspace = worldspaces[idx];
            if (worldspace && worldspace->Is_Valid() && !results.Has(worldspace())) {
                results.push_back(worldspace());
            }
        }
    }

    Bool_t Worldspace_t::Can_Fast_Travel()
    {
    return !Cant_Fast_Travel();
    }

    Bool_t Worldspace_t::Cant_Fast_Travel()
    {
        return this->worldspace_flags.Is_Flagged(Worldspace_Flags_e::CANT_FAST_TRAVEL);
    }

    Bool_t Worldspace_t::Has_Location(some<Location_t*> location)
    {
        SKYLIB_ASSERT_SOME(location);

        if (this->location == location()) {
            return true;
        } else {
            return form_ids_to_locations.Has(location->form_id);
        }
    }

    Bool_t Worldspace_t::Has_Cell(some<Cell_t*> cell)
    {
        SKYLIB_ASSERT_SOME(cell);

        if (cell == this->persistent_cell) {
            return true;
        } else if (cell->Is_Exterior() && cell->cellterior.exterior) {
            s16_yx yx = static_cast<s16_yx>(cell->cellterior.exterior->cell_xy);
            maybe<Hash_Map_t<s16_yx, maybe<Cell_t*>>::Entry_t*> entry = this->yx_to_cell.Entry(yx);
            return entry && entry->second == cell;
        } else {
            return false;
        }
    }

    String_t Worldspace_t::Any_Name()
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

    maybe<Location_t*> Worldspace_t::Location()
    {
        if (this->location) {
            return this->location;
        } else {
            for (maybe<Worldspace_t*> parent = this->parent_worldspace; parent; parent = parent->parent_worldspace) {
                if (parent->location) {
                    return parent->location;
                }
            }
            return none<Location_t*>();
        }
    }

    Vector_t<some<Worldspace_t*>> Worldspace_t::Parents()
    {
        Vector_t<some<Worldspace_t*>> results;
        Parents(results);
        return results;
    }

    void Worldspace_t::Parents(Vector_t<some<Worldspace_t*>>& results)
    {
        for (maybe<Worldspace_t*> parent = this->parent_worldspace; parent; parent = parent->parent_worldspace) {
            if (!results.Has(parent())) {
                results.push_back(parent());
            }
        }
    }

    Vector_t<some<Location_t*>> Worldspace_t::Child_Locations()
    {
        Vector_t<some<Location_t*>> results;
        Child_Locations(results);
        return results;
    }

    void Worldspace_t::Child_Locations(Vector_t<some<Location_t*>>& results)
    {
        results.reserve(results.size() + 4);

        for (size_t idx = 0, end = form_ids_to_locations.capacity; idx < end; idx += 1) {
            Hash_Map_t<Form_ID_t, maybe<Location_t*>>::Entry_t& entry = form_ids_to_locations.entries[idx];
            if (entry.chain && entry.second && !results.Has(entry.second())) {
                results.push_back(entry.second());
            }
        }
    }

    Vector_t<some<Location_t*>> Worldspace_t::Location_And_Child_Locations()
    {
        Vector_t<some<Location_t*>> results;
        Location_And_Child_Locations(results);
        return results;
    }

    void Worldspace_t::Location_And_Child_Locations(Vector_t<some<Location_t*>>& results)
    {
        if (this->location && !results.Has(this->location())) {
            results.push_back(this->location());
        }
        Child_Locations(results);
    }

    Vector_t<some<Location_t*>> Worldspace_t::Linear_Parent_Locations()
    {
        Vector_t<some<Location_t*>> results;
        Linear_Parent_Locations(results);
        return results;
    }

    void Worldspace_t::Linear_Parent_Locations(Vector_t<some<Location_t*>>& results)
    {
        for (maybe<Worldspace_t*> parent = this->parent_worldspace; parent; parent = parent->parent_worldspace) {
            if (!results.Has(parent->location())) {
                results.push_back(parent->location());
            }
        }
    }

    Vector_t<some<Location_t*>> Worldspace_t::Location_And_Linear_Parent_Locations()
    {
        Vector_t<some<Location_t*>> results;
        Location_And_Linear_Parent_Locations(results);
        return results;
    }

    void Worldspace_t::Location_And_Linear_Parent_Locations(Vector_t<some<Location_t*>>& results)
    {
        if (this->location && !results.Has(this->location())) {
            results.push_back(this->location());
        }
        Linear_Parent_Locations(results);
    }

    void Worldspace_t::Log()
    {
        #define TAB "    "

        SKYLIB_LOG("worldspace: %8.8X, %s", form_id, Get_Editor_ID());
        {
            SKYLIB_LOG(TAB "yx_to_cell capacity: %u", yx_to_cell.capacity);
            for (size_t idx = 0, end = yx_to_cell.capacity; idx < end; idx += 1) {
                Hash_Map_t<s16_yx, maybe<Cell_t*>>::Entry_t& entry = yx_to_cell.entries[idx];
                if (entry.chain) {
                    if (entry.second) {
                        SKYLIB_LOG(TAB TAB "x: %5.i, y: %5.i, cell: %8.8X, %s",
                                   entry.first.x, entry.first.y,
                                   entry.second->form_id, entry.second->Get_Editor_ID());
                    } else {
                        SKYLIB_LOG(TAB TAB "x: %5.i, y: %5.i, empty", entry.first.x, entry.first.y);
                    }
                }
            }
        }
        {
            if (persistent_cell) {
                SKYLIB_LOG(TAB "persistent_cell: %8.8X, %s", persistent_cell->form_id, persistent_cell->Get_Editor_ID());
            } else {
                SKYLIB_LOG(TAB "persistent_cell: empty");
            }
        }
        {
            auto& cell_xy_to_filtered_form_ids = form_id_maps.cell_xy_to_filtered_form_ids;
            SKYLIB_LOG(TAB "cell_xy_to_filtered_form_ids capacity: %u", cell_xy_to_filtered_form_ids.capacity);
            for (size_t idx = 0, end = cell_xy_to_filtered_form_ids.capacity; idx < end; idx += 1) {
                auto& entry = cell_xy_to_filtered_form_ids.entries[idx];
                if (entry.chain) {
                    auto& cell_xy = entry.first;
                    auto& arr = entry.second;
                    if (arr) {
                        SKYLIB_LOG(TAB TAB "x: %5.i, y: %5.i, count: %u", cell_xy.x, cell_xy.y, arr->count);
                        for (size_t idx = 0, end = arr->count; idx < end; idx += 1) {
                            Form_ID_t form_id = arr->At(idx);
                            maybe<Form_t*> form = Game_t::Form(form_id);
                            if (form) {
                                SKYLIB_LOG(TAB TAB TAB "form_id: %8.8X, form_type: %2.2X, editor_id: %s",
                                           form_id, form->form_type, form->Get_Editor_ID());
                            } else {
                                SKYLIB_LOG(TAB TAB TAB "form_id: %8.8X, unloaded", form_id);
                            }
                        }
                    } else {
                        SKYLIB_LOG(TAB TAB "x: %5.i, y: %5.i, empty", cell_xy.x, cell_xy.y);
                    }
                }
            }
        }

        #undef TAB
    }

}

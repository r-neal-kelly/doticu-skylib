/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/math.h"

#include "doticu_skylib/alias_base.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/form_factory.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/location.h"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/script.h"
#include "doticu_skylib/worldspace.h"

#include "doticu_skylib/extra_aliases.h"
#include "doticu_skylib/extra_list.inl"

#include "doticu_skylib/virtual_machine.h"

namespace doticu_skylib {

    static maybe<Worldspace_t*> Worldspace_Impl(some<Reference_t*> self)
    {
        static auto get_worldspace = reinterpret_cast
            <Worldspace_t * (*)(Reference_t*)>
            (Game_t::Base_Address() + Reference_t::Offset_e::GET_WORLDSPACE);

        SKYLIB_ASSERT_SOME(self);
        return get_worldspace(self());
    }

    class Loaded_Reference_Iterator_t : public Iterator_i<void, Reference_t*>
    {
    public:
        Vector_t<some<Reference_t*>>& results;
        Filter_i<some<Reference_t*>>* filter;
        Loaded_Reference_Iterator_t(Vector_t<some<Reference_t*>>& results, Filter_i<some<Reference_t*>>* filter) :
            results(results), filter(filter)
        {
        }
        void operator()(Reference_t* reference)
        {
            if (reference && reference->Is_Valid() && !results.Has(reference)) {
                if (!filter || (*filter)(reference)) {
                    results.push_back(reference);
                }
            }
        }

    };

    Vector_t<some<Reference_t*>> Reference_t::Loaded_References(Filter_i<some<Reference_t*>>* filter)
    {
        Vector_t<some<Reference_t*>> results;
        Loaded_References(results, filter);
        return results;
    }

    void Reference_t::Loaded_References(Vector_t<some<Reference_t*>>& results, Filter_i<some<Reference_t*>>* filter)
    {
        Loaded_Reference_Iterator_t iterator(results, filter);

        results.reserve(2048);

        Vector_t<Cell_t*> loaded_cells = Cell_t::Loaded_Cells();
        for (Index_t idx = 0, end = loaded_cells.size(); idx < end; idx += 1) {
            Cell_t* cell = loaded_cells[idx];
            if (cell && cell->Is_Valid()) {
                cell->References(iterator);
            }
        }
    }

    Vector_t<some<Reference_t*>> Reference_t::Loaded_Grid_References(Filter_i<some<Reference_t*>>* filter)
    {
        Vector_t<some<Reference_t*>> results;
        Loaded_Grid_References(results, filter);
        return results;
    }

    void Reference_t::Loaded_Grid_References(Vector_t<some<Reference_t*>>& results, Filter_i<some<Reference_t*>>* filter)
    {
        Loaded_Reference_Iterator_t iterator(results, filter);

        results.reserve(2048);

        Vector_t<some<Cell_t*>> cells_in_grid = Cell_t::Cells_In_Grid();
        for (Index_t idx = 0, end = cells_in_grid.size(); idx < end; idx += 1) {
            cells_in_grid[idx]->References(iterator);
        }
    }

    Reference_t* Reference_t::Create(some<Form_t*> base, u32 count, some<Reference_t*> at, Bool_t force_persist, Bool_t initially_disable)
    {
        SKYLIB_ASSERT_SOME(base);
        SKYLIB_ASSERT_SOME(at);

        static auto place_at_me = reinterpret_cast
            <Reference_t*(*)(Virtual::Machine_t*, Virtual::Stack_ID_t, Reference_t*, Form_t*, u32, Bool_t, Bool_t)>
            (Game_t::Base_Address() + Offset_e::PLACE_AT_ME);

        return place_at_me(Virtual::Machine_t::Self(), 0, at(), base(), count, force_persist, initially_disable);
    }

    Reference_t* Reference_t::From_Handle(Reference_Handle_t reference_handle)
    {
        static auto lookup_reference_handle_1 = reinterpret_cast
            <Bool_t(*)(Reference_Handle_t&, Reference_t*&)>
            (Game_t::Base_Address() + Offset_e::LOOKUP_REFERENCE_HANDLE_1);

        Reference_t* reference = nullptr;
        lookup_reference_handle_1(reference_handle, reference);
        return reference;
    }

    Reference_Handle_t Reference_t::Invalid_Handle()
    {
        static auto invalid_reference_handle = reinterpret_cast
            <Reference_Handle_t*>
            (Game_t::Base_Address() + Offset_e::INVALID_REFERENCE_HANDLE);

        return *invalid_reference_handle;
    }

    Bool_t Reference_t::Is_Enabled()
    {
        return !Is_Disabled();
    }

    Bool_t Reference_t::Is_Disabled()
    {
        return (form_flags & Form_Flags_e::IS_DISABLED) != 0;
    }

    Bool_t Reference_t::Is_Persistent()
    {
        return (form_flags & Form_Flags_e::IS_PERSISTENT) != 0;
    }

    Bool_t Reference_t::Is_Temporary()
    {
        return !Is_Persistent();
    }

    Bool_t Reference_t::Is_Aliased(some<Quest_t*> quest, Alias_ID_t alias_id)
    {
        SKYLIB_ASSERT_SOME(quest);

        Aliases_x* xaliases = xlist.Get<Aliases_x>();
        if (xaliases) {
            Read_Locker_t locker(xaliases->lock);
            for (Index_t idx = 0, end = xaliases->instances.count; idx < end; idx += 1) {
                Aliases_x::Instance_t* instance = xaliases->instances.entries[idx];
                if (instance && instance->quest == quest() && instance->alias_base && instance->alias_base->id == alias_id) {
                    return true;
                }
            }
            return false;
        } else {
            return false;
        }
    }

    const char* Reference_t::Name()
    {
        static auto get_name = reinterpret_cast
            <const char*(*)(Reference_t*)>
            (Game_t::Base_Address() + static_cast<Word_t>(Offset_e::GET_NAME));
        return get_name(this);
    }

    String_t Reference_t::Any_Name()
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

    Cell_t* Reference_t::Cell(Bool_t do_check_worldspace)
    {
        if (parent_cell) {
            return parent_cell;
        } else if (do_check_worldspace) {
            maybe<Worldspace_t*> worldspace = Worldspace_Impl(this);
            if (worldspace) {
                return worldspace->persistent_cell;
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    Location_t* Reference_t::Location()
    {
        Cell_t* cell = Cell(true);
        if (cell) {
            return cell->Location();
        } else {
            return nullptr;
        }
    }

    maybe<Worldspace_t*> Reference_t::Worldspace(Bool_t do_check_locations)
    {
        maybe<Worldspace_t*> worldspace = Worldspace_Impl(this);
        if (worldspace) {
            return worldspace;
        } else if (parent_cell) {
            return parent_cell->Worldspace(do_check_locations);
        } else {
            return nullptr;
        }
    }

    Vector_t<Location_t*> Reference_t::Locations()
    {
        Vector_t<Location_t*> results;
        Locations(results);
        return results;
    }

    void Reference_t::Locations(Vector_t<Location_t*>& results)
    {
        Cell_t* cell = Cell();
        if (cell && cell->Is_Valid()) {
            cell->Locations(results);
        }
    }

    Vector_t<Quest_t*> Reference_t::Quests()
    {
        Vector_t<Quest_t*> results;
        Quests(results);
        return results;
    }

    void Reference_t::Quests(Vector_t<Quest_t*>& results)
    {
        Aliases_x* xaliases = xlist.Get<Aliases_x>();
        if (xaliases) {
            Read_Locker_t locker(xaliases->lock);
            results.reserve(xaliases->instances.count);
            for (Index_t idx = 0, end = xaliases->instances.count; idx < end; idx += 1) {
                Aliases_x::Instance_t* instance = xaliases->instances.entries[idx];
                if (instance && instance->quest && instance->quest->Is_Valid() && instance->alias_base) {
                    results.push_back(instance->quest);
                }
            }
        }
    }

    Vector_t<some<Worldspace_t*>> Reference_t::Worldspaces()
    {
        Vector_t<some<Worldspace_t*>> worldspaces;
        Worldspaces(worldspaces);
        return std::move(worldspaces);
    }

    void Reference_t::Worldspaces(Vector_t<some<Worldspace_t*>>& results)
    {
        results.reserve(2);

        for (maybe<Worldspace_t*> it = Worldspace(); it; it = it->parent_worldspace) {
            if (!results.Has(it())) {
                results.push_back(it());
            }
        }
    }

    Reference_Handle_t Reference_t::To_Handle()
    {
        static auto create_reference_handle = reinterpret_cast
            <void(*)(Reference_Handle_t&, Reference_t*)>
            (Game_t::Base_Address() + Offset_e::CREATE_REFERENCE_HANDLE);

        Reference_Handle_t handle = Invalid_Handle();
        if (Is_Valid() && Reference_Count() > 0) {
            create_reference_handle(handle, this);
        }
        return handle;
    }

    Float_t Reference_t::Distance_Between(some<Reference_t*> other)
    {
        SKYLIB_ASSERT_SOME(other);

        if (this->parent_cell && other->parent_cell) {
            if (this->parent_cell == other->parent_cell ||
                (this->parent_cell->Is_Exterior() &&
                 other->parent_cell->Is_Exterior() &&
                 Worldspace_Impl(this) == Worldspace_Impl(other))) {
                Float_t x_distance;
                if (this->position.x > other->position.x) {
                    x_distance = this->position.x - other->position.x;
                } else {
                    x_distance = other->position.x - this->position.x;
                }

                Float_t y_distance;
                if (this->position.y > other->position.y) {
                    y_distance = this->position.y - other->position.y;
                } else {
                    y_distance = other->position.y - this->position.y;
                }

                Float_t z_distance;
                if (this->position.z > other->position.z) {
                    z_distance = this->position.z - other->position.z;
                } else {
                    z_distance = other->position.z - this->position.z;
                }

                return sqrt(pow(x_distance, 2) + pow(y_distance, 2) + pow(z_distance, 2));
            } else {
                return std::numeric_limits<Float_t>::max();
            }
        } else {
            return std::numeric_limits<Float_t>::max();
        }
    }

    void Reference_t::Move_To_Offset(some<Reference_t*> target,
                                     maybe<Cell_t*> target_cell,
                                     maybe<Worldspace_t*> target_worldspace,
                                     f32_xyz& offset,
                                     f32_xyz& rotation)
    {
        static auto move_to_offset = reinterpret_cast
            <void(*)(Reference_t*, Reference_Handle_t&, Cell_t*, Worldspace_t*, f32_xyz&, f32_xyz&)>
            (Game_t::Base_Address() + Offset_e::MOVE_TO_OFFSET);

        SKYLIB_ASSERT_SOME(target);

        if (Is_Valid() && target->Is_Valid()) {
            Reference_Handle_t target_handle = target->To_Handle();
            if (target_handle != Reference_t::Invalid_Handle()) {
                move_to_offset(this, target_handle, target_cell(), target_worldspace(), offset, rotation);
            }
        }
    }

    void Reference_t::Move_To_Offset(some<Reference_t*> target, f32_xyz& offset, f32_xyz& rotation)
    {
        SKYLIB_ASSERT_SOME(target);

        if (Is_Valid() && target->Is_Valid()) {
            Move_To_Offset(target, target->Cell(false), target->Worldspace(false), offset, rotation);
        }
    }

    void Reference_t::Move_To_Orbit(some<Reference_t*> origin, Float_t radius, Float_t degree)
    {
        SKYLIB_ASSERT_SOME(origin);

        if (Is_Valid() && origin->Is_Valid()) {
            Float_t radians = origin->rotation.z - To_Radians(degree);

            f32_xyz offset;
            offset.x = origin->position.x + radius * sin(radians);
            offset.y = origin->position.y + radius * cos(radians);
            offset.z = origin->position.z;

            f32_xyz rotation;
            rotation.x = 0.0f;
            rotation.y = 0.0f;
            rotation.z = origin->rotation.z + To_Radians(180.0f - degree);

            Move_To_Offset(origin, offset, rotation);
        }
    }

    void Reference_t::Select_In_Console()
    {
        Form_Factory_i* script_factory = Form_Factory_i::Form_Factory(Form_Type_e::SCRIPT);

        if (Is_Valid()) {
            Script_t* script = static_cast<Script_t*>(script_factory->Create());
            if (script) {
                script->Command((std::string("prid ") + Form_ID_String().data).c_str());
                script->Execute(this);
                delete script;
            }
        }
    }

    void Reference_t::Enable()
    {
        Form_Factory_i* script_factory = Form_Factory_i::Form_Factory(Form_Type_e::SCRIPT);

        if (Is_Valid()) {
            Script_t* script = static_cast<Script_t*>(script_factory->Create());
            if (script) {
                script->Command("Enable");
                script->Execute(this);
                delete script;
            }
        }
    }

    void Reference_t::Disable()
    {
        Form_Factory_i* script_factory = Form_Factory_i::Form_Factory(Form_Type_e::SCRIPT);

        if (Is_Valid()) {
            Script_t* script = static_cast<Script_t*>(script_factory->Create());
            if (script) {
                script->Command("Disable");
                script->Execute(this);
                delete script;
            }
        }
    }

    void Reference_t::Mark_For_Delete(Bool_t do_disable)
    {
        Form_Factory_i* script_factory = Form_Factory_i::Form_Factory(Form_Type_e::SCRIPT);

        if (Is_Valid()) {
            Script_t* script = static_cast<Script_t*>(script_factory->Create());
            if (script) {
                if (do_disable) {
                    script->Command("Disable");
                    script->Execute(this);
                }
                if (Is_Persistent()) {
                    script->Command("MarkForDelete");
                    script->Execute(this);
                }
                delete script;
            }
        }
    }

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/alias_base.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/component_container.h"
#include "doticu_skylib/dialogue_manager.h"
#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/extra_aliases.h"
#include "doticu_skylib/extra_container_changes.h"
#include "doticu_skylib/extra_list.inl"
#include "doticu_skylib/faction.h"
#include "doticu_skylib/form_factory.h"
#include "doticu_skylib/form_list.h"
#include "doticu_skylib/game.inl"
#include "doticu_skylib/havok_actor_rigid_body_controller.h"
#include "doticu_skylib/havok_actor_rigid_body_base.h"
#include "doticu_skylib/havok_rigid_body.h"
#include "doticu_skylib/havok_rigid_body_base.h"
#include "doticu_skylib/location.h"
#include "doticu_skylib/math.h"
#include "doticu_skylib/ni_3d.h"
#include "doticu_skylib/ni_collidable.h"
#include "doticu_skylib/ni_node.h"
#include "doticu_skylib/player.h"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/reference_attached_state.h"
#include "doticu_skylib/scrap_array.inl"
#include "doticu_skylib/script.h"
#include "doticu_skylib/virtual_arguments.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_debug.h"
#include "doticu_skylib/virtual_game.h"
#include "doticu_skylib/virtual_input.h"
#include "doticu_skylib/virtual_machine.inl"
#include "doticu_skylib/virtual_utility.h"
#include "doticu_skylib/virtual_variable.inl"
#include "doticu_skylib/worldspace.h"

namespace doticu_skylib {

    static maybe<Worldspace_t*> Worldspace_Impl(some<Reference_t*> self)
    {
        static auto get_worldspace = reinterpret_cast
            <Worldspace_t * (*)(Reference_t*)>
            (Game_t::Base_Address() + Reference_t::Offset_e::GET_WORLDSPACE);

        SKYLIB_ASSERT_SOME(self);
        return get_worldspace(self());
    }

    template <typename Results_t>
    class Loaded_Reference_Iterator_t : public Iterator_i<void, Reference_t*>
    {
    public:
    };

    template <>
    class Loaded_Reference_Iterator_t<Vector_t<some<Reference_t*>>&> : public Iterator_i<void, Reference_t*>
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

    template <>
    class Loaded_Reference_Iterator_t<some<Form_List_t*>> : public Iterator_i<void, Reference_t*>
    {
    public:
        some<Form_List_t*> results;
        Filter_i<some<Reference_t*>>* filter;
        Loaded_Reference_Iterator_t(some<Form_List_t*> results, Filter_i<some<Reference_t*>>* filter) :
            results(results), filter(filter)
        {
        }
        void operator()(Reference_t* reference)
        {
            if (reference && reference->Is_Valid()) {
                if (!filter || (*filter)(reference)) {
                    results->Add_Form(reference);
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
        Loaded_Reference_Iterator_t<Vector_t<some<Reference_t*>>&> iterator(results, filter);

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
        Loaded_Reference_Iterator_t<Vector_t<some<Reference_t*>>&> iterator(results, filter);

        results.reserve(2048);

        Vector_t<some<Cell_t*>> cells_in_grid = Cell_t::Cells_In_Grid();
        for (Index_t idx = 0, end = cells_in_grid.size(); idx < end; idx += 1) {
            cells_in_grid[idx]->References(iterator);
        }
    }

    void Reference_t::Loaded_Grid_References(some<Form_List_t*> results, Filter_i<some<Reference_t*>>* filter)
    {
        SKYLIB_ASSERT_SOME(results);

        Loaded_Reference_Iterator_t<some<Form_List_t*>> iterator(results, filter);

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
            <Reference_t*(*)(Virtual::Machine_t*, Virtual::Raw_Stack_ID_t, Reference_t*, Form_t*, u32, Bool_t, Bool_t)>
            (Game_t::Base_Address() + Offset_e::PLACE_AT_ME);

        return place_at_me(Virtual::Machine_t::Self()(), 0, at(), base(), count, force_persist, initially_disable);
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

    Bool_t  Reference_t::Is_Based_On_Actor_Base()           { return this->base_form && this->base_form->Is_Actor_Base(); }
    Bool_t  Reference_t::Is_Based_On_Component_Container()  { return this->base_form && this->base_form->Is_Component_Container(); }
    Bool_t  Reference_t::Is_Based_On_Container()            { return this->base_form && this->base_form->Is_Container(); }

    Bool_t Reference_t::Is_Alive()
    {
        return !Is_Dead();
    }

    Bool_t Reference_t::Is_Dead()
    {
        return Get_Is_Dead(true);
    }

    Bool_t Reference_t::Is_Deleted()
    {
        return (form_flags & Form_Flags_e::IS_DELETED) != 0;
    }

    Bool_t Reference_t::Isnt_Deleted()
    {
        return !Is_Deleted();
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

    Bool_t Reference_t::Is_Attached()
    {
        return this->attached_state != none<Reference_Attached_State_t*>();
    }

    Bool_t Reference_t::Is_Detached()
    {
        return !Is_Attached();
    }

    Bool_t Reference_t::Is_In_Dialogue_With_Player()
    {
        return this == Dialogue_Manager_t::Self()->Current_Speaker()();
    }

    Bool_t Reference_t::Is_Quest_Item()
    {
        return this->x_list.Is_Quest_Item();
    }

    Bool_t Reference_t::Is_Aliased()
    {
        return this->x_list.Is_Aliased();
    }

    Bool_t Reference_t::Is_Aliased(some<Quest_t*> quest)
    {
        return this->x_list.Is_Aliased(quest);
    }

    Bool_t Reference_t::Is_Aliased(some<Quest_t*> quest, Alias_ID_t alias_id)
    {
        return this->x_list.Is_Aliased(quest, alias_id);
    }

    Bool_t Reference_t::Has_Owner(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        maybe<Cell_t*> cell = this->Cell();
        if (cell) {
            maybe<Form_t*> cell_owner = cell->Owner();
            if (cell_owner) {
                if (cell_owner->form_type == Form_Type_e::FACTION) {
                    some<Faction_t*> cell_faction_owner = static_cast<Faction_t*>(cell_owner());
                    if (actor->Is_In_Faction(cell_faction_owner())) {
                        return true;
                    }
                } else if (cell_owner->form_type == Form_Type_e::ACTOR_BASE) {
                    if (actor->base_form == cell_owner()) {
                        return true;
                    }
                }
            }
        }

        maybe<Form_t*> ref_owner = this->Owner();
        if (ref_owner) {
            if (ref_owner->form_type == Form_Type_e::FACTION) {
                some<Faction_t*> ref_faction_owner = static_cast<Faction_t*>(ref_owner());
                if (actor->Is_In_Faction(ref_faction_owner())) {
                    return true;
                }
            } else if (ref_owner->form_type == Form_Type_e::ACTOR_BASE) {
                if (actor->base_form == ref_owner()) {
                    return true;
                }
            }
        }

        return false;
    }

    Bool_t Reference_t::Has_Potential_Thief(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        maybe<Cell_t*> cell = this->Cell();
        if (cell) {
            maybe<Form_t*> cell_owner = cell->Owner();
            if (cell_owner) {
                if (cell_owner->form_type == Form_Type_e::FACTION) {
                    some<Faction_t*> cell_faction_owner = static_cast<Faction_t*>(cell_owner());
                    if (!actor->Is_In_Faction(cell_faction_owner())) {
                        return true;
                    }
                } else if (cell_owner->form_type == Form_Type_e::ACTOR_BASE) {
                    if (actor->base_form != cell_owner()) {
                        return true;
                    }
                }
            }
        }

        maybe<Form_t*> ref_owner = this->Owner();
        if (ref_owner) {
            if (ref_owner->form_type == Form_Type_e::FACTION) {
                some<Faction_t*> ref_faction_owner = static_cast<Faction_t*>(ref_owner());
                if (!actor->Is_In_Faction(ref_faction_owner())) {
                    return true;
                }
            } else if (ref_owner->form_type == Form_Type_e::ACTOR_BASE) {
                if (actor->base_form != ref_owner()) {
                    return true;
                }
            }
        }

        return false;
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

    maybe<Actor_Base_t*> Reference_t::Actor_Base_Owner()
    {
        maybe<Form_t*> owner = Owner();
        if (owner && owner->form_type == Form_Type_e::ACTOR_BASE) {
            return static_cast<maybe<Actor_Base_t*>>(owner);
        } else {
            return none<Actor_Base_t*>();
        }
    }

    Cell_t* Reference_t::Cell(Bool_t do_check_worldspace)
    {
        if (parent_cell) {
            return parent_cell();
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

    Vector_t<some<NI_Collidable_t*>> Reference_t::Collidables()
    {
        maybe<NI_3D_t*> ni_3d = attached_state ? attached_state->ni_3d : nullptr;
        if (ni_3d) {
            return ni_3d->Collidables();
        } else {
            return Vector_t<some<NI_Collidable_t*>>();
        }
    }

    void Reference_t::Collidables(Vector_t<some<NI_Collidable_t*>>& results)
    {
        maybe<NI_3D_t*> ni_3d = attached_state ? attached_state->ni_3d : nullptr;
        if (ni_3d) {
            ni_3d->Collidables(results);
        }
    }

    maybe<Collision_Layer_Type_e> Reference_t::Collision_Layer_Type()
    {
        if (this->form_type == Form_Type_e::ACTOR) {
            some<Actor_t*> actor = static_cast<Actor_t*>(this);
            maybe<Havok_Actor_Rigid_Body_Controller_t*> controller = actor->Havok_Actor_Rigid_Body_Controller();
            if (controller && controller->actor_rigid_body_base.rigid_body_base) {
                maybe<Havok_Rigid_Body_t*> rigid_body = controller->actor_rigid_body_base.rigid_body_base->Rigid_Body();
                if (rigid_body) {
                    return rigid_body->Collision_Layer_Type();
                } else {
                    return Collision_Layer_Type_e::_NONE_;
                }
            } else {
                return Collision_Layer_Type_e::_NONE_;
            }
        } else if (this->form_type == Form_Type_e::REFERENCE) {
            maybe<NI_3D_t*> ni_3d = attached_state ? attached_state->ni_3d : nullptr;
            if (ni_3d && ni_3d->collidable) {
                return ni_3d->collidable->Collision_Layer_Type();
            } else {
                return Collision_Layer_Type_e::_NONE_;
            }
        } else {
            return Collision_Layer_Type_e::_NONE_;
        }
    }

    void Reference_t::Collision_Layer_Type(some<Collision_Layer_Type_e> collision_layer_type)
    {
        SKYLIB_ASSERT_SOME(collision_layer_type);

        if (this->form_type == Form_Type_e::ACTOR) {
            some<Actor_t*> actor = static_cast<Actor_t*>(this);
            maybe<Havok_Actor_Rigid_Body_Controller_t*> controller = actor->Havok_Actor_Rigid_Body_Controller();
            if (controller && controller->actor_rigid_body_base.rigid_body_base) {
                maybe<Havok_Rigid_Body_t*> rigid_body = controller->actor_rigid_body_base.rigid_body_base->Rigid_Body();
                if (rigid_body) {
                    rigid_body->Collision_Layer_Type(collision_layer_type());
                }
            }
        } else if (this->form_type == Form_Type_e::REFERENCE) {
            maybe<NI_3D_t*> ni_3d = attached_state ? attached_state->ni_3d : nullptr;
            if (ni_3d && ni_3d->collidable) {
                ni_3d->collidable->Collision_Layer_Type(collision_layer_type());
            }
        }
    }

    maybe<Container_c*> Reference_t::Base_Component_Container()
    {
        if (this->base_form) {
            return this->base_form->As_Component_Container();
        } else {
            return none<Container_c*>();
        }
    }

    maybe<Container_Changes_t*> Reference_t::Container_Changes(Bool_t do_force_create)
    {
        static auto initialize_container_changes = reinterpret_cast
            <Container_Changes_t*(*)(Reference_t*)>
            (Game_t::Base_Address() + Offset_e::INITIALIZE_CONTAINER_CHANGES);

        maybe<Extra_Container_Changes_t*> x_container_changes = this->x_list.Get<Extra_Container_Changes_t>();
        if (x_container_changes && x_container_changes->container_changes) {
            return x_container_changes->container_changes;
        } else if (do_force_create) {
            return initialize_container_changes(this);
        } else {
            return none<Container_Changes_t*>();
        }
    }

    maybe<Faction_t*> Reference_t::Faction_Owner()
    {
        maybe<Form_t*> owner = Owner();
        if (owner && owner->form_type == Form_Type_e::FACTION) {
            return static_cast<maybe<Faction_t*>>(owner);
        } else {
            return none<Faction_t*>();
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

    maybe<Form_t*> Reference_t::Owner()
    {
        static auto get_owner = reinterpret_cast
            <Form_t*(*)(Reference_t*)>
            (Game_t::Base_Address() + Offset_e::GET_OWNER);

        return get_owner(this);
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

    Vector_t<some<Quest_t*>> Reference_t::Quests()
    {
        Vector_t<some<Quest_t*>> results;
        Quests(results);
        return results;
    }

    void Reference_t::Quests(Vector_t<some<Quest_t*>>& results)
    {
        this->x_list.Quests(results);
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

    void Reference_t::Add_Item(some<Form_t*> item, s16 delta)
    {
        SKYLIB_ASSERT_SOME(item);

        if (Is_Valid()) {
            some<Script_t*> script = Script_t::Create();
            script->Command(std::string("AddItem ") + item->Form_ID_String().data + " " + std::to_string(delta));
            script->Execute(this);
            Script_t::Destroy(script);
        }
    }

    void Reference_t::Enable()
    {
        if (Is_Valid()) {
            some<Script_t*> script = Script_t::Create();
            script->Command("Enable");
            script->Execute(this);
            Script_t::Destroy(script);
        }
    }

    void Reference_t::Disable()
    {
        if (Is_Valid()) {
            some<Script_t*> script = Script_t::Create();
            script->Command("Disable");
            script->Execute(this);
            Script_t::Destroy(script);
        }
    }

    void Reference_t::Mark_For_Delete(Bool_t do_disable)
    {
        if (Is_Valid()) {
            some<Script_t*> script = Script_t::Create();
            if (do_disable) {
                script->Command("Disable");
                script->Execute(this);
            }
            if (Is_Persistent()) {
                script->Command("MarkForDelete");
                script->Execute(this);
            }
            Script_t::Destroy(script);
        }
    }

    void Reference_t::Push_Away(some<Actor_t*> actor, Int_t force)
    {
        SKYLIB_ASSERT_SOME(actor);

        if (Is_Valid()) {
            some<Script_t*> script = Script_t::Create();
            script->Command(std::string("PushActorAway ") + actor->Form_ID_String().data + " " + std::to_string(force));
            script->Execute(this);
            Script_t::Destroy(script);
        }
    }

    void Reference_t::Select_In_Console()
    {
        if (Is_Valid()) {
            some<Script_t*> script = Script_t::Create();
            script->Command(std::string("prid ") + Form_ID_String().data);
            script->Execute(this);
            Script_t::Destroy(script);
        }
    }

    void Reference_t::Is_Activation_Blocked(Bool_t value, maybe<Virtual::Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Virtual::Arguments_t
        {
        public:
            Bool_t value;

        public:
            Virtual_Arguments(Bool_t value) :
                value(value)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Virtual::Variable_t>* args) override
            {
                args->Resize(1);
                args->At(0).As<Bool_t>(this->value);
                return true;
            }
        };

        Virtual::Machine_t::Ready_Scriptable<Reference_t*>(this);
        Virtual::Machine_t::Self()->Call_Method(
            this,
            SCRIPT_NAME,
            "BlockActivation",
            Virtual_Arguments(value),
            v_callback
        );
    }

    void Reference_t::Is_Activation_Blocked(Bool_t value, maybe<unique<Callback_i<>>> callback)
    {
        using Callback = maybe<unique<Callback_i<>>>;

        class Virtual_Callback :
            public Virtual::Callback_t
        {
        public:
            Callback callback;

        public:
            Virtual_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(Virtual::Variable_t*) override
            {
                if (this->callback) {
                    (*this->callback)();
                }
            }
        };

        Is_Activation_Blocked(value, new Virtual_Callback(std::move(callback)));
    }

    void Reference_t::Is_Open(Bool_t value, maybe<Virtual::Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Virtual::Arguments_t
        {
        public:
            Bool_t value;

        public:
            Virtual_Arguments(Bool_t value) :
                value(value)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Virtual::Variable_t>* args) override
            {
                args->Resize(1);
                args->At(0).As<Bool_t>(this->value);
                return true;
            }
        };

        Virtual::Machine_t::Ready_Scriptable<Reference_t*>(this);
        Virtual::Machine_t::Self()->Call_Method(
            this,
            SCRIPT_NAME,
            "SetOpen",
            Virtual_Arguments(value),
            v_callback
        );
    }

    void Reference_t::Is_Open(Bool_t value, maybe<unique<Callback_i<>>> callback)
    {
        using Callback = maybe<unique<Callback_i<>>>;

        class Virtual_Callback :
            public Virtual::Callback_t
        {
        public:
            Callback callback;

        public:
            Virtual_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(Virtual::Variable_t*) override
            {
                if (this->callback) {
                    (*this->callback)();
                }
            }
        };

        Is_Open(value, new Virtual_Callback(std::move(callback)));
    }

    void Reference_t::Activate(some<Reference_t*> activator,
                               Bool_t do_only_default_processing,
                               maybe<Virtual::Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Virtual::Arguments_t
        {
        public:
            some<Reference_t*>  activator;
            Bool_t              do_only_default_processing;

        public:
            Virtual_Arguments(some<Reference_t*> activator, Bool_t do_only_default_processing) :
                activator(activator), do_only_default_processing(do_only_default_processing)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Virtual::Variable_t>* args) override
            {
                args->Resize(2);
                args->At(0).As<Reference_t*>(this->activator());
                args->At(1).As<Bool_t>(this->do_only_default_processing);
                return true;
            }
        };

        SKYLIB_ASSERT_SOME(activator);

        Virtual::Machine_t::Ready_Scriptable<Reference_t*>(this);
        Virtual::Machine_t::Self()->Call_Method(
            this,
            SCRIPT_NAME,
            "Activate",
            Virtual_Arguments(activator, do_only_default_processing),
            v_callback
        );
    }

    void Reference_t::Activate(some<Reference_t*> activator,
                               Bool_t do_only_default_processing,
                               maybe<unique<Callback_i<Bool_t>>> callback)
    {
        using Callback = maybe<unique<Callback_i<Bool_t>>>;

        class Virtual_Callback :
            public Virtual::Callback_t
        {
        public:
            Callback callback;

        public:
            Virtual_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(Virtual::Variable_t* result) override
            {
                if (this->callback) {
                    (*this->callback)(result ? result->As<Bool_t>() : false);
                }
            }
        };

        SKYLIB_ASSERT_SOME(activator);

        Activate(activator, do_only_default_processing, new Virtual_Callback(std::move(callback)));
    }

    void Reference_t::Find_Closest_Actor(Float_t radius, some<Virtual::Callback_i*> v_callback)
    {
        Virtual::Game_t::Find_Closest_Actor_From(this, radius, v_callback);
    }

    void Reference_t::Find_Closest_Actor(Float_t radius, some<unique<Callback_i<maybe<Actor_t*>>>> callback)
    {
        Virtual::Game_t::Find_Closest_Actor_From(this, radius, std::move(callback));
    }

    void Reference_t::Open_Inventory(maybe<unique<Callback_i<Bool_t>>> callback)
    {
        using Callback = maybe<unique<Callback_i<Bool_t>>>;

        class Open_Callback :
            public Virtual::Callback_t
        {
        public:
            Callback callback;

        public:
            Open_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(Virtual::Variable_t*) override
            {
                class Wait_Callback :
                    public Virtual::Callback_t
                {
                public:
                    Callback callback;

                public:
                    Wait_Callback(Callback callback) :
                        callback(std::move(callback))
                    {
                    }

                public:
                    virtual void operator()(Virtual::Variable_t*) override
                    {
                        if (this->callback) {
                            (*this->callback)(true);
                        }
                    }
                };
                Virtual::Utility_t::Wait_Out_Of_Menu(0.1f, new Wait_Callback(std::move(this->callback)));
            }
        };

        if (Is_Based_On_Component_Container()) {
            maybe<Actor_t*> actor = As_Actor();
            if (actor) {
                actor->Open_Inventory(true, new Open_Callback(std::move(callback)));
            } else {
                Activate(Player_t::Self(), false, new Open_Callback(std::move(callback)));
            }
        } else {
            if (callback) {
                (*callback)(false);
            }
        }
    }

    void Reference_t::Play_Animation(String_t animation_event_name, maybe<Virtual::Callback_i*> v_callback)
    {
        Virtual::Debug_t::Send_Animation_Event(this, animation_event_name, v_callback);
    }

    void Reference_t::Play_Animation(String_t animation_event_name, maybe<unique<Callback_i<>>> callback)
    {
        Virtual::Debug_t::Send_Animation_Event(this, animation_event_name, std::move(callback));
    }

    void Reference_t::Reset_Animation(maybe<Virtual::Callback_i*> v_callback)
    {
        Play_Animation("IdleForceDefaultState", v_callback);
    }

    void Reference_t::Reset_Animation(maybe<unique<Callback_i<>>> callback)
    {
        Play_Animation("IdleForceDefaultState", std::move(callback));
    }

    void Reference_t::Push_Away(some<Actor_t*> actor, Float_t force, maybe<Virtual::Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Virtual::Arguments_t
        {
        public:
            some<Actor_t*>  actor;
            Float_t         force;

        public:
            Virtual_Arguments(some<Actor_t*> actor, Float_t force) :
                actor(actor), force(force)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Virtual::Variable_t>* args) override
            {
                args->Resize(2);
                args->At(0).As<Actor_t*>(this->actor());
                args->At(1).As<Float_t>(this->force);
                return true;
            }
        };

        SKYLIB_ASSERT_SOME(actor);

        Virtual::Machine_t::Ready_Scriptable<Reference_t*>(this);
        Virtual::Machine_t::Self()->Call_Method(
            this,
            SCRIPT_NAME,
            "PushActorAway",
            Virtual_Arguments(actor, force),
            v_callback
        );
    }

    void Reference_t::Push_Away(some<Actor_t*> actor, Float_t force, maybe<unique<Callback_i<>>> callback)
    {
        using Callback = maybe<unique<Callback_i<>>>;

        class Virtual_Callback :
            public Virtual::Callback_t
        {
        public:
            Callback callback;

        public:
            Virtual_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(Virtual::Variable_t*) override
            {
                if (this->callback) {
                    (*this->callback)();
                }
            }
        };

        SKYLIB_ASSERT_SOME(actor);

        Push_Away(actor, force, new Virtual_Callback(std::move(callback)));
    }

    void Reference_t::Start_Translation_To(Float_t x_position, Float_t y_position, Float_t z_position,
                                           Float_t x_degree, Float_t y_degree, Float_t z_degree,
                                           Float_t movement_speed, Float_t max_rotation_speed,
                                           maybe<Virtual::Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Virtual::Arguments_t
        {
        public:
            Float_t x_position;
            Float_t y_position;
            Float_t z_position;
            Float_t x_degree;
            Float_t y_degree;
            Float_t z_degree;
            Float_t movement_speed;
            Float_t max_rotation_speed;

        public:
            Virtual_Arguments(Float_t x_position, Float_t y_position, Float_t z_position,
                              Float_t x_degree, Float_t y_degree, Float_t z_degree,
                              Float_t movement_speed, Float_t max_rotation_speed) :
                x_position(x_position), y_position(y_position), z_position(z_position),
                x_degree(x_degree), y_degree(y_degree), z_degree(z_degree),
                movement_speed(movement_speed), max_rotation_speed(max_rotation_speed)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Virtual::Variable_t>* args) override
            {
                args->Resize(8);
                args->At(0).As<Float_t>(this->x_position);
                args->At(1).As<Float_t>(this->y_position);
                args->At(2).As<Float_t>(this->z_position);
                args->At(3).As<Float_t>(this->x_degree);
                args->At(4).As<Float_t>(this->y_degree);
                args->At(5).As<Float_t>(this->z_degree);
                args->At(6).As<Float_t>(this->movement_speed);
                args->At(7).As<Float_t>(this->max_rotation_speed);
                return true;
            }
        };

        Virtual::Machine_t::Ready_Scriptable<Reference_t*>(this);
        Virtual::Machine_t::Self()->Call_Method(
            this,
            SCRIPT_NAME,
            "TranslateTo",
            Virtual_Arguments(x_position, y_position, z_position,
                              x_degree, y_degree, z_degree,
                              movement_speed, max_rotation_speed),
            v_callback
        );
    }

    void Reference_t::Start_Translation_To(Float_t x_position, Float_t y_position, Float_t z_position,
                                           Float_t x_degree, Float_t y_degree, Float_t z_degree,
                                           Float_t movement_speed, Float_t max_rotation_speed,
                                           maybe<unique<Callback_i<>>> callback)
    {
        using Callback = maybe<unique<Callback_i<>>>;

        class Virtual_Callback :
            public Virtual::Callback_t
        {
        public:
            Callback callback;

        public:
            Virtual_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(Virtual::Variable_t*) override
            {
                if (this->callback) {
                    (*this->callback)();
                }
            }
        };

        Start_Translation_To(x_position, y_position, z_position,
                             x_degree, y_degree, z_degree,
                             movement_speed, max_rotation_speed,
                             new Virtual_Callback(std::move(callback)));
    }

    void Reference_t::Stop_Translation(maybe<Virtual::Callback_i*> v_callback)
    {
        Virtual::Machine_t::Self()->Call_Method(
            this,
            SCRIPT_NAME,
            "StopTranslation",
            none<Virtual::Arguments_i*>(),
            v_callback
        );
    }

    void Reference_t::Stop_Translation(maybe<unique<Callback_i<>>> callback)
    {
        using Callback = maybe<unique<Callback_i<>>>;

        class Virtual_Callback :
            public Virtual::Callback_t
        {
        public:
            Callback callback;

        public:
            Virtual_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(Virtual::Variable_t*) override
            {
                if (this->callback) {
                    (*this->callback)();
                }
            }
        };

        Stop_Translation(new Virtual_Callback(std::move(callback)));
    }

    void Reference_t::Apply_Havok_Impulse(Float_t x, Float_t y, Float_t z, Float_t force,
                                          maybe<Virtual::Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Virtual::Arguments_t
        {
        public:
            Float_t x;
            Float_t y;
            Float_t z;
            Float_t force;

        public:
            Virtual_Arguments(Float_t x, Float_t y, Float_t z, Float_t force) :
                x(x), y(y), z(z), force(force)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Virtual::Variable_t>* args) override
            {
                args->Resize(4);
                args->At(0).As<Float_t>(this->x);
                args->At(1).As<Float_t>(this->y);
                args->At(2).As<Float_t>(this->z);
                args->At(3).As<Float_t>(this->force);
                return true;
            }
        };

        Virtual::Machine_t::Ready_Scriptable<Reference_t*>(this);
        Virtual::Machine_t::Self()->Call_Method(
            this,
            SCRIPT_NAME,
            "ApplyHavokImpulse",
            Virtual_Arguments(x, y, z, force),
            v_callback
        );
    }

    void Reference_t::Apply_Havok_Impulse(Float_t x, Float_t y, Float_t z, Float_t force,
                                          maybe<unique<Callback_i<>>> callback)
    {
        using Callback = maybe<unique<Callback_i<>>>;

        class Virtual_Callback :
            public Virtual::Callback_t
        {
        public:
            Callback callback;

        public:
            Virtual_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(Virtual::Variable_t*) override
            {
                if (this->callback) {
                    (*this->callback)();
                }
            }
        };

        Apply_Havok_Impulse(x, y, z, force, new Virtual_Callback(std::move(callback)));
    }

    void Reference_t::Log_Extra_List(std::string indent)
    {
        SKYLIB_LOG(indent + "Reference_t::Log_Extra_List");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "form_type: %s, form_id: %s, any_name: %s",
                   Form_Type_e::To_String(this->form_type),
                   this->Form_ID_String(),
                   this->Any_Name());
        if (this->base_form) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "base_form_type: %s, base_form_id: %s, component_name: %s",
                       Form_Type_e::To_String(this->base_form->form_type),
                       this->base_form->Form_ID_String(),
                       this->base_form->Component_Name());
        }
        
        this->x_list.Log(indent + SKYLIB_TAB);

        SKYLIB_LOG(indent + "}");
    }

}

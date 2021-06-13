/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/alias_base.h"
#include "doticu_skylib/alias_reference.h"
#include "doticu_skylib/atomic_number.inl"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/component_container.h"
#include "doticu_skylib/container_changes.h"
#include "doticu_skylib/container_entry.h"
#include "doticu_skylib/dialogue_manager.h"
#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/extra_aliases.h"
#include "doticu_skylib/extra_container_changes.h"
#include "doticu_skylib/extra_list.inl"
#include "doticu_skylib/extra_text_display.h"
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
#include "doticu_skylib/reference_container.h"
#include "doticu_skylib/reference_container_entry.h"
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

    Vector_t<some<Reference_t*>> Reference_t::All_References()
    {
        Vector_t<some<Reference_t*>> results;
        All_References(results);
        return results;
    }

    void Reference_t::All_References(Vector_t<some<Reference_t*>>& results)
    {
        class Iterator :
            public Iterator_i<some<Form_t*>>
        {
        public:
            Vector_t<some<Reference_t*>>& results;

        public:
            Iterator(Vector_t<some<Reference_t*>>& results) :
                results(results)
            {
            }

        public:
            virtual Iterator_e operator ()(some<Form_t*> form) override
            {
                maybe<Reference_t*> reference = form->As_Reference();
                if (reference && reference->Is_Valid()) {
                    this->results.push_back(reference());
                }
                return Iterator_e::CONTINUE;
            }
        };

        results.reserve(2048);

        Iterator iterator(results);

        Game_t::Iterate_Forms(iterator);
    }

    Vector_t<some<Reference_t*>> Reference_t::All_References(Filter_i<some<Reference_t*>>& filter)
    {
        Vector_t<some<Reference_t*>> results;
        All_References(results, filter);
        return results;
    }

    void Reference_t::All_References(Vector_t<some<Reference_t*>>& results, Filter_i<some<Reference_t*>>& filter)
    {
        class Iterator :
            public Iterator_i<some<Form_t*>>
        {
        public:
            Vector_t<some<Reference_t*>>& results;
            Filter_i<some<Reference_t*>>& filter;

        public:
            Iterator(Vector_t<some<Reference_t*>>& results, Filter_i<some<Reference_t*>>& filter) :
                results(results), filter(filter)
            {
            }

        public:
            virtual Iterator_e operator ()(some<Form_t*> form) override
            {
                maybe<Reference_t*> reference = form->As_Reference();
                if (reference && reference->Is_Valid() && this->filter(reference())) {
                    this->results.push_back(reference());
                }
                return Iterator_e::CONTINUE;
            }
        };

        results.reserve(2048);

        Iterator iterator(results, filter);

        Game_t::Iterate_Forms(iterator);
    }

    Vector_t<some<Reference_t*>> Reference_t::All_References_In_Cells(Filter_i<some<Reference_t*>>& filter)
    {
        Vector_t<some<Reference_t*>> results;
        All_References_In_Cells(results, filter);
        return results;
    }

    void Reference_t::All_References_In_Cells(Vector_t<some<Reference_t*>>& results, Filter_i<some<Reference_t*>>& filter)
    {
        class Iterator :
            public Iterator_i<some<Form_t*>>
        {
        public:
            Vector_t<some<Reference_t*>>& results;
            Filter_i<some<Reference_t*>>& filter;

        public:
            Iterator(Vector_t<some<Reference_t*>>& results, Filter_i<some<Reference_t*>>& filter) :
                results(results), filter(filter)
            {
            }

        public:
            virtual Iterator_e operator ()(some<Form_t*> form) override
            {
                maybe<Reference_t*> reference = form->As_Reference();
                if (reference && reference->Is_Valid() && reference->Cell(true) && this->filter(reference())) {
                    this->results.push_back(reference());
                }
                return Iterator_e::CONTINUE;
            }
        };

        results.reserve(2048);

        Iterator iterator(results, filter);

        Game_t::Iterate_Forms(iterator);
    }

    Vector_t<some<Reference_t*>> Reference_t::Grid_References()
    {
        Vector_t<some<Reference_t*>> results;
        Grid_References(results);
        return results;
    }

    void Reference_t::Grid_References(Vector_t<some<Reference_t*>>& results)
    {
        class Iterator :
            public Iterator_i<some<Reference_t*>>
        {
        public:
            Vector_t<some<Reference_t*>>& results;

        public:
            Iterator(Vector_t<some<Reference_t*>>& results) :
                results(results)
            {
            }

        public:
            virtual Iterator_e operator ()(some<Reference_t*> reference) override
            {
                if (reference->Is_Valid() && !this->results.Has(reference)) {
                    this->results.push_back(reference);
                }
                return Iterator_e::CONTINUE;
            }
        };

        results.reserve(2048);

        Iterator iterator(results);

        Vector_t<some<Cell_t*>> cells_in_grid = Cell_t::Grid_Cells();
        for (size_t idx = 0, end = cells_in_grid.size(); idx < end; idx += 1) {
            cells_in_grid[idx]->Iterate_References(iterator);
        }
    }

    void Reference_t::Grid_References(some<Form_List_t*> results)
    {
        class Iterator :
            public Iterator_i<some<Reference_t*>>
        {
        public:
            some<Form_List_t*> results;

        public:
            Iterator(some<Form_List_t*> results) :
                results(results)
            {
            }

        public:
            virtual Iterator_e operator ()(some<Reference_t*> reference) override
            {
                if (reference->Is_Valid() && !this->results->Has(reference)) {
                    this->results->Add_Form(reference);
                }
                return Iterator_e::CONTINUE;
            }
        };

        SKYLIB_ASSERT_SOME(results);

        Iterator iterator(results);

        Vector_t<some<Cell_t*>> cells_in_grid = Cell_t::Grid_Cells();
        for (size_t idx = 0, end = cells_in_grid.size(); idx < end; idx += 1) {
            cells_in_grid[idx]->Iterate_References(iterator);
        }
    }

    Vector_t<some<Reference_t*>> Reference_t::Grid_References(Filter_i<some<Reference_t*>>& filter)
    {
        Vector_t<some<Reference_t*>> results;
        Grid_References(results, filter);
        return results;
    }

    void Reference_t::Grid_References(Vector_t<some<Reference_t*>>& results, Filter_i<some<Reference_t*>>& filter)
    {
        class Iterator :
            public Iterator_i<some<Reference_t*>>
        {
        public:
            Vector_t<some<Reference_t*>>& results;
            Filter_i<some<Reference_t*>>& filter;

        public:
            Iterator(Vector_t<some<Reference_t*>>& results, Filter_i<some<Reference_t*>>& filter) :
                results(results), filter(filter)
            {
            }

        public:
            virtual Iterator_e operator ()(some<Reference_t*> reference) override
            {
                if (reference->Is_Valid() && !this->results.Has(reference) && this->filter(reference)) {
                    this->results.push_back(reference);
                }
                return Iterator_e::CONTINUE;
            }
        };

        results.reserve(2048);

        Iterator iterator(results, filter);

        Vector_t<some<Cell_t*>> cells_in_grid = Cell_t::Grid_Cells();
        for (size_t idx = 0, end = cells_in_grid.size(); idx < end; idx += 1) {
            cells_in_grid[idx]->Iterate_References(iterator);
        }
    }

    void Reference_t::Grid_References(some<Form_List_t*> results, Filter_i<some<Reference_t*>>& filter)
    {
        class Iterator :
            public Iterator_i<some<Reference_t*>>
        {
        public:
            some<Form_List_t*>              results;
            Filter_i<some<Reference_t*>>& filter;

        public:
            Iterator(some<Form_List_t*> results, Filter_i<some<Reference_t*>>& filter) :
                results(results), filter(filter)
            {
            }

        public:
            virtual Iterator_e operator ()(some<Reference_t*> reference) override
            {
                if (reference->Is_Valid() && !this->results->Has(reference) && this->filter(reference)) {
                    this->results->Add_Form(reference);
                }
                return Iterator_e::CONTINUE;
            }
        };

        SKYLIB_ASSERT_SOME(results);

        Iterator iterator(results, filter);

        Vector_t<some<Cell_t*>> cells_in_grid = Cell_t::Grid_Cells();
        for (size_t idx = 0, end = cells_in_grid.size(); idx < end; idx += 1) {
            cells_in_grid[idx]->Iterate_References(iterator);
        }
    }

    void Reference_t::Iterate_All_References_Periodically(Iterator_i<some<Reference_t*>>& iterator,
                                                          std::chrono::nanoseconds interval)
    {
        class Form_Iterator :
            public Iterator_i<some<Form_t*>>
        {
        public:
            Iterator_i<some<Reference_t*>>& iterator;

        public:
            Form_Iterator(Iterator_i<some<Reference_t*>>& iterator) :
                iterator(iterator)
            {
            }

        public:
            virtual Iterator_e operator ()(some<Form_t*> form) override
            {
                maybe<Reference_t*> reference = form->As_Reference();
                if (reference && reference->Is_Valid()) {
                    return this->iterator(reference());
                } else {
                    return Iterator_e::CONTINUE;
                }
            }
        };

        Form_Iterator form_iterator(iterator);

        Game_t::Iterate_Forms_Periodically(form_iterator, interval);
    }

    maybe<Reference_t*> Reference_t::Create(some<Form_t*> base,
                                            u32 count,
                                            maybe<Reference_t*> at,
                                            Bool_t do_force_persist,
                                            Bool_t do_initially_disable,
                                            Bool_t do_place_exactly)
    {
        static auto place_at_me = reinterpret_cast
            <Reference_t*(*)(Virtual::Machine_t*, Virtual::Raw_Stack_ID_t, Reference_t*, Form_t*, u32, Bool_t, Bool_t)>
            (Game_t::Base_Address() + Offset_e::PLACE_AT_ME);

        SKYLIB_ASSERT_SOME(base);

        if (!at) {
            at = Player_t::Self()();
        }

        maybe<Reference_t*> reference =
            place_at_me(Virtual::Machine_t::Self()(), 0, at(), base(), count, do_force_persist, do_initially_disable);

        if (reference && do_place_exactly) {
            reference->position.x = at->position.x;
            reference->position.y = at->position.y;
            reference->position.z = at->position.z;

            reference->rotation.x = at->rotation.x;
            reference->rotation.y = at->rotation.y;
            reference->rotation.z = at->rotation.z;

            reference->Do_Update_3D_Position(true);
        }

        return reference;
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
        return this->form_flags.Is_Flagged(Form_Flags_e::IS_DELETED);
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
        return this->form_flags.Is_Flagged(Form_Flags_e::IS_DISABLED);
    }

    Bool_t Reference_t::Is_Persistent()
    {
        return this->form_flags.Is_Flagged(Form_Flags_e::IS_PERSISTENT);
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

    Bool_t Reference_t::Is_Stealable()
    {
        static auto is_stealable = reinterpret_cast
            <Bool_t(*)(Reference_t*)>
            (Game_t::Base_Address() + static_cast<Word_t>(Offset_e::IS_STEALABLE));

        return is_stealable(this);
    }

    maybe<Bool_t> Reference_t::Is_In_Interior_Cell()
    {
        maybe<Cell_t*> cell = Cell(true);
        if (cell) {
            return cell->Is_Interior();
        } else {
            return none<Bool_t>();
        }
    }

    maybe<Bool_t> Reference_t::Is_In_Exterior_Cell()
    {
        maybe<Cell_t*> cell = Cell(true);
        if (cell) {
            return cell->Is_Exterior();
        } else {
            return none<Bool_t>();
        }
    }

    Bool_t Reference_t::Is_In_Dialogue_With_Player()
    {
        return this == Dialogue_Manager_t::Self()->Current_Speaker()();
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

    Bool_t Reference_t::Is_Aliased_As_Protected()
    {
        return this->x_list.Is_Protected();
    }

    Bool_t Reference_t::Is_Aliased_As_Essential()
    {
        return this->x_list.Is_Essential();
    }

    Bool_t Reference_t::Is_Quest_Item()
    {
        return this->x_list.Is_Quest_Item();
    }

    Bool_t Reference_t::May_Lawfully_Be_Taken_By(some<Actor_t*> actor, Bool_t do_test_factions, Bool_t must_be_owned)
    {
        static auto may_lawfully_be_taken_by = reinterpret_cast
            <Bool_t(*)(Reference_t*, Actor_t*, Bool_t, Bool_t)>
            (Game_t::Base_Address() + static_cast<Word_t>(Offset_e::MAY_LAWFULLY_BE_TAKEN_BY));

        SKYLIB_ASSERT_SOME(actor);

        return may_lawfully_be_taken_by(this, actor(), do_test_factions, must_be_owned);
    }

    Bool_t Reference_t::Has_Owner()
    {
        return !!This_Or_Cell_Owner();
    }

    Bool_t Reference_t::Has_Owner(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        return May_Lawfully_Be_Taken_By(actor, true, true);
    }

    Bool_t Reference_t::Has_Potential_Thief(some<Actor_t*> actor)
    {
        SKYLIB_ASSERT_SOME(actor);

        return !May_Lawfully_Be_Taken_By(actor, true, false);
    }

    Bool_t Reference_t::Has_Keyword(some<Keyword_t*> keyword) const
    {
        SKYLIB_ASSERT_SOME(keyword);

        return Get_Has_Keyword(keyword());
    }

    Bool_t Reference_t::Has_Extra_Text_Display()
    {
        return this->x_list.Get<Extra_Text_Display_t>() != none<Extra_Text_Display_t*>();
    }

    Bool_t Reference_t::Has_Custom_Name()
    {
        maybe<Extra_Text_Display_t*> x_text_display = this->x_list.Get<Extra_Text_Display_t>();
        if (x_text_display) {
            return x_text_display->Name().Has_Value();
        } else {
            return false;
        }
    }

    Bool_t Reference_t::Has_Quest_Text_Display(some<Quest_t*> quest)
    {
        SKYLIB_ASSERT_SOME(quest);

        maybe<Extra_Text_Display_t*> x_text_display = this->x_list.Get<Extra_Text_Display_t>();
        if (x_text_display) {
            return x_text_display->owning_quest == quest;
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

    void Reference_t::Name(String_t name)
    {
        this->x_list.Name(name);
    }

    String_t Reference_t::Any_Name()
    {
        maybe<Actor_t*> actor = As_Actor();
        if (actor) {
            return actor->Any_Name();
        } else {
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
    }

    void Reference_t::Add_Item(some<Bound_Object_t*> object,
                               maybe<Extra_List_t*> loose_x_list,
                               s32 non_zero_count,
                               maybe<Reference_t*> from)
    {
        SKYLIB_ASSERT_SOME(object);
        SKYLIB_ASSERT(non_zero_count != 0);

        // This will create the container_changes and container_changes_entry if necessary.
        // If count is zero, it sets to one. positive increments, negative decrements.
        // If not given an x_list, it will either increment or decrement by count. doesn't go below x_list count.
        // If given an x_list, it will move it and make updates to certain types, like Extra_Reference_Handle_t.
        // If the x_list is on another reference, you MUST remove it from that reference first.
        // If given a valid x_list, it ignores count. however, it's probably wise to just pass the x_list count anyway.
        // If given an unuseful x_list, it increments the object normally.
        // From doesn't have it's x_list removed automatically. perhaps it's decremented when there is no x_list?

        Do_Add_Item(object(), loose_x_list(), non_zero_count, from());
    }

    Vector_t<some<Alias_Base_t*>> Reference_t::Alias_Bases()
    {
        return this->x_list.Alias_Bases();
    }

    Vector_t<some<Alias_Reference_t*>> Reference_t::Alias_References()
    {
        return this->x_list.Alias_References();
    }

    maybe<Cell_t*> Reference_t::Cell(Bool_t do_check_worldspace)
    {
        if (this->parent_cell) {
            return this->parent_cell();
        } else if (do_check_worldspace) {
            maybe<Worldspace_t*> worldspace = Worldspace_Impl(this);
            if (worldspace) {
                return worldspace->persistent_cell;
            } else {
                return none<Cell_t*>();
            }
        } else {
            return none<Cell_t*>();
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

    maybe<Container_Entry_t*> Reference_t::Base_Component_Container_Entry(some<Bound_Object_t*> object)
    {
        SKYLIB_ASSERT_SOME(object);

        maybe<Container_c*> base_component_container = Base_Component_Container();
        if (base_component_container) {
            return base_component_container->Maybe_Entry(object);
        } else {
            return none<Container_Entry_t*>();
        }
    }

    maybe<Extra_Container_Changes_t*> Reference_t::Maybe_Extra_Container_Changes()
    {
        return this->x_list.Get<Extra_Container_Changes_t>();
    }

    some<Extra_Container_Changes_t*> Reference_t::Some_Extra_Container_Changes()
    {
        if (!this->x_list.Has<Extra_Container_Changes_t>()) {
            Some_Container_Changes();
        }
        some<Extra_Container_Changes_t*> x_container_changes = this->x_list.Get<Extra_Container_Changes_t>()();
        SKYLIB_ASSERT_SOME(x_container_changes);
        return x_container_changes;
    }

    maybe<Container_Changes_t*> Reference_t::Maybe_Container_Changes()
    {
        maybe<Extra_Container_Changes_t*> x_container_changes = this->x_list.Get<Extra_Container_Changes_t>();
        if (x_container_changes && x_container_changes->container_changes) {
            return x_container_changes->container_changes;
        } else {
            return none<Container_Changes_t*>();
        }
    }

    some<Container_Changes_t*> Reference_t::Some_Container_Changes()
    {
        static auto some_container_changes = reinterpret_cast
            <Container_Changes_t*(*)(Reference_t*)>
            (Game_t::Base_Address() + Offset_e::SOME_CONTAINER_CHANGES);

        maybe<Extra_Container_Changes_t*> x_container_changes = this->x_list.Get<Extra_Container_Changes_t>();
        if (x_container_changes && x_container_changes->container_changes) {
            return x_container_changes->container_changes();
        } else {
            some<Container_Changes_t*> container_changes = some_container_changes(this);
            SKYLIB_ASSERT_SOME(container_changes);
            return container_changes;
        }
    }

    maybe<Container_Changes_Entry_t*> Reference_t::Maybe_Container_Changes_Entry(some<Bound_Object_t*> object)
    {
        SKYLIB_ASSERT_SOME(object);

        maybe<Container_Changes_t*> container_changes = Maybe_Container_Changes();
        if (container_changes) {
            return container_changes->Maybe_Entry(object);
        } else {
            return none<Container_Changes_Entry_t*>();
        }
    }

    some<Container_Changes_Entry_t*> Reference_t::Some_Container_Changes_Entry(some<Bound_Object_t*> object)
    {
        SKYLIB_ASSERT_SOME(object);

        return Some_Container_Changes()->Some_Entry(object);
    }

    Reference_Container_t Reference_t::Container()
    {
        return std::move(Reference_Container_t(this));
    }

    maybe<Reference_Container_Entry_t> Reference_t::Maybe_Container_Entry(some<Bound_Object_t*> object)
    {
        SKYLIB_ASSERT_SOME(object);

        return maybe<Reference_Container_Entry_t>(Base_Component_Container_Entry(object), Maybe_Container_Changes_Entry(object));
    }

    some<Reference_Container_Entry_t> Reference_t::Some_Container_Entry(some<Bound_Object_t*> object)
    {
        SKYLIB_ASSERT_SOME(object);

        return some<Reference_Container_Entry_t>(Base_Component_Container_Entry(object), Some_Container_Changes_Entry(object));
    }

    sp32 Reference_t::Container_Entry_Count(some<Bound_Object_t*> object)
    {
        SKYLIB_ASSERT_SOME(object);

        maybe<Reference_Container_Entry_t> entry = Maybe_Container_Entry(object);
        if (entry) {
            return entry.Count();
        } else {
            return 0;
        }
    }

    Vector_t<some<Reference_t*>> Reference_t::Contained_References() const
    {
        return this->x_list.Contained_References();
    }

    void Reference_t::Contained_References(Vector_t<some<Reference_t*>>& results) const
    {
        return this->x_list.Contained_References(results);
    }

    maybe<Location_t*> Reference_t::Location()
    {
        maybe<Location_t*> location = Cell_Location();
        if (location) {
            return location;
        } else {
            return Worldspace_Location();
        }
    }

    maybe<Location_t*> Reference_t::Cell_Location()
    {
        maybe<Cell_t*> cell = Cell(true);
        if (cell) {
            return cell->Location();
        } else {
            return none<Location_t*>();
        }
    }

    maybe<Location_t*> Reference_t::Worldspace_Location()
    {
        maybe<Worldspace_t*> worldspace = Worldspace(true);
        if (worldspace) {
            return worldspace->Location();
        } else {
            return none<Location_t*>();
        }
    }

    maybe<Worldspace_t*> Reference_t::Worldspace(Bool_t do_check_cell_locations)
    {
        maybe<Worldspace_t*> worldspace = Worldspace_Impl(this);
        if (worldspace) {
            return worldspace;
        } else if (this->parent_cell) {
            return this->parent_cell->Worldspace(do_check_cell_locations);
        } else {
            return none<Worldspace_t*>();
        }
    }

    Vector_t<some<Location_t*>> Reference_t::Locations()
    {
        Vector_t<some<Location_t*>> results;
        Locations(results);
        return results;
    }

    void Reference_t::Locations(Vector_t<some<Location_t*>>& results)
    {
        maybe<Cell_t*> cell = Cell(true);
        if (cell && cell->Is_Valid()) {
            cell->Locations(results);
        } else {
            maybe<Worldspace_t*> worldspace = Worldspace(false);
            if (worldspace && worldspace->Is_Valid()) {
                if (!results.Has(worldspace->location())) {
                    results.push_back(worldspace->location());
                }
                worldspace->location->Parents(results);
            }
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

    s32 Reference_t::Gold_Value()
    {
        // getting the gold value can be difficult. some base forms have a Value_c,
        // whereas with Potion_t we need to look at cost_override or auto calc.
        // there may be a way to calc gold through the engine.
        if (this->base_form) {
            return this->base_form->Component_Value();
        } else {
            return -1;
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

    void Reference_t::Move_To_Offset(maybe<Reference_t*> target_reference,
                                     maybe<Cell_t*> target_cell,
                                     maybe<Worldspace_t*> target_worldspace,
                                     f32_xyz offset,
                                     f32_xyz rotation)
    {
        static auto move_to_offset = reinterpret_cast
            <void(*)(Reference_t*, Reference_Handle_t&, Cell_t*, Worldspace_t*, f32_xyz&, f32_xyz&)>
            (Game_t::Base_Address() + Offset_e::MOVE_TO_OFFSET);

        if (Is_Valid()) {
            if (target_reference) {
                Reference_Handle_t target_reference_handle =
                    target_reference->Is_Valid() ? target_reference->To_Handle() : Reference_t::Invalid_Handle();
                move_to_offset(this, target_reference_handle, target_cell(), target_worldspace(), offset, rotation);
            } else {
                Reference_Handle_t target_reference_handle = Reference_t::Invalid_Handle();
                move_to_offset(this, target_reference_handle, target_cell(), target_worldspace(), offset, rotation);
            }
        }
    }

    void Reference_t::Move_To_Offset(some<Reference_t*> reference_target, f32_xyz offset, f32_xyz rotation)
    {
        SKYLIB_ASSERT_SOME(reference_target);

        Move_To_Offset(reference_target, reference_target->Cell(false), reference_target->Worldspace(false), offset, rotation);
    }

    void Reference_t::Move_To_Offset(some<Cell_t*> interior_cell_target, f32_xyz offset, f32_xyz rotation)
    {
        SKYLIB_ASSERT_SOME(interior_cell_target);

        Move_To_Offset(none<Reference_t*>(), interior_cell_target, none<Worldspace_t*>(), offset, rotation);
    }

    void Reference_t::Move_To_Offset(some<Worldspace_t*> worldspace_target, f32_xyz offset, f32_xyz rotation)
    {
        SKYLIB_ASSERT_SOME(worldspace_target);

        Move_To_Offset(none<Reference_t*>(), none<Cell_t*>(), worldspace_target, offset, rotation);
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

    void Reference_t::Copy_Worn_Items(some<Reference_t*> other)
    {
        Reference_Container_t this_container(this);
        Reference_Container_t other_container(other);
        if (this_container.Is_Valid() && other_container.Is_Valid()) {
            for (size_t idx = 0, end = other_container.entries.size(); idx < end; idx += 1) {
                Reference_Container_Entry_t& other_entry = other_container.entries[idx];
                if (!other_entry.Is_Leveled_Item()) {
                    Vector_t<some<Extra_List_t*>> x_lists = other_entry.Some_Extra_Lists();
                    for (size_t idx = 0, end = x_lists.size(); idx < end; idx += 1) {
                        some<Extra_List_t*> x_list = x_lists[idx];
                        if (x_list->Is_Worn_Item()) {
                            this_container.Add_Copy_Or_Increment(other_entry.Some_Object(), x_list);
                        }
                    }
                }
            }
        }
    }

    void Reference_t::Destroy_Non_Quest_Items()
    {
        Reference_Container_t this_container(this);
        if (this_container.Is_Valid()) {
            for (size_t idx = 0, end = this_container.Count(); idx < end; idx += 1) {
                Reference_Container_Entry_t& this_entry = this_container.entries[idx];
                if (!this_entry.Is_Leveled_Item()) {
                    this_entry.Decrement_Count(this_container, sp32::_MAX_);
                    Vector_t<some<Extra_List_t*>> this_x_lists = this_entry.Some_Extra_Lists();
                    for (size_t idx = 0, end = this_x_lists.size(); idx < end; idx += 1) {
                        some<Extra_List_t*> this_x_list = this_x_lists[idx];
                        if (!this_x_list->Is_Quest_Item()) {
                            this_entry.Remove_And_Destroy(this_container, this_x_list);
                        }
                    }
                }
            }
        }
    }

    Bool_t Reference_t::Remove_Blank_Name(Bool_t whitespace_counts_as_blank)
    {
        maybe<Extra_Text_Display_t*> x_text_display = this->x_list.Get<Extra_Text_Display_t>();
        if (x_text_display) {
            maybe<String_t> name = x_text_display->Name();
            if (name.Has_Value()) {
                String_t value = name.Value();
                if (value == "" || (whitespace_counts_as_blank && !CString_t::Has_Non_Whitespace(value))) {
                    this->x_list.Remove_And_Destroy<Extra_Text_Display_t>(x_text_display());
                    return true;
                } else if (x_text_display->message || x_text_display->owning_quest) {
                    x_text_display->message = none<Message_t*>();
                    x_text_display->owning_quest = none<Quest_t*>();
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    void Reference_t::Add_Item(some<Form_t*> item, s16 delta)
    {
        SKYLIB_ASSERT_SOME(item);

        if (Is_Valid()) {
            some<Script_t*> script = Script_t::Create();
            script->Console_Add_Item(this, item, delta);
            Script_t::Destroy(script);
        }
    }

    void Reference_t::Remove_Item(some<Form_t*> item, s16 delta)
    {
        SKYLIB_ASSERT_SOME(item);

        if (Is_Valid()) {
            some<Script_t*> script = Script_t::Create();
            script->Console_Remove_Item(this, item, delta);
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

    Form_Owner_t Reference_t::This_Or_Cell_Owner()
    {
        static auto get_this_or_cell_owner = reinterpret_cast
            <Form_t*(*)(Reference_t*)>
            (Game_t::Base_Address() + Offset_e::GET_THIS_OR_CELL_OWNER);

        return get_this_or_cell_owner(this);
    }

    maybe<Actor_Base_t*> Reference_t::This_Or_Cell_Actor_Base_Owner()
    {
        return This_Or_Cell_Owner().As_Actor_Base();
    }

    maybe<Faction_t*> Reference_t::This_Or_Cell_Faction_Owner()
    {
        return This_Or_Cell_Owner().As_Faction();
    }

    maybe<Form_Owner_t> Reference_t::This_Owner()
    {
        return this->x_list.Owner();
    }

    void Reference_t::This_Owner(Form_Owner_t owner)
    {
        if (Is_Valid()) {
            some<Script_t*> script = Script_t::Create();
            if (owner) {
                script->Command(std::string("SetOwnership ") + owner()->Form_ID_String());
            } else {
                script->Command("SetOwnership");
            }
            script->Execute(this);
            Script_t::Destroy(script);
        }
    }

    maybe<maybe<Actor_Base_t*>> Reference_t::This_Actor_Base_Owner()
    {
        maybe<Form_Owner_t> owner = This_Owner();
        if (owner.Has_Value()) {
            return owner.Value().As_Actor_Base();
        } else {
            return none<maybe<Actor_Base_t*>>();
        }
    }

    void Reference_t::This_Actor_Base_Owner(maybe<Actor_Base_t*> actor_base)
    {
        This_Owner(actor_base);
    }

    maybe<maybe<Faction_t*>> Reference_t::This_Faction_Owner()
    {
        maybe<Form_Owner_t> owner = This_Owner();
        if (owner.Has_Value()) {
            return owner.Value().As_Faction();
        } else {
            return none<maybe<Faction_t*>>();
        }
    }

    void Reference_t::This_Faction_Owner(maybe<Faction_t*> faction)
    {
        This_Owner(faction);
    }

    Form_Owner_t Reference_t::Cell_Owner()
    {
        maybe<Cell_t*> cell = Cell(true);
        if (cell) {
            return cell->Owner();
        } else {
            return none<Form_t*>();
        }
    }

    void Reference_t::Push_Away(some<Actor_t*> actor, Int_t force)
    {
        SKYLIB_ASSERT_SOME(actor);

        if (Is_Valid() && Is_Attached()) {
            some<Script_t*> script = Script_t::Create();
            script->Command(std::string("PushActorAway ") + actor->Form_ID_String() + " " + std::to_string(force));
            script->Execute(this);
            Script_t::Destroy(script);
        }
    }

    void Reference_t::Apply_Havok_Impulse(Float_t x, Float_t y, Float_t z, Float_t force)
    {
        if (Is_Valid() && Is_Attached()) {
            some<Script_t*> script = Script_t::Create();
            script->Command(
                std::string("ApplyHavokImpulse ") +
                std::to_string(x) + " " +
                std::to_string(y) + " " +
                std::to_string(z) + " " +
                std::to_string(force));
            script->Execute(this);
            Script_t::Destroy(script);
        }
    }

    void Reference_t::Select_In_Console()
    {
        if (Is_Valid()) {
            some<Script_t*> script = Script_t::Create();
            script->Command(std::string("prid ") + Form_ID_String());
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

    void Reference_t::Actor_Base_Owner(some<Virtual::Callback_i*> v_callback)
    {
        SKYLIB_ASSERT_SOME(v_callback);

        Virtual::Machine_t::Ready_Scriptable<Reference_t*>(this);
        Virtual::Machine_t::Self()->Call_Method(
            this,
            SCRIPT_NAME,
            "GetActorOwner",
            none<Virtual::Arguments_i*>(),
            v_callback
        );
    }

    void Reference_t::Actor_Base_Owner(some<unique<Callback_i<maybe<Actor_Base_t*>>>> callback)
    {
        using Callback = some<unique<Callback_i<maybe<Actor_Base_t*>>>>;

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
                (*this->callback)(result ? result->As<Actor_Base_t*>() : nullptr);
            }
        };

        SKYLIB_ASSERT_SOME(callback);

        Actor_Base_Owner(new Virtual_Callback(std::move(callback)));
    }

    void Reference_t::Faction_Owner(some<Virtual::Callback_i*> v_callback)
    {
        SKYLIB_ASSERT_SOME(v_callback);

        Virtual::Machine_t::Ready_Scriptable<Reference_t*>(this);
        Virtual::Machine_t::Self()->Call_Method(
            this,
            SCRIPT_NAME,
            "GetFactionOwner",
            none<Virtual::Arguments_i*>(),
            v_callback
        );
    }

    void Reference_t::Faction_Owner(some<unique<Callback_i<maybe<Faction_t*>>>> callback)
    {
        using Callback = some<unique<Callback_i<maybe<Faction_t*>>>>;

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
                (*this->callback)(result ? result->As<Faction_t*>() : nullptr);
            }
        };

        SKYLIB_ASSERT_SOME(callback);

        Faction_Owner(new Virtual_Callback(std::move(callback)));
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

    void Reference_t::Add_Item(some<Form_t*> item,
                               Int_t count,
                               Bool_t do_silently,
                               maybe<Virtual::Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Virtual::Arguments_t
        {
        public:
            some<Form_t*>   item;
            Int_t           count;
            Bool_t          do_silently;

        public:
            Virtual_Arguments(some<Form_t*> item, Int_t count, Bool_t do_silently) :
                item(item), count(count), do_silently(do_silently)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Virtual::Variable_t>* args) override
            {
                args->Resize(3);
                args->At(0).As<Form_t*>(this->item());
                args->At(1).As<Int_t>(this->count);
                args->At(2).As<Bool_t>(this->do_silently);
                return true;
            }
        };

        SKYLIB_ASSERT_SOME(item);

        Virtual::Machine_t::Ready_Scriptable<Reference_t*>(this);
        Virtual::Machine_t::Self()->Call_Method(
            this,
            SCRIPT_NAME,
            "AddItem",
            Virtual_Arguments(item, count, do_silently),
            v_callback
        );
    }

    void Reference_t::Add_Item(some<Form_t*> item,
                               Int_t count,
                               Bool_t do_silently,
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

        SKYLIB_ASSERT_SOME(item);

        Add_Item(item, count, do_silently, new Virtual_Callback(std::move(callback)));
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

        class Close_Menus_Callback :
            public Callback_i<Bool_t>
        {
        public:
            some<Reference_t*>  self;
            Callback            callback;

        public:
            Close_Menus_Callback(some<Reference_t*> self, Callback callback) :
                self(self), callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(Bool_t) override
            {
                class Activate_Callback :
                    public Virtual::Callback_t
                {
                public:
                    Callback callback;

                public:
                    Activate_Callback(Callback callback) :
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
                this->self->Activate(Player_t::Self(), false, new Activate_Callback(std::move(this->callback)));
            }
        };

        class Actor_Open_Inventory_Callback :
            public Callback_i<>
        {
        public:
            Callback callback;

        public:
            Actor_Open_Inventory_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator()() override
            {
                if (this->callback) {
                    (*this->callback)(true);
                }
            }
        };

        if (Is_Based_On_Component_Container()) {
            maybe<Actor_t*> actor = As_Actor();
            if (actor) {
                actor->Open_Inventory(true, new Actor_Open_Inventory_Callback(std::move(callback)));
            } else {
                Virtual::Input_t::Close_Menus(new Close_Menus_Callback(this, std::move(callback)));
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

    void Reference_t::Remove_Item(some<Form_t*> form,
                                  Int_t count,
                                  Bool_t do_silently,
                                  maybe<Reference_t*> to,
                                  maybe<Virtual::Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Virtual::Arguments_t
        {
        public:
            some<Form_t*>       form;
            Int_t               count;
            Bool_t              do_silently;
            maybe<Reference_t*> to;

        public:
            Virtual_Arguments(some<Form_t*> form, Int_t count, Bool_t do_silently, maybe<Reference_t*> to) :
                form(form), count(count), do_silently(do_silently), to(to)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Virtual::Variable_t>* args) override
            {
                args->Resize(4);
                args->At(0).As<Form_t*>(this->form());
                args->At(1).As<Int_t>(this->count);
                args->At(2).As<Bool_t>(this->do_silently);
                args->At(3).As<Reference_t*>(this->to());
                return true;
            }
        };

        Virtual::Machine_t::Ready_Scriptable<Reference_t*>(this);
        Virtual::Machine_t::Self()->Call_Method(
            this,
            SCRIPT_NAME,
            "RemoveItem",
            Virtual_Arguments(form, count, do_silently, to),
            v_callback
        );
    }

    void Reference_t::Remove_Item(some<Form_t*> form,
                                  Int_t count,
                                  Bool_t do_silently,
                                  maybe<Reference_t*> to,
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

        Remove_Item(form, count, do_silently, to, new Virtual_Callback(std::move(callback)));
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
        Virtual::Machine_t::Ready_Scriptable<Reference_t*>(this);
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

    void Reference_t::Unfill_Aliases(maybe<unique<Callback_i<>>> callback)
    {
        Alias_Reference_t::Unfill(Alias_References(), std::move(callback));
    }

    void Reference_t::Log_Name_And_Type(std::string indent)
    {
        SKYLIB_LOG(indent + "Reference_t::Log_Name_And_Type");
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

        SKYLIB_LOG(indent + "}");
    }

    void Reference_t::Log_Contained_References(std::string indent)
    {
        SKYLIB_LOG(indent + "Reference_t::Log_Contained_References");
        SKYLIB_LOG(indent + "{");

        Vector_t<some<Reference_t*>> refs = Contained_References();
        for (size_t idx = 0, end = refs.size(); idx < end; idx += 1) {
            refs[idx]->Log_Name_And_Type(indent + SKYLIB_TAB);
        }

        SKYLIB_LOG(indent + "}");
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

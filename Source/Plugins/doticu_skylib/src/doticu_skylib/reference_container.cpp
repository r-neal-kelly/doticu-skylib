/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/bound_object.h"
#include "doticu_skylib/component_container.h"
#include "doticu_skylib/container_changes.h"
#include "doticu_skylib/container_changes_entry.h"
#include "doticu_skylib/container_entry.h"
#include "doticu_skylib/player.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/reference_container.h"
#include "doticu_skylib/reference_container_entry.h"

namespace doticu_skylib {

    Reference_Container_t::Reference_Container_t(some<Reference_t*> reference) :
        reference((SKYLIB_ASSERT_SOME(reference), reference)),
        extra_locker(reference->x_list.lock),
        base_container(reference->Base_Component_Container()),
        reference_container(reference->Maybe_Container_Changes()),
        entries(),
        has_changed(false)
    {
        if (Is_Valid()) {
            Vector_t<some<Bound_Object_t*>> handled_objects;

            if (this->reference_container) {
                maybe<List_t<maybe<Container_Changes_Entry_t*>>*> reference_entries = this->reference_container->entries;
                if (reference_entries && !reference_entries->Is_Empty()) {
                    for (maybe<List_t<maybe<Container_Changes_Entry_t*>>::Node_t*> it = &reference_entries->head; it; it = it->next) {
                        maybe<Container_Changes_Entry_t*> reference_entry = it->value;
                        if (reference_entry && reference_entry->bound_object) {
                            maybe<Container_Entry_t*> base_entry = none<Container_Entry_t*>();
                            base_entry = this->base_container->Maybe_Entry(reference_entry->bound_object());
                            if (base_entry) {
                                handled_objects.push_back(base_entry->bound_object());
                            }
                            this->entries.push_back(Reference_Container_Entry_t(base_entry, reference_entry));
                        }
                    }
                }
            }

            for (size_t idx = 0, end = this->base_container->container_entry_count; idx < end; idx += 1) {
                maybe<Container_Entry_t*> base_entry = this->base_container->container_entries[idx];
                if (base_entry && base_entry->bound_object && !handled_objects.Has(base_entry->bound_object())) {
                    this->entries.push_back(Reference_Container_Entry_t(base_entry, none<Container_Changes_Entry_t*>()));
                }
            }
        }
    }

    Reference_Container_t::Reference_Container_t(Reference_Container_t&& other) noexcept :
        reference(std::move(other.reference)),
        extra_locker(std::move(other.extra_locker)),
        base_container(std::move(other.base_container)),
        reference_container(std::move(other.reference_container)),
        entries(std::move(other.entries)),
        has_changed(std::move(other.has_changed))
    {
    }

    Reference_Container_t::~Reference_Container_t()
    {
        if (Is_Valid()) {
            for (size_t idx = 0, end = this->entries.size(); idx < end; idx += 1) {
                Reference_Container_Entry_t& entry = this->entries[idx];
                if (entry.reference_entry && entry.reference_entry->Should_Be_Destroyed()) {
                    this->reference_container->Remove_And_Destroy_Entry(entry.reference_entry());
                    entry.reference_entry = none<Container_Changes_Entry_t*>();
                }
            }

            if (Has_Changed()) {
                this->reference->Flag_Form_Change(Reference_t::Form_Change_Flags_e::CONTAINER);

                if (this->reference_container) {
                    this->reference_container->has_changed = true;
                }

                maybe<Actor_t*> actor = this->reference->As_Actor();
                if (actor) {
                    actor->Update_Equipment(none<unique<Callback_i<>>>());
                }
            }
        }
    }

    Bool_t Reference_Container_t::Is_Valid() const
    {
        return this->base_container != none<Container_c*>();
    }

    Bool_t Reference_Container_t::Has_Quest_Item() const
    {
        SKYLIB_ASSERT(Is_Valid());

        for (size_t idx = 0, end = this->entries.size(); idx < end; idx += 1) {
            const Reference_Container_Entry_t& entry = this->entries[idx];
            if (entry.Has_Quest_Item()) {
                return true;
            }
        }

        return false;
    }

    Bool_t Reference_Container_t::Has_Entry(some<Bound_Object_t*> object)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(object);

        for (size_t idx = 0, end = this->entries.size(); idx < end; idx += 1) {
            Reference_Container_Entry_t& entry = this->entries[idx];
            if (entry.Some_Object() == object) {
                return true;
            }
        }

        return false;
    }

    Bool_t Reference_Container_t::Has_Changed() const
    {
        SKYLIB_ASSERT(Is_Valid());

        return this->has_changed;
    }

    void Reference_Container_t::Has_Changed(Bool_t value)
    {
        SKYLIB_ASSERT(Is_Valid());

        this->has_changed = value;
    }

    some<Reference_t*> Reference_Container_t::Reference() const
    {
        SKYLIB_ASSERT(Is_Valid());

        return this->reference;
    }

    some<Container_c*> Reference_Container_t::Some_Base_Container()
    {
        SKYLIB_ASSERT(Is_Valid());

        return this->base_container();
    }

    maybe<Container_Changes_t*> Reference_Container_t::Maybe_Reference_Container()
    {
        SKYLIB_ASSERT(Is_Valid());

        return this->reference_container;
    }

    some<Container_Changes_t*> Reference_Container_t::Some_Reference_Container()
    {
        SKYLIB_ASSERT(Is_Valid());

        if (!this->reference_container) {
            Has_Changed(true);
            this->reference_container = this->reference->Some_Container_Changes()();
            SKYLIB_ASSERT(this->reference_container);
        }
        return this->reference_container();
    }

    maybe<Reference_Container_Entry_t*> Reference_Container_t::Maybe_Entry(some<Bound_Object_t*> object)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(object);

        for (size_t idx = 0, end = this->entries.size(); idx < end; idx += 1) {
            Reference_Container_Entry_t& entry = this->entries[idx];
            if (entry.Some_Object() == object) {
                return &entry;
            }
        }
        return none<Reference_Container_Entry_t*>();
    }

    some<Reference_Container_Entry_t*> Reference_Container_t::Some_Entry(some<Bound_Object_t*> object)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(object);
        SKYLIB_ASSERT(!object->Is_Leveled_Item());

        maybe<Reference_Container_Entry_t*> maybe_entry = Maybe_Entry(object);
        if (maybe_entry) {
            return maybe_entry();
        } else {
            Has_Changed(true);
            this->entries.push_back(Some_Reference_Container()->Some_Entry(object));
            return &this->entries[this->entries.size() - 1];
        }
    }

    size_t Reference_Container_t::Count() const
    {
        SKYLIB_ASSERT(Is_Valid());

        return this->entries.size();
    }

    sp32 Reference_Container_t::Count(some<Bound_Object_t*> object)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(object);

        maybe<Reference_Container_Entry_t*> maybe_entry = Maybe_Entry(object);
        if (maybe_entry) {
            return maybe_entry->Count();
        } else {
            return 0;
        }
    }

    sp32 Reference_Container_t::Increment_Count(some<Bound_Object_t*> object, sp32 amount)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(object);

        return Some_Entry(object)->Increment_Count(*this, amount);
    }

    sp32 Reference_Container_t::Decrement_Count(some<Bound_Object_t*> object, sp32 amount)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(object);

        maybe<Reference_Container_Entry_t*> maybe_entry = Maybe_Entry(object);
        if (maybe_entry) {
            return maybe_entry->Decrement_Count(*this, amount);
        } else {
            return 0;
        }
    }

    sp32 Reference_Container_t::Remove_Count_To(some<Bound_Object_t*> object, sp32 amount, some<Reference_t*> to)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(object);
        SKYLIB_ASSERT_SOME(to);

        maybe<Reference_Container_Entry_t*> maybe_entry = Maybe_Entry(object);
        if (maybe_entry) {
            return maybe_entry->Remove_Count_To(*this, amount, to);
        } else {
            return 0;
        }
    }

    sp32 Reference_Container_t::Add(some<Bound_Object_t*> object, some<Extra_List_t*> extra_list)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(object);
        SKYLIB_ASSERT_SOME(extra_list);

        return Some_Entry(object)->Add(*this, extra_list);
    }

    sp32 Reference_Container_t::Add_Copy_Or_Increment(some<Bound_Object_t*> object, some<Extra_List_t*> extra_list)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(object);
        SKYLIB_ASSERT_SOME(extra_list);

        return Some_Entry(object)->Add_Copy_Or_Increment(*this, extra_list);
    }

    sp32 Reference_Container_t::Remove(some<Bound_Object_t*> object, some<Extra_List_t*> extra_list)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(object);
        SKYLIB_ASSERT_SOME(extra_list);

        maybe<Reference_Container_Entry_t*> entry = Maybe_Entry(object);
        SKYLIB_ASSERT(entry);

        return entry->Remove(*this, extra_list);
    }

    sp32 Reference_Container_t::Remove_And_Destroy(some<Bound_Object_t*> object, some<Extra_List_t*> extra_list)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(object);
        SKYLIB_ASSERT_SOME(extra_list);

        maybe<Reference_Container_Entry_t*> entry = Maybe_Entry(object);
        SKYLIB_ASSERT(entry);

        return entry->Remove_And_Destroy(*this, extra_list);
    }

    sp32 Reference_Container_t::Remove_To(some<Bound_Object_t*> object, some<Extra_List_t*> extra_list, some<Reference_t*> to)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(object);
        SKYLIB_ASSERT_SOME(extra_list);
        SKYLIB_ASSERT_SOME(to);

        maybe<Reference_Container_Entry_t*> entry = Maybe_Entry(object);
        SKYLIB_ASSERT(entry);

        return entry->Remove_To(*this, extra_list, to);
    }

    maybe<sp32> Reference_Container_t::Try_To_Consume(some<Bound_Object_t*> object, some<Extra_List_t*> extra_list)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(object);
        SKYLIB_ASSERT_SOME(extra_list);

        maybe<Reference_Container_Entry_t*> entry = Maybe_Entry(object);
        if (entry) {
            return entry->Try_To_Consume(*this, extra_list);
        } else {
            return none<sp32>();
        }
    }

    Reference_Container_Entry_t& Reference_Container_t::operator [](size_t index)
    {
        SKYLIB_ASSERT(Is_Valid());

        return this->entries[index];
    }

    const Reference_Container_Entry_t& Reference_Container_t::operator [](size_t index) const
    {
        SKYLIB_ASSERT(Is_Valid());

        return this->entries[index];
    }

    void Reference_Container_t::Log(std::string indent)
    {
        SKYLIB_ASSERT(Is_Valid());

        SKYLIB_LOG(indent + "Reference_Container_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "Reference: %s, %s", this->reference->Any_Name(), this->reference->Form_ID_String());

        size_t entries_size = this->entries.size();
        if (entries_size > 0) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "entries:");
            for (size_t idx = 0, end = this->entries.size(); idx < end; idx += 1) {
                Reference_Container_Entry_t& entry = this->entries[idx];
                entry.Log(indent + SKYLIB_TAB + SKYLIB_TAB);
            }
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "entries: (none)");
        }

        SKYLIB_LOG(indent + "}");
    }

}

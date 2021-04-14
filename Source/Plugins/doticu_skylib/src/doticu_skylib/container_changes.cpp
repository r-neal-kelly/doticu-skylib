/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/bound_object.h"
#include "doticu_skylib/container_changes.h"
#include "doticu_skylib/container_changes_entry.h"
#include "doticu_skylib/forward_list.inl"
#include "doticu_skylib/reference.h"

namespace doticu_skylib {

    some<Container_Changes_t*> Container_Changes_t::Create(some<Reference_t*> owner)
    {
        some<Container_Changes_t*> container_changes = Game_t::Allocate<Container_Changes_t>();
        new (container_changes()) Container_Changes_t(owner);
        return container_changes;
    }

    void Container_Changes_t::Destroy(some<Container_Changes_t*> container_changes)
    {
        SKYLIB_ASSERT_SOME(container_changes);
        container_changes->~Container_Changes_t();
        Game_t::Deallocate<Container_Changes_t>(container_changes);
    }

    Container_Changes_t::Container_Changes_t(some<Reference_t*> owner) :
        entries(List_t<maybe<Container_Changes_Entry_t*>>::Create()()),
        owner(owner()),
        total_weight(1.0f), // double check
        armor_weight(1.0f), // double check
        has_changed(true),
        pad_19(0),
        pad_1A(0),
        pad_1B(0),
        pad_1C(0)
    {
        SKYLIB_ASSERT_SOME(owner);
    }

    Container_Changes_t::~Container_Changes_t()
    {
        Destroy_Entries();
        this->owner = none<Reference_t*>();
        this->total_weight = 0.0f;
        this->armor_weight = 0.0f;
        this->has_changed = false;
        this->pad_19 = 0;
        this->pad_1A = 0;
        this->pad_1B = 0;
        this->pad_1C = 0;
    }

    Bool_t Container_Changes_t::Has_Entry(some<Container_Changes_Entry_t*> entry)
    {
        SKYLIB_ASSERT_SOME(entry);

        if (this->entries && !this->entries->Is_Empty()) {
            for (maybe<List_t<maybe<Container_Changes_Entry_t*>>::Node_t*> it = &this->entries->head; it; it = it->next) {
                maybe<Container_Changes_Entry_t*> maybe_entry = it->value;
                if (maybe_entry == entry) {
                    return true;
                }
            }
            return false;
        } else {
            return false;
        }
    }

    Bool_t Container_Changes_t::Has_Entry(some<Bound_Object_t*> object)
    {
        SKYLIB_ASSERT_SOME(object);

        if (this->entries && !this->entries->Is_Empty()) {
            for (maybe<List_t<maybe<Container_Changes_Entry_t*>>::Node_t*> it = &this->entries->head; it; it = it->next) {
                maybe<Container_Changes_Entry_t*> maybe_entry = it->value;
                if (maybe_entry && maybe_entry->bound_object == object) {
                    return true;
                }
            }
            return false;
        } else {
            return false;
        }
    }

    Bool_t Container_Changes_t::Add_Entry(some<Container_Changes_Entry_t*> entry)
    {
        SKYLIB_ASSERT_SOME(entry);
        SKYLIB_ASSERT_SOME(entry->bound_object);

        if (!this->entries) {
            this->entries = List_t<maybe<Container_Changes_Entry_t*>>::Create()();
        }

        if (Has_Entry(entry->bound_object())) {
            return false;
        } else {
            this->entries->Add(entry());
            this->has_changed = true;
            return true;
        }
    }

    Bool_t Container_Changes_t::Remove_Entry(some<Container_Changes_Entry_t*> entry)
    {
        SKYLIB_ASSERT_SOME(entry);

        if (Has_Entry(entry)) {
            Bool_t did_remove = this->entries->Remove(entry());
            SKYLIB_ASSERT(did_remove);
            this->has_changed = true;
            return true;
        } else {
            return false;
        }
    }

    Bool_t Container_Changes_t::Remove_And_Destroy_Entry(some<Container_Changes_Entry_t*> entry)
    {
        SKYLIB_ASSERT_SOME(entry);

        if (Remove_Entry(entry)) {
            Container_Changes_Entry_t::Destroy(entry);
            return true;
        } else {
            return false;
        }
    }

    maybe<Container_Changes_Entry_t*> Container_Changes_t::Maybe_Entry(some<Bound_Object_t*> object)
    {
        SKYLIB_ASSERT_SOME(object);

        if (this->entries && !this->entries->Is_Empty()) {
            for (maybe<List_t<maybe<Container_Changes_Entry_t*>>::Node_t*> it = &this->entries->head; it; it = it->next) {
                maybe<Container_Changes_Entry_t*> maybe_entry = it->value;
                if (maybe_entry && maybe_entry->bound_object() == object()) {
                    return maybe_entry;
                }
            }
            return none<Container_Changes_Entry_t*>();
        } else {
            return none<Container_Changes_Entry_t*>();
        }
    }

    some<Container_Changes_Entry_t*> Container_Changes_t::Some_Entry(some<Bound_Object_t*> object)
    {
        SKYLIB_ASSERT_SOME(object);
        SKYLIB_ASSERT(!object->Is_Leveled_Item());

        if (!this->entries) {
            this->entries = List_t<maybe<Container_Changes_Entry_t*>>::Create()();
        }

        maybe<Container_Changes_Entry_t*> maybe_entry = Maybe_Entry(object);
        if (maybe_entry) {
            return maybe_entry();
        } else {
            some<Container_Changes_Entry_t*> some_entry = Container_Changes_Entry_t::Create(object);
            this->entries->Add(some_entry());
            this->has_changed = true;
            return some_entry;
        }
    }

    void Container_Changes_t::Destroy_Entries()
    {
        if (this->entries) {
            if (!this->entries->Is_Empty()) {
                for (maybe<List_t<maybe<Container_Changes_Entry_t*>>::Node_t*> it = &this->entries->head; it; it = it->next) {
                    maybe<Container_Changes_Entry_t*> entry = it->value;
                    if (entry) {
                        Container_Changes_Entry_t::Destroy(entry());
                        it->value = none<Container_Changes_Entry_t*>();
                    }
                }
            }
            List_t<maybe<Container_Changes_Entry_t*>>::Destroy(this->entries());
            this->entries = none<List_t<maybe<Container_Changes_Entry_t*>>*>();
            this->has_changed = true;
        }
    }

}

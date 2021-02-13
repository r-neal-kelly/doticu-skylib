/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/container_changes.h"
#include "doticu_skylib/container_changes_entry.h"
#include "doticu_skylib/forward_list.inl"

namespace doticu_skylib {

    maybe<Container_Changes_Entry_t*> Container_Changes_t::Maybe_Entry(some<Bound_Object_t*> object)
    {
        SKYLIB_ASSERT_SOME(object);

        if (this->entries && !this->entries->Is_Empty()) {
            for (maybe<List_t<maybe<Container_Changes_Entry_t*>>::Node_t*> it = &this->entries->head; it; it = it->next) {
                maybe<Container_Changes_Entry_t*> maybe_entry = it->value;
                if (maybe_entry && maybe_entry->object() == object()) {
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

        if (!this->entries) {
            this->entries = List_t<maybe<Container_Changes_Entry_t*>>::Create()();
        }

        maybe<Container_Changes_Entry_t*> maybe_entry = Maybe_Entry(object);
        if (maybe_entry) {
            return maybe_entry();
        } else {
            some<Container_Changes_Entry_t*> some_entry = Container_Changes_Entry_t::Create(object, 0);
            this->entries->Add(some_entry());
            this->has_changed = true;
            return some_entry;
        }
    }

    Bool_t Container_Changes_t::Add_Entry(some<Container_Changes_Entry_t*> entry)
    {
        SKYLIB_ASSERT_SOME(entry);
        SKYLIB_ASSERT_SOME(entry->object);

        if (!this->entries) {
            this->entries = List_t<maybe<Container_Changes_Entry_t*>>::Create()();
        }

        maybe<Container_Changes_Entry_t*> maybe_entry = Maybe_Entry(entry->object());
        if (maybe_entry) {
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

        if (!this->entries) {
            return false;
        } else {
            Bool_t did_remove = this->entries->Remove(entry());
            if (did_remove) {
                if (this->entries->Is_Empty()) {
                    Destroy_Entries();
                }
                this->has_changed = true;
            }
            return did_remove;
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

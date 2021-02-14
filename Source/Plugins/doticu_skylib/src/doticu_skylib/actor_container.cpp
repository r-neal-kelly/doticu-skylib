/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/actor_container.h"
#include "doticu_skylib/actor_container_entry.h"
#include "doticu_skylib/component_container.h"
#include "doticu_skylib/container_changes.h"
#include "doticu_skylib/container_changes_entry.h"
#include "doticu_skylib/container_entry.h"
#include "doticu_skylib/player.h"

namespace doticu_skylib {

    Actor_Container_t::Actor_Container_t(some<Actor_t*> actor) :
        owner(static_cast<Actor_t*>(nullptr)),
        reference_container(static_cast<Container_Changes_t*>(nullptr))
    {
        this->owner = actor;
        SKYLIB_ASSERT_SOME(this->owner);
        this->reference_container = this->owner->Container_Changes(true)();
        SKYLIB_ASSERT(this->reference_container);

        maybe<Container_c*> base_container = static_cast<maybe<Container_c*>>(this->owner->Actor_Base());
        Vector_t<some<Bound_Object_t*>> handled_objects;

        maybe<List_t<maybe<Container_Changes_Entry_t*>>*> reference_entries = this->reference_container->entries;
        if (reference_entries && !reference_entries->Is_Empty()) {
            for (maybe<List_t<maybe<Container_Changes_Entry_t*>>::Node_t*> it = &reference_entries->head; it; it = it->next) {
                maybe<Container_Changes_Entry_t*> reference_entry;
                if (reference_entry && reference_entry->object) {
                    maybe<Container_Entry_t*> base_entry = none<Container_Entry_t*>();
                    if (base_container) {
                        base_entry = base_container->Maybe_Entry(reference_entry->object());
                        if (base_entry) {
                            handled_objects.push_back(base_entry->object());
                        }
                    }
                    this->entries.push_back(Actor_Container_Entry_t(base_entry, reference_entry));
                }
            }
        }

        if (base_container) {
            for (size_t idx = 0, end = base_container->container_entry_count; idx < end; idx += 1) {
                maybe<Container_Entry_t*> base_entry = base_container->container_entries[idx];
                if (base_entry && base_entry->object && !handled_objects.Has(base_entry->object())) {
                    this->entries.push_back(Actor_Container_Entry_t(base_entry, none<Container_Changes_Entry_t*>()));
                }
            }
        }
    }

    Actor_Container_t::~Actor_Container_t()
    {
        for (size_t idx = 0, end = this->entries.size(); idx < end; idx += 1) {
            Actor_Container_Entry_t& entry = this->entries[idx];
            if (entry.reference_entry && entry.reference_entry->Should_Be_Destroyed()) {
                this->reference_container->Remove_Entry(entry.reference_entry());
                Container_Changes_Entry_t::Destroy(entry.reference_entry());
                entry.reference_entry = none<Container_Changes_Entry_t*>();
            }
        }
        this->entries.~Vector_t<Actor_Container_Entry_t>();
    }

    maybe<Actor_Container_Entry_t*> Actor_Container_t::Maybe_Entry(some<Bound_Object_t*> object)
    {
        SKYLIB_ASSERT_SOME(object);

        for (size_t idx = 0, end = this->entries.size(); idx < end; idx += 1) {
            Actor_Container_Entry_t& entry = this->entries[idx];
            if (entry.Some_Object() == object) {
                return &entry;
            }
        }
        return none<Actor_Container_Entry_t*>();
    }

    some<Actor_Container_Entry_t*> Actor_Container_t::Some_Entry(some<Bound_Object_t*> object)
    {
        SKYLIB_ASSERT_SOME(object);

        maybe<Actor_Container_Entry_t*> maybe_entry = Maybe_Entry(object);
        if (maybe_entry) {
            return maybe_entry();
        } else {
            this->entries.push_back(Actor_Container_Entry_t(this, object));
            return &this->entries[this->entries.size() - 1];
        }
    }

    Container_Entry_Count_t Actor_Container_t::Count(some<Bound_Object_t*> object)
    {
        SKYLIB_ASSERT_SOME(object);

        maybe<Actor_Container_Entry_t*> maybe_entry = Maybe_Entry(object);
        if (maybe_entry) {
            return maybe_entry->Count();
        } else {
            return 0;
        }
    }

    Container_Entry_Count_t Actor_Container_t::Increment_Count(some<Bound_Object_t*> object, Container_Entry_Count_t amount)
    {
        SKYLIB_ASSERT_SOME(object);

        if (amount > 0) {
            return Some_Entry(object)->Increment_Count(this, amount);
        } else {
            return Count(object);
        }
    }

    Container_Entry_Count_t Actor_Container_t::Decrement_Count(some<Bound_Object_t*> object, Container_Entry_Count_t amount)
    {
        SKYLIB_ASSERT_SOME(object);

        if (amount > 0) {
            maybe<Actor_Container_Entry_t*> maybe_entry = Maybe_Entry(object);
            if (maybe_entry) {
                return maybe_entry->Decrement_Count(this, amount);
            } else {
                return 0;
            }
        } else {
            return Count(object);
        }
    }

    void Actor_Container_t::Log(std::string indent)
    {

    }

}

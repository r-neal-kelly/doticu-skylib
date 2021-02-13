/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/actor_container.h"
#include "doticu_skylib/component_container.h"
#include "doticu_skylib/container_changes.h"
#include "doticu_skylib/container_changes_entry.h"
#include "doticu_skylib/container_entry.h"

namespace doticu_skylib {

    Actor_Container_t::Actor_Container_t(some<Actor_t*> actor) :
        owner(owner),
        base_container(static_cast<maybe<Container_c*>>(actor->Actor_Base())),
        reference_container(actor->Container_Changes(false))
    {
        Vector_t<some<Bound_Object_t*>> handled_objects;
        if (this->reference_container) {
            maybe<List_t<maybe<Container_Changes_Entry_t*>>*> reference_entries = this->reference_container->entries;
            if (reference_entries && !reference_entries->Is_Empty()) {
                for (maybe<List_t<maybe<Container_Changes_Entry_t*>>::Node_t*> it = &reference_entries->head; it; it = it->next) {
                    maybe<Container_Changes_Entry_t*> reference_entry;
                    if (reference_entry && reference_entry->object) {
                        maybe<Container_Entry_t*> base_entry = none<Container_Entry_t*>();
                        if (this->base_container) {
                            base_entry = this->base_container->Maybe_Entry(reference_entry->object());
                            if (base_entry) {
                                handled_objects.push_back(base_entry->object());
                            }
                        }
                        this->entries.push_back(Actor_Container_Entry_t(base_entry, reference_entry));
                    }
                }
            }
        }
        if (this->base_container) {
            for (size_t idx = 0, end = this->base_container->container_entry_count; idx < end; idx += 1) {
                maybe<Container_Entry_t*> base_entry = this->base_container->container_entries[idx];
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
                if (this->reference_container) {
                    this->reference_container->Remove_Entry(entry.reference_entry());
                }
                Container_Changes_Entry_t::Destroy(entry.reference_entry());
                entry.reference_entry = none<Container_Changes_Entry_t*>();
            }
        }
        this->entries.~Vector_t<Actor_Container_Entry_t>();
        this->reference_container = none<Container_Changes_t*>();
        this->base_container = none<Container_c*>();
    }

    void Actor_Container_t::Log(std::string indent)
    {

    }

}

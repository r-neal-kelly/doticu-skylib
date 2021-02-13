/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor_container_entry.h"
#include "doticu_skylib/container_changes_entry.h"
#include "doticu_skylib/container_entry.h"

namespace doticu_skylib {

    Actor_Container_Entry_t::Actor_Container_Entry_t(maybe<Container_Entry_t*> base_entry,
                                                     maybe<Container_Changes_Entry_t*> reference_entry) :
        base_entry(base_entry), reference_entry(reference_entry)
    {
    }

    Actor_Container_Entry_t::Actor_Container_Entry_t(const Actor_Container_Entry_t& other) :
        base_entry(other.base_entry), reference_entry(other.reference_entry)
    {
    }

    Actor_Container_Entry_t::Actor_Container_Entry_t(Actor_Container_Entry_t&& other) noexcept :
        base_entry(std::exchange(other.base_entry, none<Container_Entry_t*>())),
        reference_entry(std::exchange(other.reference_entry, none<Container_Changes_Entry_t*>()))
    {
    }

    Actor_Container_Entry_t& Actor_Container_Entry_t::operator =(const Actor_Container_Entry_t& other)
    {
        if (std::addressof(other) != this) {
            base_entry = other.base_entry;
            reference_entry = other.reference_entry;
        }
        return *this;
    }

    Actor_Container_Entry_t& Actor_Container_Entry_t::operator = (Actor_Container_Entry_t&& other) noexcept
    {
        if (std::addressof(other) != this) {
            base_entry = std::exchange(other.base_entry, none<Container_Entry_t*>());
            reference_entry = std::exchange(other.reference_entry, none<Container_Changes_Entry_t*>());
        }
        return *this;
    }

    Actor_Container_Entry_t::~Actor_Container_Entry_t()
    {
        this->reference_entry = none<Container_Changes_Entry_t*>();
        this->base_entry = none<Container_Entry_t*>();
    }

    some<Bound_Object_t*> Actor_Container_Entry_t::Object()
    {
        if (this->reference_entry) {
            return this->reference_entry->object();
        } else {
            return this->base_entry->object();
        }
    }

    Container_Entry_Count_t Actor_Container_Entry_t::Base_Count()
    {
        if (this->base_entry) {
            return this->base_entry->count;
        } else {
            return 0;
        }
    }

    Container_Entry_Count_t Actor_Container_Entry_t::Count()
    {
        if (this->reference_entry) {
            return this->reference_entry->Count(Base_Count());
        } else {
            return Base_Count();
        }
    }

    void Actor_Container_Entry_t::Log(std::string indent)
    {

    }

}

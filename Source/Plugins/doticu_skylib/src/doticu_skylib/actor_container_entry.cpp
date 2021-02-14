/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor_container.h"
#include "doticu_skylib/actor_container_entry.h"
#include "doticu_skylib/container_changes.h"
#include "doticu_skylib/container_changes_entry.h"
#include "doticu_skylib/container_entry.h"

namespace doticu_skylib {

    Actor_Container_Entry_t::Actor_Container_Entry_t(some<Actor_Container_t*> owner, some<Bound_Object_t*> object) :
        base_entry(none<Container_Entry_t*>()),
        reference_entry(none<Container_Changes_Entry_t*>())
    {
        SKYLIB_ASSERT_SOME(owner);
        SKYLIB_ASSERT_SOME(object);

        this->reference_entry = owner->reference_container->Some_Entry(object)();
        SKYLIB_ASSERT_SOME(this->reference_entry);
    }

    Actor_Container_Entry_t::Actor_Container_Entry_t(maybe<Container_Entry_t*> base_entry,
                                                     maybe<Container_Changes_Entry_t*> reference_entry) :
        base_entry(base_entry),
        reference_entry(reference_entry)
    {
        SKYLIB_ASSERT(base_entry || reference_entry);
    }

    Actor_Container_Entry_t::Actor_Container_Entry_t(const Actor_Container_Entry_t& other) :
        base_entry(other.base_entry),
        reference_entry(other.reference_entry)
    {
        SKYLIB_ASSERT(base_entry || reference_entry);
    }

    Actor_Container_Entry_t::Actor_Container_Entry_t(Actor_Container_Entry_t&& other) noexcept :
        base_entry(std::exchange(other.base_entry, none<Container_Entry_t*>())),
        reference_entry(std::exchange(other.reference_entry, none<Container_Changes_Entry_t*>()))
    {
        SKYLIB_ASSERT(base_entry || reference_entry);
    }

    Actor_Container_Entry_t& Actor_Container_Entry_t::operator =(const Actor_Container_Entry_t& other)
    {
        if (std::addressof(other) != this) {
            base_entry = other.base_entry;
            reference_entry = other.reference_entry;
            SKYLIB_ASSERT(base_entry || reference_entry);
        }
        return *this;
    }

    Actor_Container_Entry_t& Actor_Container_Entry_t::operator = (Actor_Container_Entry_t&& other) noexcept
    {
        if (std::addressof(other) != this) {
            base_entry = std::exchange(other.base_entry, none<Container_Entry_t*>());
            reference_entry = std::exchange(other.reference_entry, none<Container_Changes_Entry_t*>());
            SKYLIB_ASSERT(base_entry || reference_entry);
        }
        return *this;
    }

    Actor_Container_Entry_t::~Actor_Container_Entry_t()
    {
        this->reference_entry = none<Container_Changes_Entry_t*>();
        this->base_entry = none<Container_Entry_t*>();
    }

    some<Bound_Object_t*> Actor_Container_Entry_t::Some_Object()
    {
        if (this->reference_entry) {
            SKYLIB_ASSERT(this->reference_entry->object);
            return this->reference_entry->object();
        } else {
            SKYLIB_ASSERT(this->base_entry && this->base_entry->object);
            return this->base_entry->object();
        }
    }

    some<Container_Changes_Entry_t*> Actor_Container_Entry_t::Some_Reference_Entry(some<Actor_Container_t*> owner)
    {
        SKYLIB_ASSERT_SOME(owner);

        if (!this->reference_entry) {
            this->reference_entry = owner->reference_container->Some_Entry(Some_Object())();
            SKYLIB_ASSERT_SOME(this->reference_entry);
        }
        return this->reference_entry();
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

    Container_Entry_Count_t Actor_Container_Entry_t::Increment_Count(some<Actor_Container_t*> owner, Container_Entry_Count_t amount)
    {
        SKYLIB_ASSERT_SOME(owner);

        return Some_Reference_Entry(owner)->Increment_Delta(Base_Count(), amount);
    }

    Container_Entry_Count_t Actor_Container_Entry_t::Decrement_Count(some<Actor_Container_t*> owner, Container_Entry_Count_t amount)
    {
        SKYLIB_ASSERT_SOME(owner);

        return Some_Reference_Entry(owner)->Decrement_Delta(Base_Count(), amount);
    }

    void Actor_Container_Entry_t::Log(std::string indent)
    {

    }

}

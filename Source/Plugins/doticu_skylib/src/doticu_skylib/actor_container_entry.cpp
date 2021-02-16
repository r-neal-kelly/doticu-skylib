/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor_container.h"
#include "doticu_skylib/actor_container_entry.h"
#include "doticu_skylib/bound_object.h"
#include "doticu_skylib/container_changes.h"
#include "doticu_skylib/container_changes_entry.h"
#include "doticu_skylib/container_entry.h"

namespace doticu_skylib {

    Actor_Container_Entry_t::Actor_Container_Entry_t(some<Container_Changes_Entry_t*> reference_entry) :
        base_entry(none<Container_Entry_t*>()),
        reference_entry(reference_entry())
    {
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

    Actor_Container_Entry_t& Actor_Container_Entry_t::operator =(Actor_Container_Entry_t&& other) noexcept
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

    maybe<Leveled_Item_t*> Actor_Container_Entry_t::Maybe_Leveled_Item()
    {
        if (this->base_entry) {
            SKYLIB_ASSERT_SOME(this->base_entry->object);
            return this->base_entry->object->As_Leveled_Item();
        } else {
            return none<Leveled_Item_t*>();
        }
    }

    maybe<Container_Changes_Entry_t*> Actor_Container_Entry_t::Maybe_Reference_Entry()
    {
        return this->reference_entry;
    }

    some<Container_Changes_Entry_t*> Actor_Container_Entry_t::Some_Reference_Entry(some<Actor_Container_t*> owner)
    {
        SKYLIB_ASSERT_SOME(owner);
        SKYLIB_ASSERT(!Some_Object()->Is_Leveled_Item());

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

    Container_Entry_Count_t Actor_Container_Entry_t::Reference_Count()
    {
        if (this->reference_entry) {
            return this->reference_entry->Delta(Base_Count());
        } else {
            return 0;
        }
    }

    Container_Entry_Count_t Actor_Container_Entry_t::Extra_Lists_Count()
    {
        if (this->reference_entry) {
            return this->reference_entry->Extra_Lists_Count();
        } else {
            return 0;
        }
    }

    Container_Entry_Count_t Actor_Container_Entry_t::Count()
    {
        Container_Entry_Count_t base_count = Base_Count();
        if (this->reference_entry) {
            return this->reference_entry->Delta(base_count) + base_count;
        } else {
            return base_count;
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
        SKYLIB_LOG(indent + "Actor_Container_Entry_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "object: %s", Some_Object()->Form_ID_String());
        SKYLIB_LOG(indent + SKYLIB_TAB + "base_count: %d", Base_Count());
        SKYLIB_LOG(indent + SKYLIB_TAB + "reference_count: %d", Reference_Count());
        SKYLIB_LOG(indent + SKYLIB_TAB + "extra_lists_count: %d", Extra_Lists_Count());
        SKYLIB_LOG(indent + SKYLIB_TAB + "count: %d", Count());

        SKYLIB_LOG(indent + "}");
    }

}

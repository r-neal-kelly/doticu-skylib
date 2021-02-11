/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/container_changes_entry.h"
#include "doticu_skylib/game.inl"

namespace doticu_skylib {

    some<Container_Changes_Entry_t*> Container_Changes_Entry_t::Create(some<Bound_Object_t*> object, s32 count_delta)
    {
        some<Container_Changes_Entry_t*> container_changes_entry = Game_t::Allocate<Container_Changes_Entry_t>();
        new (container_changes_entry()) Container_Changes_Entry_t(object, count_delta);
        return container_changes_entry;
    }

    void Container_Changes_Entry_t::Destroy(some<Container_Changes_Entry_t*> container_changes_entry)
    {
        SKYLIB_ASSERT_SOME(container_changes_entry);
        container_changes_entry->~Container_Changes_Entry_t();
        Game_t::Deallocate<Container_Changes_Entry_t>(container_changes_entry);
    }

    Container_Changes_Entry_t::Container_Changes_Entry_t() :
        object(none<Bound_Object_t*>()), x_lists(none<List_t<maybe<Extra_List_t*>>*>()), count_delta(0), pad_14(0)
    {
    }

    Container_Changes_Entry_t::Container_Changes_Entry_t(some<Bound_Object_t*> object, s32 count_delta) :
        object(object()), x_lists(none<List_t<maybe<Extra_List_t*>>*>()), count_delta(count_delta), pad_14(0)
    {
    }

    Container_Changes_Entry_t::~Container_Changes_Entry_t()
    {
        this->object = none<Bound_Object_t*>();
        if (this->x_lists) {
            List_t<maybe<Extra_List_t*>>::Destroy(this->x_lists());
            this->x_lists = none<List_t<maybe<Extra_List_t*>>*>();
        }
        this->count_delta = 0;
        this->pad_14 = 0;
    }

}

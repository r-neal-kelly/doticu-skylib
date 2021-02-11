/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/forward_list.h"

#include "doticu_skylib/extra_list.h"

namespace doticu_skylib {

    class Bound_Object_t;

    class Container_Changes_Entry_t // InventoryEntryData
    {
    public:
        static some<Container_Changes_Entry_t*> Create(some<Bound_Object_t*> object, s32 count_delta);
        static void                             Destroy(some<Container_Changes_Entry_t*> container_changes_entry);

    public:
        maybe<Bound_Object_t*>                  object;         // 00
        maybe<List_t<maybe<Extra_List_t*>>*>    x_lists;        // 08
        s32                                     count_delta;    // 10
        u32                                     pad_14;         // 14

    public:
        Container_Changes_Entry_t();
        Container_Changes_Entry_t(some<Bound_Object_t*> object, s32 count_delta);
        Container_Changes_Entry_t(const Container_Changes_Entry_t& other)                   = delete;
        Container_Changes_Entry_t(Container_Changes_Entry_t&& other) noexcept               = delete;
        Container_Changes_Entry_t& operator=(const Container_Changes_Entry_t& other)        = delete;
        Container_Changes_Entry_t& operator=(Container_Changes_Entry_t&& other) noexcept    = delete;
        ~Container_Changes_Entry_t();

    public:
    };
    STATIC_ASSERT(sizeof(Container_Changes_Entry_t) == 0x18);

}

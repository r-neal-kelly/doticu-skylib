/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/container_entry_count.h"
#include "doticu_skylib/forward_list.h"

namespace doticu_skylib {

    class Bound_Object_t;
    class Extra_List_t;

    class Container_Changes_Entry_t // InventoryEntryData
    {
    public:
        static some<Container_Changes_Entry_t*> Create(some<Bound_Object_t*> object, s32 delta);
        static void                             Destroy(some<Container_Changes_Entry_t*> container_changes_entry);

    public:
        maybe<Bound_Object_t*>                  object;     // 00
        maybe<List_t<maybe<Extra_List_t*>>*>    x_lists;    // 08
        s32                                     delta;      // 10
        u32                                     pad_14;     // 14

    public:
        Container_Changes_Entry_t();
        Container_Changes_Entry_t(some<Bound_Object_t*> object, s32 delta);
        Container_Changes_Entry_t(const Container_Changes_Entry_t& other)                   = delete;
        Container_Changes_Entry_t(Container_Changes_Entry_t&& other) noexcept;
        Container_Changes_Entry_t& operator=(const Container_Changes_Entry_t& other)        = delete;
        Container_Changes_Entry_t& operator=(Container_Changes_Entry_t&& other) noexcept;
        ~Container_Changes_Entry_t();

    public:
        s32 Extra_Lists_Count();

        s32 Minimum_Delta(Container_Entry_Count_t container_entry_count);
        s32 Maximum_Delta(Container_Entry_Count_t container_entry_count);
        s32 Delta(Container_Entry_Count_t container_entry_count);

        s32 Increment_Delta(Container_Entry_Count_t container_entry_count, s32 amount);
        s32 Decrement_Delta(Container_Entry_Count_t container_entry_count, s32 amount);

        s32 Add_Extra_List(Container_Entry_Count_t container_entry_count, some<Extra_List_t*> extra_list);
        s32 Remove_Extra_List(Container_Entry_Count_t container_entry_count, some<Extra_List_t*> extra_list);

        s32 Increment_Extra_List_Count(Container_Entry_Count_t container_entry_count, some<Extra_List_t*> extra_list, s16 amount);
        s32 Decrement_Extra_List_Count(Container_Entry_Count_t container_entry_count, some<Extra_List_t*> extra_list, s16 amount);

    public:
        void Log(std::string indent);
    };
    STATIC_ASSERT(sizeof(Container_Changes_Entry_t) == 0x18);

}

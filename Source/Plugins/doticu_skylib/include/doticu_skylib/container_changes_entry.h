/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/container_entry_count.h"
#include "doticu_skylib/forward_list.h"

namespace doticu_skylib {

    class Bound_Object_t;
    class Extra_List_t;

    class Container_Changes_Entry_t // InventoryEntryData
    {
    public:
        static some<Container_Changes_Entry_t*> Create(some<Bound_Object_t*> object);
        static void                             Destroy(some<Container_Changes_Entry_t*> container_changes_entry);

    public:
        maybe<Bound_Object_t*>                  object;     // 00
        maybe<List_t<maybe<Extra_List_t*>>*>    x_lists;    // 08
        s32                                     delta;      // 10
        u32                                     pad_14;     // 14

    public:
        Container_Changes_Entry_t();
        Container_Changes_Entry_t(some<Bound_Object_t*> object);
        Container_Changes_Entry_t(const Container_Changes_Entry_t& other)                   = delete;
        Container_Changes_Entry_t(Container_Changes_Entry_t&& other) noexcept;
        Container_Changes_Entry_t& operator=(const Container_Changes_Entry_t& other)        = delete;
        Container_Changes_Entry_t& operator=(Container_Changes_Entry_t&& other) noexcept;
        ~Container_Changes_Entry_t();

    public:
        Container_Entry_Count_t         Count(Container_Entry_Count_t base_count);
        s32                             Delta(Container_Entry_Count_t base_count);
        s32                             Minimum_Delta(Container_Entry_Count_t base_count);
        s32                             Maximum_Delta(Container_Entry_Count_t base_count);
        s32                             Increment_Delta(Container_Entry_Count_t base_count, Container_Entry_Count_t amount);
        s32                             Decrement_Delta(Container_Entry_Count_t base_count, Container_Entry_Count_t amount);

        Vector_t<some<Extra_List_t*>>   Extra_Lists();
        Container_Entry_Count_t         Extra_Lists_Count();
        s32                             Add(Container_Entry_Count_t base_count, some<Extra_List_t*> extra_list);
        s32                             Remove(Container_Entry_Count_t base_count, some<Extra_List_t*> extra_list);
        s32                             Remove_And_Destroy(Container_Entry_Count_t base_count, some<Extra_List_t*> extra_list);
        s32                             Increment_Count(Container_Entry_Count_t base_count, some<Extra_List_t*> extra_list, s16 amount);
        s32                             Decrement_Count(Container_Entry_Count_t base_count, some<Extra_List_t*> extra_list, s16 amount);
        Bool_t                          Try_To_Consume(some<Extra_List_t*> extra_list);

        Bool_t                          Has_Quest_Item();
        Bool_t                          Should_Be_Destroyed();

        void                            Destroy_Extra_Lists();

    public:
        void Log(std::string indent);
    };
    STATIC_ASSERT(sizeof(Container_Changes_Entry_t) == 0x18);

    /*
        Extra_Type_e that we know we can find on these x_lists:
            OUTFIT
            OWNER
            LEVELED_ITEM
            COUNT
            UNIQUE_ID
            ALIASES
            REFERENCE_HANDLE
            FROM_ALIAS
            WORN
            WORN_LEFT
            TEXT_DISPLAY
            HEALTH
            CHARGE
    */

}

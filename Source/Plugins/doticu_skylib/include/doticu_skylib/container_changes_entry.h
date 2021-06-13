/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/enum_extra_type.h"
#include "doticu_skylib/forward_list.h"
#include "doticu_skylib/sp32.h"

namespace doticu_skylib {

    class Bound_Object_t;
    class Extra_List_t;

    class Container_Changes_Entry_t // InventoryEntryData
    {
    public:
        class Extra_List_Copy_Filter_t :
            public Filter_i<Extra_Type_e>
        {
        public:
            virtual Bool_t operator ()(Extra_Type_e extra_type) override;
        };

    public:
        static Extra_List_Copy_Filter_t extra_list_copy_filter;

    public:
        static some<Container_Changes_Entry_t*> Create(some<Bound_Object_t*> object);
        static void                             Destroy(some<Container_Changes_Entry_t*> container_changes_entry);

        static some<Extra_List_t*>              Some_Extra_List(sp32 count);
        static maybe<Extra_List_t*>             Maybe_Extra_List_Copy(some<Extra_List_t*> extra_list);
        static some<Extra_List_t*>              Some_Extra_List_Copy(some<Extra_List_t*> extra_list);

    public:
        maybe<Bound_Object_t*>                  bound_object;   // 00
        maybe<List_t<maybe<Extra_List_t*>>*>    x_lists;        // 08
        s32                                     delta;          // 10
        u32                                     pad_14;         // 14

    public:
        Container_Changes_Entry_t();
        Container_Changes_Entry_t(some<Bound_Object_t*> object);
        Container_Changes_Entry_t(const Container_Changes_Entry_t& other)                   = delete;
        Container_Changes_Entry_t(Container_Changes_Entry_t&& other) noexcept;
        Container_Changes_Entry_t& operator=(const Container_Changes_Entry_t& other)        = delete;
        Container_Changes_Entry_t& operator=(Container_Changes_Entry_t&& other) noexcept;
        ~Container_Changes_Entry_t();

    public:
        s32                             Delta(sp32 base_count);
        s32                             Minimum_Delta(sp32 base_count);
        s32                             Maximum_Delta(sp32 base_count);
        s32                             Increment_Delta(sp32 base_count, sp32 amount);
        s32                             Decrement_Delta(sp32 base_count, sp32 amount);

        Vector_t<some<Extra_List_t*>>   Extra_Lists();
        sp32                            Extra_Lists_Count();
        s32                             Add(sp32 base_count, some<Extra_List_t*> extra_list);
        s32                             Add_Copy_Or_Increment(sp32 base_count, some<Extra_List_t*> extra_list);
        s32                             Remove(sp32 base_count, some<Extra_List_t*> extra_list);
        s32                             Remove_And_Destroy(sp32 base_count, some<Extra_List_t*> extra_list);
        s32                             Remove_To(sp32 base_count,
                                                  some<Extra_List_t*> extra_list,
                                                  maybe<Reference_t*> this_owner,
                                                  some<Reference_t*> new_owner);
        s32                             Increment_Count(sp32 base_count, some<Extra_List_t*> extra_list, s16 amount);
        s32                             Decrement_Count(sp32 base_count, some<Extra_List_t*> extra_list, s16 amount);
        maybe<s32>                      Try_To_Consume(sp32 base_count, some<Extra_List_t*> extra_list);

        Bool_t                          Has_Quest_Item() const;
        Bool_t                          Should_Be_Destroyed();

        void                            Destroy_Extra_Lists();

    public:
        void    Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Container_Changes_Entry_t) == 0x18);

}

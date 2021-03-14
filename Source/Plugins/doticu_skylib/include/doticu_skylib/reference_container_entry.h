/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/container_entry_count.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Bound_Object_t;
    class Container_Entry_t;
    class Container_Changes_Entry_t;
    class Extra_List_t;
    class Leveled_Item_t;
    class Reference_Container_t;

    class Reference_Container_Entry_t
    {
    public:
        maybe<Container_Entry_t*>           base_entry;
        maybe<Container_Changes_Entry_t*>   reference_entry;

    public:
        Reference_Container_Entry_t(some<Container_Changes_Entry_t*> reference_entry);
        Reference_Container_Entry_t(maybe<Container_Entry_t*> base_entry, maybe<Container_Changes_Entry_t*> reference_entry);
        Reference_Container_Entry_t(const Reference_Container_Entry_t& other);
        Reference_Container_Entry_t(Reference_Container_Entry_t&& other) noexcept;
        Reference_Container_Entry_t& operator =(const Reference_Container_Entry_t& other);
        Reference_Container_Entry_t& operator =(Reference_Container_Entry_t&& other) noexcept;
        ~Reference_Container_Entry_t();

    public:
        Bool_t                              Is_Valid();
        Bool_t                              Is_Leveled_Item();
        Bool_t                              Has_Quest_Item();

        some<Bound_Object_t*>               Some_Object();
        maybe<Leveled_Item_t*>              Maybe_Leveled_Item();
        maybe<Container_Changes_Entry_t*>   Maybe_Reference_Entry();
        some<Container_Changes_Entry_t*>    Some_Reference_Entry(some<Reference_Container_t*> owner);
        Vector_t<some<Extra_List_t*>>       Some_Extra_Lists();

        Container_Entry_Count_t             Base_Count();
        Container_Entry_Count_t             Reference_Count();
        Container_Entry_Count_t             Extra_Lists_Count();
        Container_Entry_Count_t             Non_Extra_Lists_Count();
        Container_Entry_Count_t             Count();

        Container_Entry_Count_t             Increment_Count(some<Reference_Container_t*> owner, Container_Entry_Count_t amount);
        Container_Entry_Count_t             Decrement_Count(some<Reference_Container_t*> owner, Container_Entry_Count_t amount);

        Container_Entry_Count_t             Add(some<Reference_Container_t*> owner, some<Extra_List_t*> extra_list);
        Container_Entry_Count_t             Add_Copy_Or_Increment(some<Reference_Container_t*> owner, some<Extra_List_t*> extra_list);
        Container_Entry_Count_t             Remove(some<Extra_List_t*> extra_list);
        Container_Entry_Count_t             Remove_And_Destroy(some<Extra_List_t*> extra_list);
        Container_Entry_Count_t             Increment_Count(some<Extra_List_t*> extra_list, s16 amount);
        Container_Entry_Count_t             Decrement_Count(some<Extra_List_t*> extra_list, s16 amount);
        Bool_t                              Try_To_Consume(some<Extra_List_t*> extra_list);

    public:
        void Log(std::string indent = "");
    };

}

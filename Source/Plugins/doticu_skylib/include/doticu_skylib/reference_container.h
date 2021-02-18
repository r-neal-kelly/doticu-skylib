/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/reference_container_entry.h"
#include "doticu_skylib/collections.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    // we may want to rename Container_Entry_t to Component_Container_Entry_t and Container_c to Component_Container_t

    class Bound_Object_t;
    class Container_c;
    class Container_Changes_t;
    class Container_Changes_Entry_t;
    class Reference_t;

    class Reference_Container_t
    {
    public:
        some<Reference_t*>                      reference;
        some<Container_c*>                      base_container;
        maybe<Container_Changes_t*>             reference_container;
        Vector_t<Reference_Container_Entry_t>   entries;

    public:
        Reference_Container_t(some<Reference_t*> reference);
        Reference_Container_t(const Reference_Container_t& other)                   = delete;
        Reference_Container_t(Reference_Container_t&& other) noexcept               = delete;
        Reference_Container_t& operator =(const Reference_Container_t& other)       = delete;
        Reference_Container_t& operator =(Reference_Container_t&& other) noexcept   = delete;
        ~Reference_Container_t();

    public:
        Bool_t                              Is_Valid();

        some<Container_c*>                  Some_Base_Container();
        maybe<Container_Changes_t*>         Maybe_Reference_Container();
        some<Container_Changes_t*>          Some_Reference_Container();

        maybe<Reference_Container_Entry_t*> Maybe_Entry(some<Bound_Object_t*> object);
        some<Reference_Container_Entry_t*>  Some_Entry(some<Bound_Object_t*> object);

        Container_Entry_Count_t             Count(some<Bound_Object_t*> object);

        Container_Entry_Count_t             Increment_Count(some<Bound_Object_t*> object, Container_Entry_Count_t amount);
        Container_Entry_Count_t             Decrement_Count(some<Bound_Object_t*> object, Container_Entry_Count_t amount);

        Container_Entry_Count_t             Add(some<Bound_Object_t*> object, some<Extra_List_t*> extra_list);
        Container_Entry_Count_t             Remove(some<Bound_Object_t*> object, some<Extra_List_t*> extra_list);
        Container_Entry_Count_t             Remove_And_Destroy(some<Bound_Object_t*> object, some<Extra_List_t*> extra_list);
        Bool_t                              Try_To_Consume(some<Bound_Object_t*> object, some<Extra_List_t*> extra_list);

    public:
        void Log(std::string indent = "");
    };

}

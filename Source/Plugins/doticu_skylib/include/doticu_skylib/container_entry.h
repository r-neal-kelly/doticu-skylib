/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/container_entry_count.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Bound_Object_t;
    class Container_Entry_Extra_t;
    class Leveled_Item_t;
    class Reference_t;

    class Container_Entry_t // ContainerObject
    {
    public:
        Raw_Container_Entry_Count_t     count;          // 00
        u32                             pad_04;         // 04
        maybe<Bound_Object_t*>          bound_object;   // 08
        maybe<Container_Entry_Extra_t*> extra;          // 10 (COED - Container Object Extra Data)

    public:
        Container_Entry_Count_t Count();
        void                    Count(Container_Entry_Count_t count);

        void                    Add_Item_To(some<Reference_t*> reference);
    };
    STATIC_ASSERT(sizeof(Container_Entry_t) == 0x18);

}

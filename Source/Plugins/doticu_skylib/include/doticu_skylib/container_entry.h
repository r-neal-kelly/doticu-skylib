/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"
#include "doticu_skylib/sp32.h"

namespace doticu_skylib {

    class Bound_Object_t;
    class Container_Entry_Extra_t;
    class Leveled_Item_t;
    class Reference_t;

    class Container_Entry_t // ContainerObject
    {
    public:
        sp32                            count;          // 00
        u32                             pad_04;         // 04
        maybe<Bound_Object_t*>          bound_object;   // 08
        maybe<Container_Entry_Extra_t*> extra;          // 10 (COED - Container Object Extra Data)

    public:
        sp32    Count();
        void    Count(sp32 count);

        void    Add_Item_To(some<Reference_t*> reference);
    };
    STATIC_ASSERT(sizeof(Container_Entry_t) == 0x18);

}

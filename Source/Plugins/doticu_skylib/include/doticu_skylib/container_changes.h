/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/forward_list.h"

namespace doticu_skylib {

    class Bound_Object_t;
    class Container_Changes_Entry_t;
    class Reference_t;

    class Container_Changes_t // InventoryChanges
    {
    public:
        static some<Container_Changes_t*>   Create(some<Reference_t*> owner);
        static void                         Destroy(some<Container_Changes_t*> container_changes);

    public:
        maybe<List_t<maybe<Container_Changes_Entry_t*>>*>   entries;        // 00 (this is probably a some<>)
        maybe<Reference_t*>                                 owner;          // 08 ("")
        Float_t                                             total_weight;   // 10
        Float_t                                             armor_weight;   // 14
        Bool_t                                              has_changed;    // 18
        u8                                                  pad_19;         // 19
        u8                                                  pad_1A;         // 1A
        u8                                                  pad_1B;         // 1B
        u32                                                 pad_1C;         // 1C

    public:
        Container_Changes_t(some<Reference_t*> owner);
        ~Container_Changes_t();

    public:
        Bool_t                              Has_Entry(some<Container_Changes_Entry_t*> entry);
        Bool_t                              Has_Entry(some<Bound_Object_t*> object);
        Bool_t                              Add_Entry(some<Container_Changes_Entry_t*> entry);
        Bool_t                              Remove_Entry(some<Container_Changes_Entry_t*> entry);
        Bool_t                              Remove_And_Destroy_Entry(some<Container_Changes_Entry_t*> entry);

        maybe<Container_Changes_Entry_t*>   Maybe_Entry(some<Bound_Object_t*> object);
        some<Container_Changes_Entry_t*>    Some_Entry(some<Bound_Object_t*> object);

        void                                Destroy_Entries();
    };
    STATIC_ASSERT(sizeof(Container_Changes_t) == 0x20);

}

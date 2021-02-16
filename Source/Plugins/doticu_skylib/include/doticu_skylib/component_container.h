/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_form_data.h"
#include "doticu_skylib/container_entry_count.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Bound_Object_t;
    class Container_Entry_t;

    class Container_c : public Form_Data_c // TESContainer
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E15488, // 513941
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Container_c(); // 0

    public:
        maybe<maybe<Container_Entry_t*>*>   container_entries;      // 08 (CNTO - Container Object)
        u32                                 container_entry_count;  // 10 (COCT - Container Count)
        u32                                 pad_14;                 // 14

    public:
        maybe<Container_Entry_t*>   Maybe_Entry(some<Bound_Object_t*> object);
        Container_Entry_Count_t     Entry_Count(some<Bound_Object_t*> object);
    };
    STATIC_ASSERT(sizeof(Container_c) == 0x18);

}

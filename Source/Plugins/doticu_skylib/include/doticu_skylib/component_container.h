/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/atomic_number.h"
#include "doticu_skylib/component_form_data.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/sp32.h"

namespace doticu_skylib {

    class Bound_Object_t;
    class Container_Entry_t;
    class Reference_t;

    class Container_c :     // TESContainer
        public Form_Data_c  // 00
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E15488, // 513941
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Container_c(); // 0

    public:
        maybe<maybe<Container_Entry_t*>*>   container_entries;      // 08 (CNTO - Container Object)
        Atomic_Number_t<u32>                container_entry_count;  // 10 (COCT - Container Count)
        u32                                 pad_14;                 // 14

    public:
        maybe<Container_Entry_t*>   Maybe_Entry(some<Bound_Object_t*> bound_object);
        sp32                        Entry_Count(some<Bound_Object_t*> bound_object);

        void                        Container_Add_Items_To(some<Reference_t*> reference);
    };
    STATIC_ASSERT(sizeof(Container_c) == 0x18);

}

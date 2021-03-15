/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/form_id.h"

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Container_Changes_t;

    class Extra_Container_Changes_t :   // ExtraContainerChanges
        public Extra_Data_t             // 00
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::CONTAINER_CHANGES,
        };

        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                V_TABLE = 0x0152F260, // 229886
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Extra_Container_Changes_t*> Create();
        static void                             Destroy(some<Extra_Container_Changes_t*> x_container_changes);

    public:
        virtual ~Extra_Container_Changes_t(); // 0

    public:
        maybe<Container_Changes_t*> container_changes; // 10
    };
    STATIC_ASSERT(sizeof(Extra_Container_Changes_t) == 0x18);

}

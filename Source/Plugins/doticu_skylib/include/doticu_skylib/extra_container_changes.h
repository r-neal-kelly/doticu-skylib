/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/form_id.h"

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Container_Changes_t;

    class Container_Changes_x : public Data_x // ExtraContainerChanges
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
                V_TABLE = 0x0152F260,
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Container_Changes_x();

    public:
        Container_Changes_t* container_changes; // 10
    };
    STATIC_ASSERT(sizeof(Container_Changes_x) == 0x18);

}

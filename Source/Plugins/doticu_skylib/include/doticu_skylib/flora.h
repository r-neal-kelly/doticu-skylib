/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "doticu_skylib/component_harvest.h"

#include "doticu_skylib/activator.h"

namespace doticu_skylib {

    class Flora_t :
        public Activator_t, // 00
        public Harvest_c    // C8
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::FLORA,
        };

    public:
        virtual ~Flora_t(); // 00
    };
    STATIC_ASSERT(sizeof(Flora_t) == 0xE8);

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/season.h"

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Bound_Object_t;

    class Harvest_c : public Form_Data_c // TESProduceForm
    {
    public:
        virtual ~Harvest_c(); // 0

        void*           harvest_sound;                      // 08
        Bound_Object_t* harvest_item;                       // 10
        s8              harvest_chance[Season_e::_END_];    // 18
        u32             pad_1C;                             // 1C
    };
    STATIC_ASSERT(sizeof(Harvest_c) == 0x20);

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Race_t;

    class Race_c : public Form_Data_c // TESRaceForm
    {
    public:
        virtual ~Race_c(); // 0

        Race_t* race; // 0
    };
    STATIC_ASSERT(sizeof(Race_c) == 0x10);

}

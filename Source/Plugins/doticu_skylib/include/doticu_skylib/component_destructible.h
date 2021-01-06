/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Destructible_c : public Form_Data_c // BGSDestructibleObjectForm
    {
    public:
        virtual ~Destructible_c(); // 0

        void* unk_8; // 8
    };
    STATIC_ASSERT(sizeof(Destructible_c) == 0x10);

}

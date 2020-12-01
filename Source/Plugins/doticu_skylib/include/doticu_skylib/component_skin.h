/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Skin_c : public Form_Data_c // BGSSkinForm
    {
    public:
        virtual ~Skin_c(); // 0

        void* unk_8; // 8
    };
    STATIC_ASSERT(sizeof(Skin_c) == 0x10);

}

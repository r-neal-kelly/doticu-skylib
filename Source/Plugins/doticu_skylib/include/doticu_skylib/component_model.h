/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/string.h"

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Model_c :         // TESModel
        public Form_Data_c  // 00
    {
    public:
        virtual ~Model_c(); // 0

    public:
        String_t    model;              // 08
        void*       textures;           // 10
        void*       model_addons;       // 18
        u16         texture_count;      // 20
        u16         model_addon_count;  // 22
        u32         pad_24;             // 24
    };
    STATIC_ASSERT(sizeof(Model_c) == 0x28);

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_form_data.h"
#include "doticu_skylib/string.h"

namespace doticu_skylib {

    class Texture_c :       // TESTexture
        public Form_Data_c  // 00
    {
    public:
        virtual ~Texture_c(); // 0

    public:
        String_t texture_name; // 8
    };
    STATIC_ASSERT(sizeof(Texture_c) == 0x10);

}

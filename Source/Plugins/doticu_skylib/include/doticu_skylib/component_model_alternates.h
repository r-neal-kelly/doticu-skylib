/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

#include "doticu_skylib/component_model.h"

namespace doticu_skylib {

    class Model_Alternates_c : public Model_c // TESModelTextureSwap
    {
    public:
        virtual ~Model_Alternates_c(); // 0

        void*   alternate_textures;         // 28
        u32     alternate_texture_count;    // 30
        u32     pad_34;                     // 34
    };
    STATIC_ASSERT(sizeof(Model_Alternates_c) == 0x38);

}

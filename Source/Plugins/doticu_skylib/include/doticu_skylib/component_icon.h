/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/string.h"

#include "doticu_skylib/component_texture.h"

namespace doticu_skylib {

    class Icon_c : public Texture_c // TESIcon
    {
    public:
        virtual ~Icon_c(); // 0
    };
    STATIC_ASSERT(sizeof(Icon_c) == 0x10);

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Color_t;
    class Texture_Set_t;

    class Actor_Head_Data_t // HeadRelatedData
    {
    public:
        maybe<Color_t*>         hair_color; // 00 (HCLF)
        maybe<Texture_Set_t*>   head_skin;  // 08 (FTST)
    };
    STATIC_ASSERT(sizeof(Actor_Head_Data_t) == 0x10);

}

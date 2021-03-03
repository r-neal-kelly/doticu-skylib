/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_face_morph_type.h"
#include "doticu_skylib/enum_face_part_type.h"
#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Actor_Face_Data_t // FaceData
    {
    public:
        Float_t face_morphs[Face_Morph_Type_e::_TOTAL_];    // 00 (NAM9)
        s32     face_parts[Face_Part_Type_e::_TOTAL_];      // 4C (NAMA)
    };
    STATIC_ASSERT(sizeof(Actor_Face_Data_t) == 0x5C);

}

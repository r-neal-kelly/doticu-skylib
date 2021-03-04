/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/ni_matrix.h"
#include "doticu_skylib/ni_point.h"

namespace doticu_skylib {

    class NI_Transform_t // NiTransform
    {
    public:
        NI_Matrix_3_t   rotation;       // 00
        NI_Point_3_t    translation;    // 24
        Float_t         scale;          // 30

    public:
        void Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(NI_Transform_t) == 0x34);

}

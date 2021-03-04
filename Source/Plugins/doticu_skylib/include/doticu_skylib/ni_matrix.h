/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class NI_Matrix_3_t // NiMatrix3
    {
    public:
        Float_t matrix[3][3];

    public:
        void Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(NI_Matrix_3_t) == 0x24);

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class NI_Point_3_t  // NiPoint3
    {
    public:
        Float_t x; // 0
        Float_t y; // 4
        Float_t z; // 8

    public:
        NI_Point_3_t();
        NI_Point_3_t(const NI_Point_3_t& other);
        NI_Point_3_t(NI_Point_3_t&& other) noexcept;
        NI_Point_3_t& operator =(const NI_Point_3_t& other);
        NI_Point_3_t& operator =(NI_Point_3_t&& other) noexcept;
        ~NI_Point_3_t();

    public:
        void Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(NI_Point_3_t) == 0xC);

}

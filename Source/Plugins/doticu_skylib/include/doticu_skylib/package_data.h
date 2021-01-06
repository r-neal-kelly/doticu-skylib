/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Package_t;
    class Package_Value_t;

    class Package_Data_t
    {
    public:
        virtual ~Package_Data_t(); // 0

    public:
        Package_Value_t**   values;             // 08
        void*               data_10;            // 10 Variable Size, probably an array/hashmap (** ptr to ptrs), repeats more among like packages
        u16                 value_count;        // 18
        u8                  marker;             // 1A XNAM
        u8                  uint_1B;            // 1B
        Bool_t              bool_1C;            // 1C
        u8                  pad_1D;             // 1D
        u16                 pad_1E;             // 1E
        void*               shared_20;          // 20 (connected with template. procedures or inputs)
        void*               shared_28;          // 28 (connected with template. procedures or inputs)
        Package_t*          package_template;   // 30
        u16                 version;            // 38
        u16                 uint_3A;            // 3A
        Bool_t              bool_3C;            // 3C
        u8                  pad_3D;             // 3D
        u16                 pad_3E;             // 3E
    };
    STATIC_ASSERT(sizeof(Package_Data_t) == 0x40);

}

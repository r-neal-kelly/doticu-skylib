/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_package_location.h"

#include "doticu_skylib/reference_handle.h"

namespace doticu_skylib {

    class Form_t;

    class Package_Location_t
    {
    public:
        union Location_u
        {
            Reference_Handle_t  handle;
            Form_t*             form;
        };
        STATIC_ASSERT(sizeof(Location_u) == 0x08);

    public:
        virtual ~Package_Location_t();

    public:
        Package_Location_e  type;       // 08
        u8                  pad_09;     // 09
        u16                 pad_0A;     // 0A
        u32                 radius;     // 0C
        Location_u          location;   // 10
    };
    STATIC_ASSERT(sizeof(Package_Location_t) == 0x18);

}

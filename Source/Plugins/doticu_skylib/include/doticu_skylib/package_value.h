/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_package_value.h"

namespace doticu_skylib {

    class Package_Value_t
    {
    public:
        virtual ~Package_Value_t(); // 0

    public:
        Package_Value_e Type() const;
    };
    STATIC_ASSERT(sizeof(Package_Value_t) == 0x08);

}

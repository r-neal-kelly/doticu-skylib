/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"

#include "doticu_skylib/activator.h"
#include "doticu_skylib/enum_script_type.h"

namespace doticu_skylib {

    class Furniture_t : public Activator_t
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::FURNITURE,
        };

    public:
        virtual ~Furniture_t(); // 0

    public:
        Byte_t data[0x28]; // C8
    };
    STATIC_ASSERT(sizeof(Furniture_t) == 0xF0);

}

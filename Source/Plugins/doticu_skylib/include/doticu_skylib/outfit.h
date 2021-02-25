/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/dynamic_array.h"

#include "doticu_skylib/form.h"
#include "doticu_skylib/enum_script_type.h"

namespace doticu_skylib {

    class Outfit_t :    // BGSOutfit
        public Form_t   // 00
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::OUTFIT,
        };

    public:
        virtual ~Outfit_t(); // 0

    public:
        Array_t<Form_t*> entries; // 20
    };
    STATIC_ASSERT(sizeof(Outfit_t) == 0x38);

}

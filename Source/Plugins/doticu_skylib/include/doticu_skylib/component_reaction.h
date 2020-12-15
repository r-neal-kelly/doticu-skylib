/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/forward_list.h"

#include "doticu_skylib/component_form_data.h"

#include "doticu_skylib/form_type.h"

namespace doticu_skylib {

    class Reaction_c : public Form_Data_c
    {
    public:
        virtual ~Reaction_c(); // 00

        List_t<void*>   reactions;          // 08
        Form_Type_e     reaction_form_type; // 18
        u8              pad_19;             // 19
        u16             pad_1A;             // 1A
        u32             pad_1C;             // 1C
    };
    STATIC_ASSERT(sizeof(Reaction_c) == 0x20);

}

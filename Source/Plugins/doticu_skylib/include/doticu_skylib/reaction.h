/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_reaction_type.h"
#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Form_t;

    class Reaction_t    // GROUP_REACTION
    {
    public:
        maybe<Form_t*>  form;           // 00
        s32             modifier;       // 08
        Reaction_Type_e reaction_type;  // 0C

    public:
        void    Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Reaction_t) == 0x10);

}

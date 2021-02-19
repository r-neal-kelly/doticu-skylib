/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_actor_value_modifier.h"
#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Actor_Value_Modifiers_t // Modifiers
    {
    public:
        Float_t modifiers[Actor_Value_Modifier_e::_TOTAL_]; // 00
    };
    STATIC_ASSERT(sizeof(Actor_Value_Modifiers_t) == 0xC);

}

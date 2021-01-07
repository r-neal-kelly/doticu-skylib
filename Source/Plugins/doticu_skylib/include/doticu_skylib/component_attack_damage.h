/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Attack_Damage_c : public Form_Data_c // TESAttackDamageForm
    {
    public:
        virtual ~Attack_Damage_c(); // 0

    public:
        u16 attack_damage;  // 08
        u16 pad_0A;         // 0A
        u32 pad_0C;         // 0C
    };
    STATIC_ASSERT(sizeof(Attack_Damage_c) == 0x10);

}

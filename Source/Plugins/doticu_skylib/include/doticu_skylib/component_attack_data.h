/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Attack_Data_c : public Form_Data_c // BGSAttackDataForm
    {
    public:
        virtual ~Attack_Data_c(); // 0

        void* unk_8; // 08
    };
    STATIC_ASSERT(sizeof(Attack_Data_c) == 0x10);

}

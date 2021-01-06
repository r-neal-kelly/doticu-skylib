/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "doticu_skylib/component_form_data.h"
#include "doticu_skylib/component_model_alternates.h"

namespace doticu_skylib {

    class Biped_Model_c : public Form_Data_c // TESBipedModelForm
    {
    public:
        virtual ~Biped_Model_c(); // 0

        Model_Alternates_c  male_alternates;    // 08
        Model_Alternates_c  female_alternates;  // 40
        Byte_t              unk_78[0x78];       // 78
    };
    STATIC_ASSERT(sizeof(Biped_Model_c) == 0xF0);

}

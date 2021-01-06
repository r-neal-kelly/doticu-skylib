/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_armor.h"
#include "doticu_skylib/enum_biped_slots.h"

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Biped_Object_c : public Form_Data_c // BGSBipedObjectForm
    {
    public:
        virtual ~Biped_Object_c(); // 0

        Biped_Slots_e   biped_slots;
        Armor_e         biped_armor_type;
    };
    STATIC_ASSERT(sizeof(Biped_Object_c) == 0x10);

}

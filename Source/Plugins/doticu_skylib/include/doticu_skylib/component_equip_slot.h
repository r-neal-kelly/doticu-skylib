/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Equip_Slot_c : public Form_Data_c // BGSEquipType
    {
    public:
        virtual ~Equip_Slot_c(); // 0

        void*   equip_slot; // 08
    };
    STATIC_ASSERT(sizeof(Equip_Slot_c) == 0x10);

}

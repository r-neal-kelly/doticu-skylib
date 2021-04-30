/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Equip_Slot_c :    // BGSEquipType
        public Form_Data_c  // 00
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E11038, // 513861
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Equip_Slot_c(); // 0

    public:
        void*   equip_slot; // 08
    };
    STATIC_ASSERT(sizeof(Equip_Slot_c) == 0x10);

}

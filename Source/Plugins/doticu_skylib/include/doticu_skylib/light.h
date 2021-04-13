/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/animated_object.h"
#include "doticu_skylib/component_destructible.h"
#include "doticu_skylib/component_equip_slot.h"
#include "doticu_skylib/component_icon.h"
#include "doticu_skylib/component_message_icon.h"
#include "doticu_skylib/component_model_alternates.h"
#include "doticu_skylib/component_name.h"
#include "doticu_skylib/component_value.h"
#include "doticu_skylib/component_weight.h"

namespace doticu_skylib {

    class Light_t :                 // TESObjectLIGH
        public Animated_Object_t,   // 000
        public Name_c,              // 030
        public Model_Alternates_c,  // 040
        public Icon_c,              // 078
        public Message_Icon_c,      // 088
        public Weight_c,            // 0A0
        public Value_c,             // 0B0
        public Destructible_c,      // 0C0
        public Equip_Slot_c         // 0D0
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::LIGHT,
        };

        static constexpr const char* SCRIPT_NAME = "Light";

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E116A0, // 513874
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Light_t(); // 0

    public:
        Byte_t  data_0E0[0x50]; // 0E0

    public:
        void    Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Light_t) == 0x130);

}

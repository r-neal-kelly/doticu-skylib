/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_keywords.h"
#include "doticu_skylib/component_menu_display.h"
#include "doticu_skylib/component_name.h"

#include "doticu_skylib/form.h"
#include "doticu_skylib/enum_script_type.h"

namespace doticu_skylib {

    class Magic_Effect_t :      // EffectSetting
        public Form_t,          // 00
        public Name_c,          // 20
        public Menu_Display_c,  // 30
        public Keywords_c       // 40
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::MAGIC_EFFECT,
        };

    public:
        virtual ~Magic_Effect_t(); // 0

    public:
        Byte_t data[0x140]; // 58
    };
    STATIC_ASSERT(sizeof(Magic_Effect_t) == 0x198);

}

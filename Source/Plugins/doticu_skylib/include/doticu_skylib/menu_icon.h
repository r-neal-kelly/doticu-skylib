/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_icon.h"

#include "doticu_skylib/form.h"
#include "doticu_skylib/enum_script_type.h"

namespace doticu_skylib {

    class Menu_Icon_t :
        public Form_t,  // 00
        public Icon_c   // 20
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::MENU_ICON,
        };

    public:
        virtual ~Menu_Icon_t(); // 00
    };
    STATIC_ASSERT(sizeof(Menu_Icon_t) == 0x30);

}

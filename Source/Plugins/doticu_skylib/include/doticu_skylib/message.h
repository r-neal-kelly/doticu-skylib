/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/forward_list.h"
#include "doticu_skylib/string.h"

#include "doticu_skylib/enum_message_flags.h"

#include "doticu_skylib/component_description.h"
#include "doticu_skylib/component_name.h"

#include "doticu_skylib/form.h"
#include "doticu_skylib/enum_script_type.h"

namespace doticu_skylib {

    class Menu_Icon_t;
    class Quest_t;

    class Message_t :
        public Form_t,          // 00
        public Name_c,          // 20
        public Description_c    // 30
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::MESSAGE,
        };

        class Button_t
        {
        public:
            String_t    text; // 0
            void*       conditions; // 8
        };
        STATIC_ASSERT(sizeof(Button_t) == 0x10);

    public:
        virtual ~Message_t(); // 00

    public:
        Menu_Icon_t*        menu_icon;      // 40
        Quest_t*            owner;          // 48
        List_t<Button_t*>   menu_buttons;   // 50
        Message_Flags_e     message_flags;  // 60
        u32                 display_time;   // 64
    };
    STATIC_ASSERT(sizeof(Message_t) == 0x68);

}

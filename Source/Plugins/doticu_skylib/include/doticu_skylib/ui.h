/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/PapyrusUI.h"

#include "doticu_skylib/collections.h"
#include "doticu_skylib/dynamic_array.h"
#include "doticu_skylib/enum.h"
#include "doticu_skylib/event_dispatcher.h"
#include "doticu_skylib/event_open_close_menu.h"
#include "doticu_skylib/game_timer.h"
#include "doticu_skylib/interface.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/singleton.h"
#include "doticu_skylib/spin_lock.h"
#include "doticu_skylib/string.h"
#include "doticu_skylib/unique.h"

namespace doticu_skylib {

    class Menu_i;

    namespace Virtual {

        class Array_t;
        class Callback_i;

    }

    class GFx_Value_t :
        public GFxValue
    {
    public:
        template <typename Type>
        Type Value();
        template <typename Type>
        void Value(Type value);
    };

    class UI_t:                                             // UI, MenuManager
        public Singleton_t<UI_t>,                           // 000
        public Event_Dispatcher_t<Event_Open_Close_Menu_t>, // 008
        public Event_Dispatcher_t<void*>,                   // 060
        public Event_Dispatcher_t<void**>                   // 0B8
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                SELF = 0x01EBEB20, // 514178
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        static some<UI_t*> Self();

    public:
        template <typename Type>
        static Type     Value(String_t menu, String_t target);
        template <typename Type>
        static void     Value(String_t menu, String_t target, Type value);

        template <typename Type>
        static void     Run(String_t menu, String_t target, Type argument);
        template <typename Type>
        static void     Run(String_t menu, String_t target, Vector_t<Type> arguments);
        template <typename Type>
        static void     Run(String_t menu, String_t target, Virtual::Array_t* arguments);
        static void     Run(String_t menu, String_t target);

        static void     Create_Message_Box(String_t message, maybe<Virtual::Callback_i*> v_callback);
        static void     Create_Message_Box(String_t message, maybe<unique<Callback_i<>>> callback);
        static void     Create_Notification(String_t note, maybe<Virtual::Callback_i*> v_callback);
        static void     Create_Notification(String_t note, maybe<unique<Callback_i<>>> callback);

        static Bool_t   Is_Menu_Open(String_t menu);
        static void     Is_In_Menu_Mode(some<Virtual::Callback_i*> v_callback);
        static void     Is_In_Menu_Mode(some<unique<Callback_i<Bool_t>>> callback);

    public:
        Array_t<maybe<Menu_i*>>     menus;                      // 110
        Hash_Map_t<String_t, void*> unk_hash_map;               // 128
        mutable Spin_Lock_t         spin_lock;                  // 158
        u32                         pause_game_count;           // 160
        u32                         item_menu_count;            // 164
        u32                         disable_pause_menu_count;   // 168
        u32                         allow_saving_count;         // 16C
        u32                         dont_hide_cursor_count;     // 170
        u32                         custom_render_count;        // 174
        u32                         application_menu_count;     // 178
        Bool_t                      has_modal;                  // 17C
        u8                          pad_17D;                    // 17D
        u16                         pad_17E;                    // 17E
        Game_Timer_t                game_timer;                 // 180
        Bool_t                      is_menu_visible;            // 1C0
        Bool_t                      is_closing_all_menus;       // 1C1
        u16                         pad_1C2;                    // 1C2
        u32                         pad_1C4;                    // 1C4
    };
    STATIC_ASSERT(sizeof(UI_t) == 0x1C8);

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/interface.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/unique.h"
#include "doticu_skylib/virtual.h"

namespace doticu_skylib { namespace Virtual {

    class Callback_i;

    class Input_t
    {
    public:
        static constexpr const char* SCRIPT_NAME = "Input";

    public:
        static Int_t    Control_To_Key(String_t control, u32 device_type = 0xFF);
        static String_t Key_To_Control(Int_t key);

    public:
        static void Is_Key_Pressed(Int_t key, some<Virtual::Callback_i*> v_callback);                       // IsKeyPressed
        static void Is_Key_Pressed(Int_t key, some<unique<doticu_skylib::Callback_i<Bool_t>>> callback);

        static void Tap_Key(Int_t key, maybe<Virtual::Callback_i*> v_callback);                             // TapKey
        static void Tap_Key(Int_t key, maybe<unique<doticu_skylib::Callback_i<>>> callback);

        static void Tap_Inventory_Key(maybe<Virtual::Callback_i*> v_callback);
        static void Tap_Inventory_Key(maybe<unique<doticu_skylib::Callback_i<>>> callback);

    public:
        static void Close_Menus(maybe<unique<doticu_skylib::Callback_i<Bool_t>>> callback);
    };

}}

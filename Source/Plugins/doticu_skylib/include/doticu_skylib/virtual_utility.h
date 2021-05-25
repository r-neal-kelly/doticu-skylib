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

    class Utility_t
    {
    public:
        static constexpr const char* SCRIPT_NAME = "Utility";

    public:
        static void Wait_Out_Of_Menu(Float_t seconds, some<Virtual::Callback_i*> v_callback);                               // Wait
        static void Wait_Out_Of_Menu(Float_t seconds, some<unique<doticu_skylib::Callback_i<>>> callback);

        static void Wait_Even_In_Menu(Float_t seconds, some<Virtual::Callback_i*> v_callback);                              // WaitMenuMode
        static void Wait_Even_In_Menu(Float_t seconds, some<unique<doticu_skylib::Callback_i<>>> callback);

        static void Wait_For_Game_Time(Float_t hours, some<Virtual::Callback_i*> v_callback);                               // WaitGameTime
        static void Wait_For_Game_Time(Float_t hours, some<unique<doticu_skylib::Callback_i<>>> callback);

        static void Is_In_Menu_Mode(some<Virtual::Callback_i*> v_callback);                                                 // IsInMenuMode
        static void Is_In_Menu_Mode(some<unique<doticu_skylib::Callback_i<Bool_t>>> callback);

        static void To_Game_Time_String(Float_t days_passed, some<Virtual::Callback_i*> v_callback);                        // GameTimeToString
        static void To_Game_Time_String(Float_t days_passed, some<unique<doticu_skylib::Callback_i<String_t>>> callback);
    };

}}

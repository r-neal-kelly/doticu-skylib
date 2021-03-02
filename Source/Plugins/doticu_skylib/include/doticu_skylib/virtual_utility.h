/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/interface.h"
#include "doticu_skylib/virtual.h"

namespace doticu_skylib { namespace Virtual {

    class Callback_i;

    class Utility_t
    {
    public:
        static constexpr const char* SCRIPT_NAME = "Utility";

    public:
        static void Wait(Float_t seconds, Callback_i* vcallback = nullptr);
        static void Wait_Out_Of_Menu(Float_t seconds, Callback_i* vcallback = nullptr);
        static void Is_In_Menu_Mode(Callback_i* vcallback);
        static void Tap_Key(Int_t key, Callback_i* vcallback);
        static void Close_Menus(doticu_skylib::Callback_i<Bool_t>* ucallback = nullptr);
        //static void Open_Container(Reference_t* container, Callback_i* vcallback = nullptr);
    };

}}

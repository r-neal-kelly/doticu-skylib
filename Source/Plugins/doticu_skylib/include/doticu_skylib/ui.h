/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/PapyrusUI.h"

#include "doticu_skylib/collections.h"
#include "doticu_skylib/interface.h"
#include "doticu_skylib/string.h"
#include "doticu_skylib/unique.h"

namespace doticu_skylib {

    namespace Virtual {

        class Array_t;
        class Callback_i;

    }

    class GFx_Value_t : public GFxValue
    {
    public:
        template <typename Type>
        Type Value();
        template <typename Type>
        void Value(Type value);
    };

    class UI_t
    {
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

        static void     Notification(String_t note, Virtual::Callback_i* vcallback = nullptr);
        static void     Message_Box(String_t message, Virtual::Callback_i* vcallback = nullptr);

        static Bool_t   Is_Menu_Open(String_t menu);
        static void     Is_In_Menu_Mode(some<Virtual::Callback_i*> v_callback);
        static void     Is_In_Menu_Mode(some<unique<doticu_skylib::Callback_i<Bool_t>>> callback);
    };

}

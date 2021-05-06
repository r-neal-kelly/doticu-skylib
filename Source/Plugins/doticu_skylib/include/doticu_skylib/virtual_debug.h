/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/interface.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/string.h"
#include "doticu_skylib/unique.h"
#include "doticu_skylib/virtual.h"

namespace doticu_skylib {

    class Reference_t;

}

namespace doticu_skylib { namespace Virtual {

    class Callback_i;

    class Debug_t
    {
    public:
        static constexpr const char* SCRIPT_NAME = "Debug";

    public:
        static void Create_Message_Box(String_t message, maybe<Virtual::Callback_i*> v_callback);               // MessageBox
        static void Create_Message_Box(String_t message, maybe<unique<doticu_skylib::Callback_i<>>> callback);

        static void Create_Notification(String_t note, maybe<Virtual::Callback_i*> v_callback);                 // Notification
        static void Create_Notification(String_t note, maybe<unique<doticu_skylib::Callback_i<>>> callback);

        static void Send_Animation_Event(some<Reference_t*> reference,
                                         String_t event_name,
                                         maybe<Virtual::Callback_i*> v_callback);                               // SendAnimationEvent
        static void Send_Animation_Event(some<Reference_t*> reference,
                                         String_t event_name,
                                         maybe<unique<doticu_skylib::Callback_i<>>> callback);

        static void Trace(String_t note, Int_t severity, maybe<Virtual::Callback_i*> v_callback);               // Trace
        static void Trace(String_t note, Int_t severity, maybe<unique<doticu_skylib::Callback_i<>>> callback);
    };

}}

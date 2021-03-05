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
        static void Send_Animation_Event(some<Reference_t*> reference,
                                         String_t event_name,
                                         maybe<Virtual::Callback_i*> v_callback = nullptr);                 // SendAnimationEvent
        static void Send_Animation_Event(some<Reference_t*> reference,
                                         String_t event_name,
                                         maybe<unique<doticu_skylib::Callback_i<>>> callback = nullptr);    // SendAnimationEvent
    };

}}

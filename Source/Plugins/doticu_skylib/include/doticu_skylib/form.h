/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/GameForms.h"

#include "doticu_skylib/utils.h"
#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    namespace Virtual {

        class Callback_i;

    }

    class Form_Component_t { // BaseFormComponent
    public:
        virtual ~Form_Component_t(); // 00
    };
    STATIC_ASSERT(sizeof(Form_Component_t) == 0x8);

    class Form_t : public Form_Component_t { // TESForm
    public:
        enum {
            kTypeID = kFormType_None,
        };

    public:
        virtual ~Form_t(); // 00

        void Register_Mod_Event(String_t event_name, String_t callback_name, Virtual::Callback_i* vcallback = nullptr);
        void Unregister_Mod_Event(String_t event_name, Virtual::Callback_i* vcallback = nullptr);
        void Unregister_Mod_Events(Virtual::Callback_i* vcallback = nullptr);
    };

}

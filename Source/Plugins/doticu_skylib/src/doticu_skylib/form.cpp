/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/GameData.h"

#include "doticu_skylib/utils.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/virtual_arguments.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_machine.h"
#include "doticu_skylib/virtual_variable.h"

namespace doticu_skylib {

    Bool_t Actor_Base_Component_t::Is_Female()
    {
        return (actor_base_flags & static_cast<Actor_Base_Flags_t>(Actor_Base_Flags_e::IS_FEMALE)) != 0;
    }

    void Form_t::Register_Mod_Event(String_t event_name, String_t callback_name, Virtual::Callback_i* vcallback)
    {
        struct VArguments_t : public Virtual::Arguments_t {
            String_t event_name;
            String_t callback_name;
            VArguments_t(String_t event_name, String_t callback_name) :
                event_name(event_name), callback_name(callback_name)
            {
            }
            Bool_t operator()(Array_t* args)
            {
                args->Resize(2);
                args->At(0)->String(event_name);
                args->At(1)->String(callback_name);
                return true;
            }
        } arguments(event_name, callback_name);

        Virtual::Machine_t::Self()->Call_Method(
            this,
            "Form",
            "RegisterForModEvent",
            &arguments, &vcallback
        );
    }

    void Form_t::Unregister_Mod_Event(String_t event_name, Virtual::Callback_i* vcallback)
    {
        struct VArguments_t : public Virtual::Arguments_t {
            String_t event_name;
            VArguments_t(String_t event_name) :
                event_name(event_name)
            {
            }
            Bool_t operator()(Array_t* args)
            {
                args->Resize(1);
                args->At(0)->String(event_name);
                return true;
            }
        } arguments(event_name);

        Virtual::Machine_t::Self()->Call_Method(
            this,
            "Form",
            "UnregisterForModEvent",
            &arguments,
            &vcallback
        );
    }

    void Form_t::Unregister_Mod_Events(Virtual::Callback_i* vcallback)
    {
        Virtual::Machine_t::Self()->Call_Method(
            this,
            "Form",
            "UnregisterForAllModEvents",
            nullptr,
            &vcallback
        );
    }

}

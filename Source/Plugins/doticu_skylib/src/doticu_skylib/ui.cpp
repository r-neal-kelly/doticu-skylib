/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/ui.h"

#include "doticu_skylib/virtual_arguments.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_machine.h"
#include "doticu_skylib/virtual_variable.inl"

namespace doticu_skylib {

    void UI_t::Run(String_t menu, String_t target)
    {
        return Run<Bool_t>(menu, target, false);
    }

    void UI_t::Notification(String_t note, Virtual::Callback_i* vcallback)
    {
        struct VArguments : public Virtual::Arguments_t {
            String_t note;
            VArguments(String_t note) :
                note(note)
            {
            }
            Bool_t operator()(Buffer_t<Virtual::Variable_t>* arguments)
            {
                arguments->Resize(1);
                arguments->At(0)->String(note);
                return true;
            }
        } arguments(note);

        Virtual::Machine_t::Self()->Call_Global(
            "Debug",
            "Notification",
            &arguments,
            &vcallback
        );
    }

    void UI_t::Message_Box(String_t message, Virtual::Callback_i* vcallback)
    {
        struct VArguments : public Virtual::Arguments_t {
            String_t message;
            VArguments(String_t message) :
                message(message)
            {
            }
            Bool_t operator()(Buffer_t<Virtual::Variable_t>* arguments)
            {
                arguments->Resize(1);
                arguments->At(0)->String(message);
                return true;
            }
        } arguments(message);

        Virtual::Machine_t::Self()->Call_Global(
            "Debug",
            "MessageBox",
            &arguments,
            &vcallback
        );
    }

    Bool_t UI_t::Is_Menu_Open(String_t menu)
    {
        MenuManager* menu_manager = MenuManager::GetSingleton();
        if (menu_manager) {
            return menu_manager->IsMenuOpen(reinterpret_cast<BSFixedString*>(&menu));
        } else {
            return false;
        }
    }

}

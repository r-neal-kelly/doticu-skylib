/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/scrap_array.inl"
#include "doticu_skylib/ui.h"
#include "doticu_skylib/virtual_arguments.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_debug.h"
#include "doticu_skylib/virtual_machine.h"
#include "doticu_skylib/virtual_utility.h"
#include "doticu_skylib/virtual_variable.inl"

namespace doticu_skylib {

    void UI_t::Run(String_t menu, String_t target)
    {
        return Run<Bool_t>(menu, target, false);
    }

    void UI_t::Create_Message_Box(String_t message, maybe<Virtual::Callback_i*> v_callback)
    {
        Virtual::Debug_t::Create_Message_Box(message, v_callback);
    }

    void UI_t::Create_Message_Box(String_t message, maybe<unique<Callback_i<>>> callback)
    {
        Virtual::Debug_t::Create_Message_Box(message, std::move(callback));
    }

    void UI_t::Create_Notification(String_t note, maybe<Virtual::Callback_i*> v_callback)
    {
        Virtual::Debug_t::Create_Notification(note, v_callback);
    }

    void UI_t::Create_Notification(String_t note, maybe<unique<Callback_i<>>> callback)
    {
        Virtual::Debug_t::Create_Notification(note, std::move(callback));
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

    void UI_t::Is_In_Menu_Mode(some<Virtual::Callback_i*> v_callback)
    {
        Virtual::Utility_t::Is_In_Menu_Mode(v_callback);
    }

    void UI_t::Is_In_Menu_Mode(some<unique<Callback_i<Bool_t>>> callback)
    {
        Virtual::Utility_t::Is_In_Menu_Mode(std::move(callback));
    }

}

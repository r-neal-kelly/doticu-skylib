/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/GameData.h"

#include "doticu_skylib/utils.h"
#include "doticu_skylib/game.h"

namespace doticu_skylib {

    static DataHandler* Data_Handler()
    {
        static DataHandler* data_handler = DataHandler::GetSingleton();
        SKYLIB_ASSERT(data_handler != nullptr);
        return data_handler;
    }

    Mod_t* Game_t::Mod(const char* mod_name)
    {
        return const_cast<Mod_t*>(Data_Handler()->LookupModByName(mod_name));
    }

    Form_t* Game_t::Form(Form_ID_t form_id)
    {
        return LookupFormByID(form_id);
    }

    Form_t* Game_t::Form(Mod_t* mod, Lower_Form_ID_t lower_form_id)
    {
        if (mod) {
            return Form(static_cast<Form_ID_t>(mod->GetFormID(lower_form_id)));
        } else {
            return nullptr;
        }
    }

    Bool_t Game_t::Has_Mod(Mod_t* mod)
    {
        return mod && mod->IsActive();
    }

    Bool_t Game_t::Has_Form(Mod_t* mod, Form_ID_t form_id)
    {
        if (mod) {
            return mod->IsFormInMod(form_id);
        } else {
            return false;
        }
    }

}

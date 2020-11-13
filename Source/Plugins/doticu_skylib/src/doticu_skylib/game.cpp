/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/utils.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/worldspace.h"

namespace doticu_skylib {

    Game_Data_t* Game_t::Data()
    {
        static Game_Data_t* data = static_cast<Game_Data_t*>(DataHandler::GetSingleton());
        SKYLIB_ASSERT(data != nullptr);
        return data;
    }

    Mod_t* Game_t::Mod(const char* mod_name)
    {
        return const_cast<Mod_t*>(Data()->LookupModByName(mod_name));
    }

    Form_t* Game_t::Form(Form_ID_t form_id)
    {
        return reinterpret_cast<Form_t*>(LookupFormByID(form_id));
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

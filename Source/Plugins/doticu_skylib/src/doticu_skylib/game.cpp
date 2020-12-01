/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.h"
#include "doticu_skylib/mod.h"

namespace doticu_skylib {

    Game_t* Game_t::Self()
    {
        static Game_t* data = static_cast<Game_t*>(DataHandler::GetSingleton());
        SKYLIB_ASSERT(data != nullptr);
        return data;
    }

    Word_t Game_t::Base_Address()
    {
        static Word_t base_address = reinterpret_cast<Word_t>(GetModuleHandle(0));
        SKYLIB_ASSERT(base_address);
        return base_address;
    }

    Byte_t* Game_t::Base_Address_Pointer()
    {
        return reinterpret_cast<Byte_t*>(Base_Address());
    }

    Mod_t* Game_t::Mod(const char* mod_name)
    {
        return (Mod_t*)(Self()->LookupModByName(mod_name));
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

    Word_t Game_t::V_Table_Offset(void* instance)
    {
        return *reinterpret_cast<Word_t*>(instance) - Game_t::Base_Address();
    }

    void Game_t::Write_V_Table(void* instance, Word_t v_table_offset)
    {
        static_cast<Word_t*>(instance)[0] = Game_t::Base_Address() + v_table_offset;
    }

}

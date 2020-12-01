/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/GameData.h"

#include "doticu_skylib/intrinsic.h"

#include "doticu_skylib/form_id.h"

namespace doticu_skylib {

    class Form_t;
    class Mod_t;

    class Game_t : public DataHandler
    {
    public:
        static Game_t*  Self();

        static Word_t   Base_Address();
        static Byte_t*  Base_Address_Pointer();

        static Mod_t*   Mod(const char* mod_name);
        static Form_t*  Form(Form_ID_t form_id);
        static Form_t*  Form(Mod_t* mod, Lower_Form_ID_t lower_form_id);

        static Bool_t   Has_Mod(Mod_t* mod);
        static Bool_t   Has_Form(Mod_t* mod, Form_ID_t form_id);

        static Word_t   V_Table_Offset(void* instance);
        static void     Write_V_Table(void* instance, Word_t v_table_offset);
    };

}

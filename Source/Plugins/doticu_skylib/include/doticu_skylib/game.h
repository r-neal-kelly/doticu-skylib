/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Game_t {
    public:
        static Mod_t* Mod(const char* mod_name);
        static Form_t* Form(Form_ID_t form_id);
        static Form_t* Form(Mod_t* mod, Lower_Form_ID_t lower_form_id);

        static Bool_t Has_Mod(Mod_t* mod);
        static Bool_t Has_Form(Mod_t* mod, Form_ID_t form_id);
    };

}

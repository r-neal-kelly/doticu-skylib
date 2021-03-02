/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/component_form_data.h"
#include "doticu_skylib/game.inl"

namespace doticu_skylib {

    Bool_t  Form_Data_c::Component_Is_Actor_Base()  { return Component_As_Actor_Base() != none<Actor_Base_t*>(); }
    Bool_t  Form_Data_c::Component_Is_Form()        { return Component_As_Form() != none<Form_t*>(); }

    maybe<Actor_Base_t*>    Form_Data_c::Component_As_Actor_Base()  { return Game_t::Runtime_Cast<Form_Data_c, Actor_Base_t>(this); }
    maybe<Form_t*>          Form_Data_c::Component_As_Form()        { return Game_t::Runtime_Cast<Form_Data_c, Form_t>(this); }

    Bool_t Form_Data_c::Component_Flag_Form_Change(u32 flag)
    {
        maybe<Form_t*> form = Component_As_Form();
        if (form) {
            return form->Flag_Form_Change(flag);
        } else {
            return false;
        }
    }

    void Form_Data_c::Component_Unflag_Form_Change(u32 flag)
    {
        maybe<Form_t*> form = Component_As_Form();
        if (form) {
            form->Unflag_Form_Change(flag);
        }
    }

}

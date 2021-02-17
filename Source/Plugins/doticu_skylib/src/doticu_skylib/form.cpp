/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/cstring.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/game.inl"
#include "doticu_skylib/leveled_item.h"
#include "doticu_skylib/mod.h"
#include "doticu_skylib/virtual_arguments.h"
#include "doticu_skylib/virtual_machine.h"
#include "doticu_skylib/virtual_variable.inl"

namespace doticu_skylib {

    Int_t Form_t::Compare_Names(const char* name_a, const char* name_b)
    {
        if (!name_a || !name_a[0]) {
            return Comparator_e::IS_UNORDERED;
        } else if (!name_b || !name_b[0]) {
            return Comparator_e::IS_ORDERED;
        } else if (name_a[0] == '0' && name_a[1] == 'x' && name_b[0] != '0' && name_b[1] != 'x') {
            return Comparator_e::IS_UNORDERED;
        } else if (name_a[0] != '0' && name_a[1] != 'x' && name_b[0] == '0' && name_b[1] == 'x') {
            return Comparator_e::IS_ORDERED;
        } else {
            return _stricmp(name_a, name_b);
        }
    }

    Bool_t Form_t::Is_Valid()   { return static_cast<Bool_t>(form_id); }
    Bool_t Form_t::Is_Static()  { return form_id.Is_Static(); }
    Bool_t Form_t::Is_Dynamic() { return form_id.Is_Dynamic(); }
    Bool_t Form_t::Is_Heavy()   { return form_id.Is_Heavy(); }
    Bool_t Form_t::Is_Light()   { return form_id.Is_Light(); }

    maybe<Heavy_Mod_Index_t>    Form_t::Heavy_Mod_Index()   { return form_id.Heavy_Mod_Index(); }
    maybe<Light_Mod_Index_t>    Form_t::Light_Mod_Index()   { return form_id.Light_Mod_Index(); }
    maybe<Heavy_Form_Index_t>   Form_t::Heavy_Form_Index()  { return form_id.Heavy_Form_Index(); }
    maybe<Light_Form_Index_t>   Form_t::Light_Form_Index()  { return form_id.Light_Form_Index(); }

    maybe<Mod_t*> Form_t::Indexed_Mod()
    {
        return form_id.Mod();
    }

    Bool_t Form_t::Has_Indexed_Mod(maybe<const char*> mod_name)
    {
        if (mod_name && mod_name[0]) {
            if (Is_Static()) {
                maybe<Mod_t*> mod = Indexed_Mod();
                if (mod) {
                    return CString_t::Is_Same(mod_name(), mod->Name(), true);
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            if (Is_Dynamic()) {
                return true;
            } else {
                return false;
            }
        }
    }

    Bool_t Form_t::Has_Indexed_Mod(maybe<Mod_t*> mod)
    {
        if (mod) {
            return Indexed_Mod() == mod();
        } else {
            return Is_Dynamic();
        }
    }

    Vector_t<Mod_t*> Form_t::Mods()
    {
        Vector_t<Mod_t*> mods;
        if (form_mods) {
            for (Index_t idx = 0, end = form_mods->count; idx < end; idx += 1) {
                Mod_t* mod = form_mods->entries[idx];
                if (mod) {
                    mods.push_back(mod);
                }
            }
        }
        return mods;
    }

    String_t Form_t::Form_ID_String()
    {
        return static_cast<String_t>(this->form_id);
    }

    Vector_t<String_t> Form_t::Mod_Names()
    {
        Vector_t<String_t> results;
        Mod_Names(results);
        return results;
    }

    void Form_t::Mod_Names(Vector_t<String_t>& results)
    {
        if (form_mods) {
            results.reserve(form_mods->count);
            for (Index_t idx = 0, end = form_mods->count; idx < end; idx += 1) {
                Mod_t* mod = form_mods->entries[idx];
                if (mod) {
                    results.push_back(mod->Name());
                }
            }
        }
    }

    Bool_t  Form_t::Is_Actor()          { return As_Actor() != none<Actor_t*>(); }
    Bool_t  Form_t::Is_Leveled_Item()   { return As_Leveled_Item() != none<Leveled_Item_t*>(); }

    maybe<Actor_t*>         Form_t::As_Actor()          { return Game_t::Runtime_Cast<Form_t, Actor_t>(this); }
    maybe<Leveled_Item_t*>  Form_t::As_Leveled_Item()   { return Game_t::Runtime_Cast<Form_t, Leveled_Item_t>(this); }

    void Form_t::Register_Mod_Event(String_t event_name, String_t callback_name, Virtual::Callback_i* vcallback)
    {
        struct VArguments_t : public Virtual::Arguments_t {
            String_t event_name;
            String_t callback_name;
            VArguments_t(String_t event_name, String_t callback_name) :
                event_name(event_name), callback_name(callback_name)
            {
            }
            Bool_t operator()(Buffer_t<Virtual::Variable_t>* args)
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
            Bool_t operator()(Buffer_t<Virtual::Variable_t>* args)
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

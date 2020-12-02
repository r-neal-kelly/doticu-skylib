/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cstring.h"

#include "doticu_skylib/form.h"
#include "doticu_skylib/mod.h"

#include "doticu_skylib/virtual_arguments.h"
#include "doticu_skylib/virtual_machine.h"
#include "doticu_skylib/virtual_variable.h"

namespace doticu_skylib {

    Bool_t Form_t::Is_Static(Form_ID_t form_id)
    {
        return !Is_Dynamic(form_id);
    }

    Bool_t Form_t::Is_Dynamic(Form_ID_t form_id)
    {
        return (form_id & 0xFF000000) == 0xFF000000;
    }

    Bool_t Form_t::Is_Heavy(Form_ID_t form_id)
    {
        return !Is_Light(form_id);
    }

    Bool_t Form_t::Is_Light(Form_ID_t form_id)
    {
        return (form_id & 0xFF000000) == 0xFE000000;
    }

    Form_ID_t Form_t::Reindex(Form_ID_t form_id, Mod_t* mod)
    {
        if (mod) {
            maybe<Index_t> mod_idx;
            if (Is_Light(form_id)) {
                mod_idx = mod->Light_Index();
            } else {
                mod_idx = mod->Heavy_Index();
            }
            if (mod_idx) {
                return Reindex(form_id, mod_idx());
            } else {
                return 0;
            }
        } else {
            if (Is_Heavy(form_id)) {
                return Reindex(form_id, 0xFF);
            } else {
                return 0;
            }
        }
    }

    Form_ID_t Form_t::Reindex(Form_ID_t form_id, u32 idx)
    {
        if (Is_Light(form_id)) {
            if (idx < 0x1000) {
                return 0xFE000000 | (idx << 12) | (form_id & 0x00000FFF);
            } else {
                return 0;
            }
        } else {
            if (idx < 0x100) {
                return (idx << 24) | (form_id & 0x00FFFFFF);
            } else {
                return 0;
            }
        }
    }

    Form_ID_t Form_t::Form_ID(Lower_Form_ID_t lower_form_id, some<Mod_t*> mod)
    {
        SKYLIB_ASSERT_SOME(mod);

        if (mod->Is_Light()) {
            maybe<Index_t> mod_idx = mod->Light_Index();
            if (mod_idx && mod_idx() < 0x1000) {
                return 0xFE000000 | (mod_idx() << 12) | (lower_form_id & 0x00000FFF);
            } else {
                return 0;
            }
        } else {
            maybe<Index_t> mod_idx = mod->Heavy_Index();
            if (mod_idx && mod_idx() < 0x100) {
                return (mod_idx() << 24) | (lower_form_id & 0x00FFFFFF);
            } else {
                return 0;
            }
        }
    }

    Bool_t Form_t::Is_Valid()
    {
        return form_id != 0;
    }

    Bool_t Form_t::Is_Static()
    {
        return !Is_Dynamic();
    }

    Bool_t Form_t::Is_Dynamic()
    {
        return (form_id & 0xFF000000) == 0xFF000000;
    }

    Bool_t Form_t::Is_Heavy()
    {
        return !Is_Light();
    }

    Bool_t Form_t::Is_Light()
    {
        return (form_id & 0xFF000000) == 0xFE000000;
    }

    Mod_t* Form_t::Indexed_Mod()
    {
        Array_t<Mod_t*>& heavy_mods = Mod_t::Active_Heavy_Mods_2();
        Array_t<Mod_t*>& light_mods = Mod_t::Active_Light_Mods_2();
        
        if (Is_Static()) {
            if (Is_Light()) {
                u32 index = (form_id & 0x00FFF000) >> 12;
                SKYLIB_ASSERT(index < light_mods.count);
                return light_mods.entries[index];
            } else {
                u32 index = (form_id & 0xFF000000) >> 24;
                SKYLIB_ASSERT(index < heavy_mods.count);
                return heavy_mods.entries[index];
            }
        } else {
            return nullptr;
        }
    }

    Bool_t Form_t::Has_Indexed_Mod(const char* mod_name)
    {
        Array_t<Mod_t*>& heavy_mods = Mod_t::Active_Heavy_Mods_2();
        Array_t<Mod_t*>& light_mods = Mod_t::Active_Light_Mods_2();

        if (mod_name && mod_name[0]) {
            if (Is_Static()) {
                Mod_t* mod = Indexed_Mod();
                if (mod) {
                    return CString_t::Is_Same(mod_name, mod->Name(), true);
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
        static const char hex_values[16] =
        {
            '0', '1', '2', '3', '4', '5', '6', '7',
            '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
        };

        char form_id_string[11] =
        {
            '0', 'x',
            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            '\0'
        };

        form_id_string[2] = hex_values[(form_id & 0xF0000000) >> 28];
        form_id_string[3] = hex_values[(form_id & 0x0F000000) >> 24];
        form_id_string[4] = hex_values[(form_id & 0x00F00000) >> 20];
        form_id_string[5] = hex_values[(form_id & 0x000F0000) >> 16];
        form_id_string[6] = hex_values[(form_id & 0x0000F000) >> 12];
        form_id_string[7] = hex_values[(form_id & 0x00000F00) >>  8];
        form_id_string[8] = hex_values[(form_id & 0x000000F0) >>  4];
        form_id_string[9] = hex_values[(form_id & 0x0000000F) >>  0];

        return form_id_string;
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

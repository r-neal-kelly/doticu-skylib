/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/GameData.h"

#include "doticu_skylib/utils.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/mod.h"
#include "doticu_skylib/virtual_arguments.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_machine.h"
#include "doticu_skylib/virtual_variable.h"

namespace doticu_skylib {

    Bool_t Actor_Base_Component_t::Is_Male()
    {
        return !Is_Female();
    }

    Bool_t Actor_Base_Component_t::Is_Female()
    {
        return (actor_base_flags & Actor_Base_Flags_e::IS_FEMALE) != 0;
    }

    Bool_t Actor_Base_Component_t::Is_Unique()
    {
        return (actor_base_flags & Actor_Base_Flags_e::IS_UNIQUE) != 0;
    }

    Bool_t Actor_Base_Component_t::Is_Generic()
    {
        return !Is_Unique();
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
        static tArray<Mod_t*>& heavy_mods = Mod_t::Active_Heavy_Mods_2();
        static tArray<Mod_t*>& light_mods = Mod_t::Active_Light_Mods_2();
        
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

    Vector_t<Mod_t*> Form_t::Mods()
    {
        Vector_t<Mod_t*> mods;
        if (form_files) {
            for (Index_t idx = 0, end = form_files->count; idx < end; idx += 1) {
                Mod_t* mod = form_files->entries[idx];
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
        if (form_files) {
            results.reserve(form_files->count);
            for (Index_t idx = 0, end = form_files->count; idx < end; idx += 1) {
                Mod_t* mod = form_files->entries[idx];
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
            Bool_t operator()(Array_t* args)
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
            Bool_t operator()(Array_t* args)
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

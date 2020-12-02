/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cstring.h"

#include "doticu_skylib/form.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/mod.h"

namespace doticu_skylib {

    size_t Mod_t::Active_Mod_Count()
    {
        return Active_Heavy_Mod_Count() + Active_Light_Mod_Count();
    }

    size_t Mod_t::Active_Heavy_Mod_Count()
    {
        return Game_t::Self()->heavy_mods.count;
    }

    size_t Mod_t::Active_Light_Mod_Count()
    {
        return Game_t::Self()->light_mods.count;
    }

    Vector_t<some<Mod_t*>> Mod_t::Active_Mods()
    {
        Array_t<Mod_t*>& heavy_mods = Game_t::Self()->heavy_mods;
        Array_t<Mod_t*>& light_mods = Game_t::Self()->light_mods;

        Vector_t<some<Mod_t*>> results;
        results.reserve(heavy_mods.count + light_mods.count);

        for (Index_t idx = 0, end = heavy_mods.count; idx < end; idx += 1) {
            Mod_t* mod = heavy_mods.entries[idx];
            if (mod) {
                results.push_back(mod);
            }
        }

        for (Index_t idx = 0, end = light_mods.count; idx < end; idx += 1) {
            Mod_t* mod = light_mods.entries[idx];
            if (mod) {
                results.push_back(mod);
            }
        }

        return results;
    }

    Vector_t<some<Mod_t*>> Mod_t::Active_Heavy_Mods()
    {
        Array_t<Mod_t*>& heavy_mods = Game_t::Self()->heavy_mods;

        Vector_t<some<Mod_t*>> results;
        results.reserve(heavy_mods.count);

        for (Index_t idx = 0, end = heavy_mods.count; idx < end; idx += 1) {
            Mod_t* mod = heavy_mods.entries[idx];
            if (mod) {
                results.push_back(mod);
            }
        }

        return results;
    }

    Vector_t<some<Mod_t*>> Mod_t::Active_Light_Mods()
    {
        Array_t<Mod_t*>& light_mods = Game_t::Self()->light_mods;

        Vector_t<some<Mod_t*>> results;
        results.reserve(light_mods.count);

        for (Index_t idx = 0, end = light_mods.count; idx < end; idx += 1) {
            Mod_t* mod = light_mods.entries[idx];
            if (mod) {
                results.push_back(mod);
            }
        }

        return results;
    }

    Array_t<Mod_t*>& Mod_t::Active_Heavy_Mods_2()
    {
        return Game_t::Self()->heavy_mods;
    }

    Array_t<Mod_t*>& Mod_t::Active_Light_Mods_2()
    {
        return Game_t::Self()->light_mods;
    }

    static void Log_Mods(const char* title, Vector_t<some<Mod_t*>> mods)
    {
        #define TAB "    "

        _MESSAGE("%s {", title);
        for (size_t idx = 0, end = mods.size(); idx < end; idx += 1) {
            Mod_t* mod = mods[idx];
            _MESSAGE(TAB "index: %6zu, mod: %s", idx, mod->Name());
        }
        _MESSAGE("}");

        #undef TAB
    }

    void Mod_t::Log_Active_Mods()
    {
        doticu_skylib::Log_Mods("Log_Active_Mods", Active_Mods());
    }

    void Mod_t::Log_Active_Heavy_Mods()
    {
        doticu_skylib::Log_Mods("Log_Active_Heavy_Mods", Active_Heavy_Mods());
    }

    void Mod_t::Log_Active_Light_Mods()
    {
        doticu_skylib::Log_Mods("Log_Active_Light_Mods", Active_Light_Mods());
    }

    maybe<Mod_t*> Mod_t::Active_Mod(some<const char*> mod_name)
    {
        SKYLIB_ASSERT_SOME(mod_name);

        Array_t<Mod_t*>& heavy_mods = Game_t::Self()->heavy_mods;
        Array_t<Mod_t*>& light_mods = Game_t::Self()->light_mods;

        for (Index_t idx = 0, end = heavy_mods.count; idx < end; idx += 1) {
            Mod_t* mod = heavy_mods.entries[idx];
            if (mod) {
                if (CString_t::Is_Same(mod_name, mod->Name(), true)) {
                    return mod;
                }
            }
        }

        for (Index_t idx = 0, end = light_mods.count; idx < end; idx += 1) {
            Mod_t* mod = light_mods.entries[idx];
            if (mod) {
                if (CString_t::Is_Same(mod_name, mod->Name(), true)) {
                    return mod;
                }
            }
        }

        return nullptr;
    }

    some<Mod_t*> Mod_t::Skyrim()
    {
        static maybe<Mod_t*> skyrim = Active_Mod("Skyrim.esm");
        SKYLIB_ASSERT(skyrim);
        return skyrim;
    }

    Bool_t Mod_t::Is_Active()
    {
        return (mod_flags & Mod_Flags_e::IS_ACTIVE) != 0;
    }

    Bool_t Mod_t::Is_Heavy()
    {
        return !Is_Light();
    }

    Bool_t Mod_t::Is_Light()
    {
        return (mod_flags & Mod_Flags_e::IS_LIGHT) != 0;
    }

    const char* Mod_t::Name()
    {
        return static_cast<const char*>(file_name);
    }

    maybe<Index_t> Mod_t::Heavy_Index()
    {
        if (Is_Heavy()) {
            if (heavy_index == 0xFF) {
                return none<Index_t>();
            } else {
                return maybe<Index_t>(static_cast<Index_t>(heavy_index));
            }
        } else {
            return none<Index_t>();
        }
    }

    maybe<Index_t> Mod_t::Light_Index()
    {
        if (Is_Light()) {
            if (light_index == 0xFFFF) {
                return none<Index_t>();
            } else {
                return maybe<Index_t>(static_cast<Index_t>(light_index));
            }
        } else {
            return none<Index_t>();
        }
    }

}

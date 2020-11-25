/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/mod.h"
#include "doticu_skylib/game.h"

namespace doticu_skylib {

    size_t Mod_t::Mod_Count()
    {
        tList<Mod_t>& mods = reinterpret_cast<tList<Mod_t>&>(Game_t::Data()->modList.modInfoList);
        return mods.Count();
    }

    size_t Mod_t::Active_Mod_Count()
    {
        return Active_Heavy_Mod_Count() + Active_Light_Mod_Count();
    }

    size_t Mod_t::Active_Heavy_Mod_Count()
    {
        tArray<Mod_t*>& heavy_mods = reinterpret_cast<tArray<Mod_t*>&>(Game_t::Data()->modList.loadedMods);
        return heavy_mods.count;
    }

    size_t Mod_t::Active_Light_Mod_Count()
    {
        tArray<Mod_t*>& light_mods = reinterpret_cast<tArray<Mod_t*>&>(Game_t::Data()->modList.loadedCCMods);
        return light_mods.count;
    }

    Vector_t<Mod_t*> Mod_t::Mods()
    {
        tList<Mod_t>& mods = reinterpret_cast<tList<Mod_t>&>(Game_t::Data()->modList.modInfoList);

        Vector_t<Mod_t*> results;
        results.reserve(8);

        for (tList<Mod_t>::Iterator it = mods.Begin(); !it.End(); ++it) {
            Mod_t* mod = it.Get();
            if (mod) {
                results.push_back(mod);
            }
        }

        return results;
    }

    Vector_t<Mod_t*> Mod_t::Active_Mods()
    {
        tArray<Mod_t*>& heavy_mods = reinterpret_cast<tArray<Mod_t*>&>(Game_t::Data()->modList.loadedMods);
        tArray<Mod_t*>& light_mods = reinterpret_cast<tArray<Mod_t*>&>(Game_t::Data()->modList.loadedCCMods);

        Vector_t<Mod_t*> results;
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

    Vector_t<Mod_t*> Mod_t::Active_Heavy_Mods()
    {
        tArray<Mod_t*>& heavy_mods = reinterpret_cast<tArray<Mod_t*>&>(Game_t::Data()->modList.loadedMods);

        Vector_t<Mod_t*> results;
        results.reserve(heavy_mods.count);

        for (Index_t idx = 0, end = heavy_mods.count; idx < end; idx += 1) {
            Mod_t* mod = heavy_mods.entries[idx];
            if (mod) {
                results.push_back(mod);
            }
        }

        return results;
    }

    Vector_t<Mod_t*> Mod_t::Active_Light_Mods()
    {
        tArray<Mod_t*>& light_mods = reinterpret_cast<tArray<Mod_t*>&>(Game_t::Data()->modList.loadedCCMods);

        Vector_t<Mod_t*> results;
        results.reserve(light_mods.count);

        for (Index_t idx = 0, end = light_mods.count; idx < end; idx += 1) {
            Mod_t* mod = light_mods.entries[idx];
            if (mod) {
                results.push_back(mod);
            }
        }

        return results;
    }

    tArray<Mod_t*>& Mod_t::Active_Heavy_Mods_2()
    {
        return reinterpret_cast<tArray<Mod_t*>&>(Game_t::Data()->modList.loadedMods);
    }

    tArray<Mod_t*>& Mod_t::Active_Light_Mods_2()
    {
        return reinterpret_cast<tArray<Mod_t*>&>(Game_t::Data()->modList.loadedCCMods);
    }

    static void Log_Mods(const char* title, Vector_t<Mod_t*> mods)
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

    void Mod_t::Log_Mods()
    {
        doticu_skylib::Log_Mods("Log_Mods", Mods());
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

    const char* Mod_t::Name()
    {
        return static_cast<const char*>(name);
    }

}

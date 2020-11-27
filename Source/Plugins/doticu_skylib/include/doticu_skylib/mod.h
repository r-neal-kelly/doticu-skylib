/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/collections.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/xlist.h"

namespace doticu_skylib {

    class Mod_t : public ModInfo // until we fill it out ourselves.
    {
    public:
        static size_t           Mod_Count();
        static size_t           Active_Mod_Count();
        static size_t           Active_Heavy_Mod_Count();
        static size_t           Active_Light_Mod_Count();
        static Vector_t<Mod_t*> Mods();
        static Vector_t<Mod_t*> Active_Mods();
        static Vector_t<Mod_t*> Active_Heavy_Mods();
        static Vector_t<Mod_t*> Active_Light_Mods();
        static tArray<Mod_t*>&  Active_Heavy_Mods_2();
        static tArray<Mod_t*>&  Active_Light_Mods_2();
        static void             Log_Mods();
        static void             Log_Active_Mods();
        static void             Log_Active_Heavy_Mods();
        static void             Log_Active_Light_Mods();

        static Mod_t* From(const char* mod_name);

    public:
        const char* Name();
        Index_t Heavy_Index();
        Index_t Light_Index();
    };
    //STATIC_ASSERT(sizeof(Mod_t) == 0x0);

}

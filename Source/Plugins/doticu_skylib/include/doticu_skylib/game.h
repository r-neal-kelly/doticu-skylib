/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/enum.h"
#include "doticu_skylib/forward_list.h"
#include "doticu_skylib/maybe.h"

#include "doticu_skylib/form_id.h"
#include "doticu_skylib/form_type.h"

namespace doticu_skylib {

    class Actor_Base_t;
    class Addon_Node_t;
    class Cell_t;
    class Form_t;
    class Leveled_Actor_Base_t;
    class Mod_t;
    class Race_t;
    class Region_t;
    class Worldspace_t;

    class Game_t
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : Word_t
            {
                SELF        = 0x01EBE428,
                GET_FORM    = 0x00194230,
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Game_t*>    Self();

        static Word_t           Base_Address();
        static some<Byte_t*>    Base_Address_Pointer();

        static maybe<Form_t*>   Form(Form_ID_t form_id);
        static maybe<Form_t*>   Form(Mod_t* mod, Lower_Form_ID_t lower_form_id);

        static Word_t           V_Table_Offset(void* instance);
        static void             Write_V_Table(void* instance, Word_t v_table_offset);
        static void             Log_u64s(void* data, size_t count, std::string indent = "");

    public:
        u64                             unk_000;                                // 000
        void*                           unk_008;                                // 008
        Array_t<Form_t*>                form_caches[Form_Type_e::MAX_TYPES];    // 010
        List_t<Region_t*>*              region_list;                            // D00
        Short_Array_t<Cell_t*>          interior_cells;                         // D08
        Short_Array_t<Addon_Node_t*>    addon_nodes;                            // D20
        Double_List_t<Form_t*>          bad_forms;                              // D38
        Form_ID_t                       next_id;                                // D50
        u32                             pad_D54;                                // D54
        Mod_t*                          active_mod;                             // D58
        List_t<Mod_t*>                  mods;                                   // D60
        Array_t<Mod_t*>                 heavy_mods;                             // D70
        Array_t<Mod_t*>                 light_mods;                             // D88
        Bool_t                          boolean_flags[16];                      // DA0
        void*                           region_manager;                         // DB0
        u64                             unk_DB8;                                // DB8

    public:
        Array_t<Actor_Base_t*>&         Actor_Bases();
        Array_t<Leveled_Actor_Base_t*>& Leveled_Actor_Bases();
        Array_t<Race_t*>&               Races();
        Array_t<Worldspace_t*>&         Worldspaces();
    };
    STATIC_ASSERT(sizeof(Game_t) == 0xDC0);

}

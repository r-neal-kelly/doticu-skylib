/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/enum.h"
#include "doticu_skylib/forward_list.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/version.h"

#include "doticu_skylib/form_id.h"
#include "doticu_skylib/form_type.h"

namespace doticu_skylib {

    class Actor_Base_t;
    class Addon_Node_t;
    class Cell_t;
    class Faction_t;
    class Form_t;
    class Leveled_Actor_Base_t;
    class Mod_t;
    class Quest_t;
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
                SELF            = 0x01EBE428,
                GET_FORM        = 0x00194230,
                RUNTIME_CAST    = 0x0134BDB0,
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Game_t*>            Self();

        static Word_t                   Base_Address();
        static some<Byte_t*>            Base_Address_Pointer();
        static size_t                   Base_Address_Size();

        static const Version_t<u16>&    Version();

        template <typename T>
        static some<T*>                 Allocate();
        template <typename T>
        static some<T*>                 Callocate();
        template <typename T>
        static void                     Deallocate(some<T*> data);

        static maybe<Form_t*>           Form(Raw_Form_ID_t raw_form_id);
        static maybe<Form_t*>           Form(some<Mod_t*> mod, Raw_Form_Index_t raw_form_index);

        template <typename From_t, typename To_t>
        static maybe<To_t*>             Runtime_Cast(some<From_t*> from);

        static Word_t                   V_Table_Offset(const void* instance);
        static void                     Write_V_Table(void* instance, Word_t v_table_offset);

        template <typename Data_t, typename Value_t>
        static Bool_t                   Data_Has_Value(Data_t* data, Value_t value);
        template <typename Data_t, typename Value_t>
        static Word_t                   Offset_Of_Value(Data_t* data, Value_t value);

        template <typename Value_t>
        static void                     Log_Value_Offsets(Value_t value, std::string indent = "");

        static void                     Log_u64s(void* data, size_t count, std::string indent = "");

    public:
        u64                             unk_000;                            // 000
        void*                           unk_008;                            // 008
        Array_t<Form_t*>                form_caches[Form_Type_e::_END_];    // 010
        List_t<Region_t*>*              region_list;                        // D00
        Short_Array_t<Cell_t*>          interior_cells;                     // D08
        Short_Array_t<Addon_Node_t*>    addon_nodes;                        // D20
        Double_List_t<Form_t*>          bad_forms;                          // D38
        Form_ID_t                       next_id;                            // D50
        u32                             pad_D54;                            // D54
        Mod_t*                          active_mod;                         // D58
        List_t<Mod_t*>                  mods;                               // D60
        Array_t<Mod_t*>                 heavy_mods;                         // D70
        Array_t<Mod_t*>                 light_mods;                         // D88
        Bool_t                          boolean_flags[16];                  // DA0
        void*                           region_manager;                     // DB0
        u64                             unk_DB8;                            // DB8

    public:
        Array_t<Actor_Base_t*>&         Actor_Bases();
        Array_t<Faction_t*>&            Factions();
        Array_t<Leveled_Actor_Base_t*>& Leveled_Actor_Bases();
        Array_t<Quest_t*>&              Quests();
        Array_t<Race_t*>&               Races();
        Array_t<Worldspace_t*>&         Worldspaces();
    };
    STATIC_ASSERT(sizeof(Game_t) == 0xDC0);

}

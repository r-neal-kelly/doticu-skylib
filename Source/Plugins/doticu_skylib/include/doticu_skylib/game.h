/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <mutex>

#include "doticu_skylib/collections.h"
#include "doticu_skylib/dynamic_array.h"
#include "doticu_skylib/enum.h"
#include "doticu_skylib/enum_form_type.h"
#include "doticu_skylib/form_id.h"
#include "doticu_skylib/forward_list.h"
#include "doticu_skylib/interface.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/read_write_lock.h"
#include "doticu_skylib/version.h"

namespace doticu_skylib {

    class Actor_Base_t;
    class Addon_Node_t;
    class Cell_t;
    class Faction_t;
    class Form_t;
    class Leveled_Actor_Base_t;
    class Location_t;
    class Mod_t;
    class Quest_t;
    class Race_t;
    class Region_t;
    class Worldspace_t;

    class Game_t    // TESDataHandler
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                SELF                        = 0x01EBE428, // 514141

                GET_FORM                    = 0x00194230, // 14461
                FORM_IDS_TO_FORMS           = 0x01EC3CB8, // 514351
                FORM_IDS_TO_FORMS_LOCK      = 0x01EC4150, // 514360
                EDITOR_IDS_TO_FORMS         = 0x01EC3CC0, // 514352
                EDITOR_IDS_TO_FORMS_LOCK    = 0x01EC4158, // 514361

                RUNTIME_CAST                = 0x0134BDB0, // 102238
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        static std::mutex lock;

    public:
        static some<Game_t*>            Self();

        static Word_t                   Base_Address();
        static some<Byte_t*>            Base_Address_Pointer();
        static size_t                   Base_Address_Size();

        static const Version_t<u16>&    Version();

        static const std::wstring       Save_Path();
        static const std::wstring       Save_File_Path(some<const wchar_t*> file_name, some<const wchar_t*> extension);
        static const std::wstring       Save_File_Path(some<const char*> file_name, some<const char*> extension);

    public:
        template <typename T>
        static some<T*>                 Allocate(size_t count = 1);
        template <typename T>
        static some<T*>                 Callocate(size_t count = 1);
        template <typename T>
        static some<T*>                 Reallocate(some<T*> data, size_t new_count);
        template <typename T>
        static void                     Deallocate(some<T*> data);

        template <typename From_t, typename To_t>
        static maybe<To_t*>             Runtime_Cast(some<const From_t*> from);

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
        static Hash_Map_t<Form_ID_t, maybe<Form_t*>>&   Form_IDs_To_Forms();
        static Read_Write_Lock_t&                       Form_IDs_To_Forms_Lock();
        static Hash_Map_t<String_t, maybe<Form_t*>>&    Editor_IDs_To_Forms();
        static Read_Write_Lock_t&                       Editor_IDs_To_Forms_Lock();

        static Bool_t                                   Has_Form(some<Form_ID_t> form_id, Read_Locker_t& locker);
        static Bool_t                                   Has_Form(some<Form_t*> form, Read_Locker_t& locker);

        static maybe<Form_t*>                           Form(Raw_Form_ID_t raw_form_id);
        static maybe<Form_t*>                           Form(some<Mod_t*> mod, Raw_Form_Index_t raw_form_index);
        static Vector_t<some<Form_t*>>                  Forms();
        static Vector_t<some<Form_t*>>                  Forms(Filter_i<some<Form_t*>>& filter);
        static void                                     Forms(Vector_t<some<Form_t*>>& results);
        static void                                     Forms(Vector_t<some<Form_t*>>& results, Filter_i<some<Form_t*>>& filter);

        static void                                     Iterate_Forms(Iterator_i<some<Form_t*>>& iterator);
        static void                                     Iterate_Forms_Periodically(Iterator_i<some<Form_t*>>& iterator, std::chrono::nanoseconds interval);

    public:
        u64                                 unk_000;                            // 000
        void*                               unk_008;                            // 008
        Array_t<maybe<Form_t*>>             form_caches[Form_Type_e::_TOTAL_];  // 010
        maybe<List_t<maybe<Region_t*>>*>    region_list;                        // D00
        Short_Array_t<maybe<Cell_t*>>       interior_cells;                     // D08
        Short_Array_t<maybe<Addon_Node_t*>> addon_nodes;                        // D20
        Double_List_t<maybe<Form_t*>>       bad_forms;                          // D38
        Form_ID_t                           next_id;                            // D50
        u32                                 pad_D54;                            // D54
        maybe<Mod_t*>                       active_mod;                         // D58
        List_t<maybe<Mod_t*>>               mods;                               // D60
        Array_t<maybe<Mod_t*>>              heavy_mods;                         // D70
        Array_t<maybe<Mod_t*>>              light_mods;                         // D88
        Bool_t                              boolean_flags[16];                  // DA0
        void*                               region_manager;                     // DB0
        u64                                 unk_DB8;                            // DB8

    public:
        Array_t<maybe<Actor_Base_t*>>&          Actor_Bases();
        Array_t<maybe<Faction_t*>>&             Factions();
        Array_t<maybe<Leveled_Actor_Base_t*>>&  Leveled_Actor_Bases();
        Array_t<maybe<Location_t*>>&            Locations();
        Array_t<maybe<Quest_t*>>&               Quests();
        Array_t<maybe<Race_t*>>&                Races();
        Array_t<maybe<Worldspace_t*>>&          Worldspaces();
    };
    STATIC_ASSERT(sizeof(Game_t) == 0xDC0);

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/dynamic_array.h"
#include "doticu_skylib/enum.h"
#include "doticu_skylib/forward_list.h"
#include "doticu_skylib/string.h"

#include "doticu_skylib/enum_form_flags.h"
#include "doticu_skylib/form_id.h"
#include "doticu_skylib/mod_index.h"

namespace doticu_skylib {

    class Cell_t;

    class Mod_Error_e : public Enum_t<u32>
    {
    public:
        enum : u32
        {
        };
        using Enum_t::Enum_t;
    };

    class Mod_Flags_e : public Enum_t<u32>
    {
    public:
        enum : u32
        {
            IS_MASTER = 1 << 0,
            IS_ALTERED = 1 << 1,

            IS_ACTIVE = 1 << 3, // doesn't seem to be correct. if a mod is inactive, it won't have an instance.

            IS_LIGHT = 1 << 9,
        };
        using Enum_t::Enum_t;
    };

    class Record_Header_Base_t
    {
    public:
        char    type[4];    // 00
        u32     body_size;  // 04 sizeof(header) + sizeof(body) == sizeof(record)

    public:
        Bool_t Has_Type(const char* type);
    };

    class Record_Header_t :
        public Record_Header_Base_t
    {
    public:
        Form_Flags_e    form_flags;         // 08
        Form_ID_t       form_id;            // 0C
        u32             version_control_1;  // 10
        u16             form_version;       // 14
        u16             version_control_2;  // 16

        void Log(Mod_t* mod, std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Record_Header_t) == 0x18);

    class Record_Group_t : public Record_Header_Base_t
    {
    public:
        char    inner_type[4];  // 08
        u32     unk_0C;         // 0C
        u64     unk_10;         // 10

    public:
        Bool_t Has_Inner_Type(const char* type);
    };
    STATIC_ASSERT(sizeof(Record_Group_t) == 0x18);

    class Sub_Record_Header_t : public Record_Header_Base_t
    {
    public:
    };
    STATIC_ASSERT(sizeof(Sub_Record_Header_t) == 0x8);

    class Mod_t
    {
    public:
        class Offset_e : Enum_t<Word_t>
        {
        public:
            enum
            {
                SEEK                    = 0x0017D550,   // 13898
                SEEK_NEXT_SUB_RECORD    = 0x0017D960,   // 13903
                CURRENT_SUB_RECORD_TYPE = 0x0017D910,   // 13902
                READ                    = 0x0017DA10,   // 13904
            };
            using Enum_t::Enum_t;
        };

    public:
        static size_t                   Active_Mod_Count();
        static size_t                   Active_Heavy_Mod_Count();
        static size_t                   Active_Light_Mod_Count();

        static Vector_t<some<Mod_t*>>   Active_Mods();
        static Vector_t<some<Mod_t*>>   Active_Heavy_Mods();
        static Vector_t<some<Mod_t*>>   Active_Light_Mods();
        static Array_t<maybe<Mod_t*>>&  Active_Heavy_Mods_2();
        static Array_t<maybe<Mod_t*>>&  Active_Light_Mods_2();

        static Bool_t                   Has_Active_Mod(some<const char*> mod_name);
        static maybe<Mod_t*>            Active_Mod(some<const char*> mod_name);
        static maybe<Mod_t*>            Active_Heavy_Mod(some<const char*> mod_name);
        static maybe<Mod_t*>            Active_Light_Mod(some<const char*> mod_name);

        static void                     Log_Active_Mods();
        static void                     Log_Active_Heavy_Mods();
        static void                     Log_Active_Light_Mods();

    public:
        Mod_Error_e             last_error;                 // 000
        u32                     pad_004;                    // 004
        Mod_t*                  parent_mod;                 // 008
        void*                   unk_map_010;                // 010
        u64                     unk_018;                    // 018
        u64                     unk_020;                    // 020
        u64                     unk_028;                    // 028
        void*                   unk_030;                    // 030
        void*                   unk_038;                    // 038
        void*                   unk_040;                    // 040
        void*                   unk_048;                    // 048
        void*                   unk_050;                    // 050
        char                    file_name[MAX_PATH];        // 058
        char                    file_path[MAX_PATH];        // 15C
        char*                   buffer;                     // 260
        u32                     buffer_count;               // 268
        u32                     first_cell_offset;          // 26C
        u32                     current_cell_offset;        // 270
        u32                     unk_274;                    // 274
        Cell_t*                 current_cell;               // 278
        u32                     current_reference_offset;   // 280
        Record_Header_t         current_record_header;      // 284
        Sub_Record_Header_t     current_sub_record_header;  // 29C
        u32                     file_size;                  // 2A4
        u32                     file_offset;                // 2A8
        u32                     current_record_offset;      // 2AC
        u32                     current_sub_record_offset;  // 2B0
        Record_Header_t         save_record_header;         // 2B4
        u32                     save_record_offset;         // 2CC
        u64                     save_sub_record_offset;     // 2D0
        u64                     unk_2D8;                    // 2D8
        u64                     unk_2E0;                    // 2E0
        u8                      unk_2E8;                    // 2E8
        Bool_t                  is_big_endian;              // 2E9
        u8                      unk_2EA;                    // 2EA
        u8                      pad_2EB;                    // 2EB
        WIN32_FIND_DATA         file_data;                  // 2EC
        Float_t                 unk_42C;                    // 42C
        u32                     unk_430;                    // 430
        u32                     unk_flags;                  // 434
        Mod_Flags_e             mod_flags;                  // 438
        u32                     pad_43C;                    // 43C
        List_t<const char*>     master_names;               // 440
        List_t<ULARGE_INTEGER*> master_file_datas;          // 450
        u32                     master_count;               // 460
        u32                     pad_464;                    // 464
        Mod_t**                 masters;                    // 468
        FILETIME                deleted_time;               // 470
        u8                      heavy_index;                // 478
        u8                      pad_479;                    // 479
        u16                     light_index;                // 47A
        u32                     pad_47C;                    // 47C
        Dynamic_String_t        creator;                    // 480
        Dynamic_String_t        summary;                    // 490
        char*                   uncompressed_buffer;        // 4A0
        u32                     uncompressed_buffer_length; // 4A8
        u32                     pad_4AC;                    // 4AC
        void*                   volatile_buffer;            // 4B0
        u32                     volatile_buffer_size;       // 4B8
        u32                     pad_4BC;                    // 4BC
        void*                   unk_4C0;                    // 4C0

    public:
        Bool_t                      Is_Heavy();
        Bool_t                      Is_Light();
        Bool_t                      Has_Form(some<Form_t*> form);
        Bool_t                      Has_Form(maybe<Form_ID_t> form_id);

        Bool_t                      Has_Current_Record_Type(const char* type);
        Bool_t                      Has_Current_Sub_Record_Type(const char* type);

        const char*                 Name();
        maybe<Heavy_Mod_Index_t>    Heavy_Mod_Index();
        maybe<Light_Mod_Index_t>    Light_Mod_Index();

        Bool_t                      Seek(u32 offset);
        //Bool_t                      Seek_Next_Record();
        Bool_t                      Seek_Next_Sub_Record();
        void                        Read(void* destination, u32 size);

        Bool_t                      Find_Record(const char* type, Form_ID_t form_id);
        const char*                 Allocate_Editor_ID(const char* type, Form_ID_t form_id);

        void                        Log_Records(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Mod_t) == 0x4C8);

}

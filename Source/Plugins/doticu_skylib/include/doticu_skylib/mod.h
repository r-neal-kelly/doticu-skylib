/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/enum.h"
#include "doticu_skylib/string.h"

#include "doticu_skylib/form_flags.h"
#include "doticu_skylib/form_id.h"

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

            IS_ACTIVE = 1 << 3,

            IS_LIGHT = 1 << 9,
        };
        using Enum_t::Enum_t;
    };

    class Mod_Form_t
    {
    public:
        char            type[4];            // 00
        u32             length;             // 04
        Form_Flags_e    flags;              // 08
        Form_ID_t       id;                 // 0C
        u32             control;            // 10
        u16             version;            // 14
        u16             control_version;    // 16
    };
    STATIC_ASSERT(sizeof(Mod_Form_t) == 0x18);

    class Mod_t
    {
    public:
        static size_t                   Active_Mod_Count();
        static size_t                   Active_Heavy_Mod_Count();
        static size_t                   Active_Light_Mod_Count();

        static Vector_t<some<Mod_t*>>   Active_Mods();
        static Vector_t<some<Mod_t*>>   Active_Heavy_Mods();
        static Vector_t<some<Mod_t*>>   Active_Light_Mods();
        static Array_t<Mod_t*>&         Active_Heavy_Mods_2();
        static Array_t<Mod_t*>&         Active_Light_Mods_2();

        static void                     Log_Active_Mods();
        static void                     Log_Active_Heavy_Mods();
        static void                     Log_Active_Light_Mods();

        static maybe<Mod_t*>            Active_Mod(some<const char*> mod_name);
        static some<Mod_t*>             Skyrim();

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
        Mod_Form_t              current_form;               // 284
        u32                     current_chunk_id;           // 29C
        u32                     chunk_size;                 // 2A0
        u32                     file_size;                  // 2A4
        u32                     file_offset;                // 2A8
        u32                     form_offset;                // 2AC
        u32                     chunk_offset;               // 2B0
        Mod_Form_t              save_form;                  // 2B4
        u32                     save_form_offset;           // 2CC
        u64                     save_chunk_offset;          // 2D0
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
        Bool_t              Is_Active();
        Bool_t              Is_Heavy();
        Bool_t              Is_Light();

        const char*         Name();
        maybe<Index_t>      Heavy_Index();
        maybe<Index_t>      Light_Index();
    };
    STATIC_ASSERT(sizeof(Mod_t) == 0x4C8);

}

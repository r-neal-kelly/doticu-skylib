/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/collections.h"
#include "doticu_skylib/xlist.h"

namespace doticu_skylib {

    class Cell_t;
    class Reference_t;

    class XY_t {
        Float_t x;
        Float_t y;
    };
    STATIC_ASSERT(sizeof(XY_t) == 0x8);

    class Cell_XY_t {
    public:
        s16 y;
        s16 x;
    };
    STATIC_ASSERT(sizeof(Cell_XY_t) == 0x4);

    class Worldspace_XY_t {
    public:
        s16 x;
        s16 y;
    };
    STATIC_ASSERT(sizeof(Worldspace_XY_t) == 0x4);

    typedef u8 Worldspace_Flags_t;
    enum class Worldspace_Flags_e : Worldspace_Flags_t {
        IS_SMALL = 1 << 0,
        CANT_FAST_TRAVEL = 1 << 1,
        HASNT_LOD_WATER = 1 << 3,
        HASNT_LANDSCAPE = 1 << 4,
        HASNT_SKY = 1 << 5,
        HAS_FIXED_DIMENSIONS = 1 << 6,
        HASNT_GRASS = 1 << 7,
    };

    class Worldspace_Info_t {
    public:
        u8 data[0x2C];
    };
    STATIC_ASSERT(sizeof(Worldspace_Info_t) == 0x2C);

    class Worldspace_Form_ID_Maps_t {
    public:
        class Array_t {
        public:
            u32 count; // 00
            Form_ID_t head;

            Form_ID_t At(Index_t index);
        };

    public:
        Hash_Map_t<Cell_XY_t, Array_t*>     cell_xy_to_form_ids;            // 00
        Hash_Map_t<Form_ID_t, Cell_XY_t>    form_id_to_cell_xy;             // 30
        Hash_Map_t<Cell_XY_t, Array_t*>     cell_xy_to_filtered_form_ids;   // 60
    };
    STATIC_ASSERT(sizeof(Worldspace_Form_ID_Maps_t) == 0x90);

    class Worldspace_t : public Form_t, public Name_Component_t, public Model_Component_t {
    public:
        enum {
            kTypeID = kFormType_WorldSpace,
        };

        static Vector_t<Worldspace_t*> Worldspaces();

    public:
        virtual ~Worldspace_t();

        Hash_Map_t<Cell_XY_t, Cell_t*>          xy_to_cell;                         // 058
        Cell_t*                                 persistent_cell;                    // 088
        void*                                   unk_090;                            // 090
        void*                                   climate;                            // 098
        Worldspace_Flags_t                      worldspace_flags;                   // 0A0
        u8                                      unk_0A1;                            // 0A1
        u16                                     parent_flags;                       // 0A2
        Worldspace_XY_t                         center_xy;                          // 0A4
        Hash_Map_t<u32, tArray<Reference_t*>>   unk_to_immobile_persistent_refs;    // 0A8
        tArray<Reference_t*>                    mobile_persistent_refs;             // 0D8
        void*                                   unk_0F0;                            // 0F0
        Cell_t*                                 sky_cell;                           // 0F8
        Hash_Map_t<Form_ID_t, Location_t*>      form_id_to_location;                // 100
        void*                                   unk_130;                            // 130
        void*                                   unk_138;                            // 138
        void*                                   unk_140;                            // 140
        void*                                   unk_148;                            // 148
        void*                                   unk_150;                            // 150
        Worldspace_t*                           parent_worldspace;                  // 158
        void*                                   unk_160;                            // 160
        void*                                   unk_168;                            // 168
        void*                                   unk_170;                            // 170
        Float_t                                 unk_178;                            // 178
        u32                                     pad_17C;                            // 17C
        u64                                     unk_180;                            // 180
        Worldspace_Info_t                       worldspace_info;                    // 188
        u32                                     pad_1B4;                            // 1B4
        void*                                   music;                              // 1B8
        XY_t                                    min_coords;                         // 1C0
        XY_t                                    max_coords;                         // 1C8
        Hash_Map_t<Mod_t*, void*>               mod_to_unk;                         // 1D0
        BSString                                editor_id;                          // 200
        Float_t                                 default_land_height;                // 210
        Float_t                                 default_water_height;               // 214
        Float_t                                 unk_218;                            // 218
        u32                                     pad_21C;                            // 21C
        void*                                   encounter_zone;                     // 220
        Location_t*                             location;                           // 228
        TESTexture                              unk_230;                            // 230
        TESTexture                              unk_240;                            // 240
        Worldspace_Form_ID_Maps_t               form_id_maps;                       // 250
        u64                                     unk_2E0;                            // 2E0
        Hash_Map_t<void*, void*>                unk_2E8;                            // 2E8
        Hash_Map_t<void*, void*>                unk_318;                            // 318
        Float_t                                 north_rotation;                     // 348
        u32                                     pad_34C;                            // 34C
        s8*                                     unk_350;                            // 350

        void Log();
    };
    STATIC_ASSERT(sizeof(Worldspace_t) == 0x358);

}

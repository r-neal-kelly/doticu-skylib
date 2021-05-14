/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/component_model.h"
#include "doticu_skylib/component_name.h"
#include "doticu_skylib/component_texture.h"
#include "doticu_skylib/dynamic_array.h"
#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/string.h"

namespace doticu_skylib {

    class Cell_t;
    class Encounter_Zone_t;
    class Location_t;
    class Reference_t;

    class Worldspace_Flags_e : public Enum_t<u8>
    {
    public:
        enum : u8
        {
            IS_SMALL                = 1 << 0,
            CANT_FAST_TRAVEL        = 1 << 1,
            HASNT_LOD_WATER         = 1 << 3,
            HASNT_LANDSCAPE         = 1 << 4,
            HASNT_SKY               = 1 << 5,
            HAS_FIXED_DIMENSIONS    = 1 << 6,
            HASNT_GRASS             = 1 << 7,
        };
        using Enum_t::Enum_t;
    };

    class Worldspace_Info_t
    {
    public:
        u8 data[0x2C];
    };
    STATIC_ASSERT(sizeof(Worldspace_Info_t) == 0x2C);

    class Worldspace_Form_ID_Maps_t
    {
    public:
        Hash_Map_t<s16_yx, Type_Array_t<Form_ID_t>*>    cell_xy_to_form_ids;            // 00
        Hash_Map_t<Form_ID_t, s16_yx>                   form_id_to_cell_xy;             // 30
        Hash_Map_t<s16_yx, Type_Array_t<Form_ID_t>*>    cell_xy_to_filtered_form_ids;   // 60
    };
    STATIC_ASSERT(sizeof(Worldspace_Form_ID_Maps_t) == 0x90);

    class Worldspace_t :    // TESWorldSpace
        public Form_t,      // 000
        public Name_c,      // 020
        public Model_c      // 030
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::WORLDSPACE,
        };

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E13658, // 513891
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        static Vector_t<some<Worldspace_t*>>    Worldspaces_Dynamic();
        static void                             Worldspaces_Dynamic(Vector_t<some<Worldspace_t*>>& results);

        static Vector_t<some<Worldspace_t*>>    Worldspaces_Static();
        static void                             Worldspaces_Static(Vector_t<some<Worldspace_t*>>& results);

    public:
        virtual ~Worldspace_t();

    public:
        Hash_Map_t<s16_yx, maybe<Cell_t*>>              yx_to_cell;                         // 058
        maybe<Cell_t*>                                  persistent_cell;                    // 088
        void*                                           unk_090;                            // 090
        void*                                           climate;                            // 098
        Worldspace_Flags_e                              worldspace_flags;                   // 0A0
        u8                                              unk_0A1;                            // 0A1
        u16                                             parent_flags;                       // 0A2
        s16_xy                                          center_xy;                          // 0A4
        Hash_Map_t<u32, Array_t<maybe<Reference_t*>>>   unk_to_immobile_persistent_refs;    // 0A8
        Array_t<maybe<Reference_t*>>                    mobile_persistent_refs;             // 0D8
        void*                                           unk_0F0;                            // 0F0
        maybe<Cell_t*>                                  sky_cell;                           // 0F8
        Hash_Map_t<Form_ID_t, maybe<Location_t*>>       form_ids_to_locations;              // 100
        void*                                           unk_130;                            // 130
        void*                                           unk_138;                            // 138
        void*                                           unk_140;                            // 140
        void*                                           unk_148;                            // 148
        void*                                           unk_150;                            // 150
        maybe<Worldspace_t*>                            parent_worldspace;                  // 158
        void*                                           unk_160;                            // 160
        void*                                           unk_168;                            // 168
        void*                                           unk_170;                            // 170
        Float_t                                         unk_178;                            // 178
        u32                                             pad_17C;                            // 17C
        u64                                             unk_180;                            // 180
        Worldspace_Info_t                               worldspace_info;                    // 188
        u32                                             pad_1B4;                            // 1B4
        void*                                           music;                              // 1B8
        f32_xy                                          min_coords;                         // 1C0
        f32_xy                                          max_coords;                         // 1C8
        Hash_Map_t<maybe<Mod_t*>, void*>                mod_to_unk;                         // 1D0
        Dynamic_String_t                                editor_id;                          // 200
        Float_t                                         default_land_height;                // 210
        Float_t                                         default_water_height;               // 214
        Float_t                                         unk_218;                            // 218
        u32                                             pad_21C;                            // 21C
        maybe<Encounter_Zone_t*>                        encounter_zone;                     // 220
        maybe<Location_t*>                              location;                           // 228
        Texture_c                                       texture_230;                        // 230
        Texture_c                                       texture_240;                        // 240
        Worldspace_Form_ID_Maps_t                       form_id_maps;                       // 250
        u64                                             unk_2E0;                            // 2E0
        Hash_Map_t<void*, void*>                        unk_2E8;                            // 2E8
        Hash_Map_t<void*, void*>                        unk_318;                            // 318
        Float_t                                         north_rotation;                     // 348
        u32                                             pad_34C;                            // 34C
        maybe<s8*>                                      unk_350;                            // 350

    public:
        Bool_t                          Can_Fast_Travel();
        Bool_t                          Cant_Fast_Travel();
        Bool_t                          Has_Location(some<Location_t*> location);
        Bool_t                          Has_Cell(some<Cell_t*> cell);

        String_t                        Any_Name();

        maybe<Location_t*>              Location();

        Vector_t<some<Worldspace_t*>>   Parents();
        void                            Parents(Vector_t<some<Worldspace_t*>>& results);

        Vector_t<some<Location_t*>>     Child_Locations();
        void                            Child_Locations(Vector_t<some<Location_t*>>& results);
        Vector_t<some<Location_t*>>     Location_And_Child_Locations();
        void                            Location_And_Child_Locations(Vector_t<some<Location_t*>>& results);

        Vector_t<some<Location_t*>>     Linear_Parent_Locations();
        void                            Linear_Parent_Locations(Vector_t<some<Location_t*>>& results);
        Vector_t<some<Location_t*>>     Location_And_Linear_Parent_Locations();
        void                            Location_And_Linear_Parent_Locations(Vector_t<some<Location_t*>>& results);

        void Log();
    };
    STATIC_ASSERT(sizeof(Worldspace_t) == 0x358);

}

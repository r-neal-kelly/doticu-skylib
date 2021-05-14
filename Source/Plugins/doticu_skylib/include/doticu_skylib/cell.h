/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_name.h"
#include "doticu_skylib/dynamic_array.h"
#include "doticu_skylib/enum_cell_flags.h"
#include "doticu_skylib/enum_cell_state.h"
#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/extra_list.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/form_owner.h"
#include "doticu_skylib/forward_list.h"
#include "doticu_skylib/interface.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/reference_handle.h"

namespace doticu_skylib {

    class Actor_Base_t;
    class Encounter_Zone_t;
    class Faction_t;
    class Land_t;
    class Location_t;
    class Reference_t;
    class Worldspace_t;

    class Exterior_Cell_t
    {
    public:
        s32_xy  cell_xy;        // 00
        char*   unk_08;         // 08
        void*   unk_10;         // 10
        f32_xy  world_xy;       // 18
        u8      unk_flags_20;   // 20
        u8      pad_21;         // 21
        u16     pad_22;         // 22
        u32     pad_24;         // 24
    };
    STATIC_ASSERT(sizeof(Exterior_Cell_t) == 0x28);

    class Interior_Cell_t
    {
    public:
    };

    class Attached_Cell_t
    {
    public:
        void*                       unk_000;            // 000
        void*                       cell_3D;            // 008
        void*                       unk_010;            // 010
        void*                       unk_018;            // 018
        void*                       unk_020;            // 020
        u64                         unk_028;            // 028
        u64                         unk_030;            // 030
        u64                         unk_038;            // 038
        Array_t<void*>              unk_040;            // 040
        Array_t<void*>              unk_058;            // 058
        Byte_t                      unk_070[0x80];      // 070
        List_t<Reference_Handle_t>  activating_refs;    // 0F0
        List_t<Reference_Handle_t>  unk_100;            // 100
        u64                         unk_110;            // 110
        Array_t<void*>              unk_118;            // 118
        Array_t<void*>              unk_130;            // 130
        Array_t<void*>              unk_148;            // 148
        Encounter_Zone_t*           encounter_zone;     // 160
        u64                         unk_168;            // 168
        u64                         unk_170;            // 170
        u64                         unk_178;            // 178
    };
    STATIC_ASSERT(sizeof(Attached_Cell_t) == 0x180);

    class Cell_t :      // TESObjectCELL
        public Form_t,  // 000
        public Name_c   // 020
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::CELL,
        };

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E13680, // 513892
            };

        public:
            using Enum_t::Enum_t;
        };

        union Cellterior_u
        {
        public:
            maybe<Interior_Cell_t*> interior;
            maybe<Exterior_Cell_t*> exterior;

        public:
            Cellterior_u() :
                interior(none<Interior_Cell_t*>())
            {
            }

            ~Cellterior_u()
            {
            }
        };

    public:
        static Vector_t<some<Cell_t*>>  Interior_Cells_Dynamic();
        static void                     Interior_Cells_Dynamic(Vector_t<some<Cell_t*>>& results);

        static Vector_t<some<Cell_t*>>  Interior_Cells_Static();
        static void                     Interior_Cells_Static(Vector_t<some<Cell_t*>>& results);

        static Vector_t<some<Cell_t*>>  Exterior_Cells();
        static void                     Exterior_Cells(Vector_t<some<Cell_t*>>& results);

        static Vector_t<some<Cell_t*>>  Grid_Cells();
        static void                     Grid_Cells(Vector_t<some<Cell_t*>>& results);

        static Vector_t<some<Cell_t*>>  Attached_Cells();
        static void                     Attached_Cells(Vector_t<some<Cell_t*>>& results);

        static Vector_t<some<Cell_t*>>  All_Cells();
        static void                     All_Cells(Vector_t<some<Cell_t*>>& results);

        static size_t                   Interior_Cell_Dynamic_Count();
        static size_t                   Interior_Cell_Static_Count();
        static size_t                   Exterior_Cell_Count();

    public:
        virtual ~Cell_t();

    public:
        u64                             spin_lock_1;        // 030
        u64                             spin_lock_2;        // 038
        Cell_Flags_e                    cell_flags;         // 040
        u16                             unk_042;            // 042
        Cell_State_e                    cell_state;         // 044
        Bool_t                          unk_045;            // 045
        Bool_t                          is_cell_detached;   // 046
        u8                              pad_047;            // 047
        Extra_List_t                    x_list;             // 048
        Cellterior_u                    cellterior;         // 060
        maybe<Land_t*>                  land;               // 068
        Float_t                         water_height;       // 070
        void*                           nav_meshes;         // 078
        Set_t<maybe<Reference_t*>>      references;         // 080
        maybe<Form_t*>                  unk_0B0;            // 0B0
        Array_t<maybe<Reference_t*>>    unk_0B8;            // 0B8
        Array_t<void*>                  unk_0D0;            // 0D0
        Array_t<void*>                  unk_0E8;            // 0E8
        Array_t<void*>                  unk_100;            // 100
        u64                             spin_lock_3;        // 118
        maybe<Worldspace_t*>            worldspace;         // 120
        maybe<Attached_Cell_t*>         attached_cell;      // 128
        void*                           lighting_template;  // 130
        u64                             unk_138;            // 138

    public:
        Bool_t                          Is_Attached();
        Bool_t                          Is_Exterior();
        Bool_t                          Is_Interior();

        Bool_t                          Can_Travel_From();
        Bool_t                          Has_Reference(some<Reference_t*> reference);

        maybe<Encounter_Zone_t*>        Encounter_Zone(Bool_t do_check_locations = true);
        
        maybe<Location_t*>              Location();
        maybe<Location_t*>              This_Location();
        maybe<Location_t*>              Worldspace_Location();

        Vector_t<some<Location_t*>>     Locations();
        void                            Locations(Vector_t<some<Location_t*>>& results);
        Vector_t<String_t>              Location_Names();
        void                            Location_Names(Vector_t<String_t>& results);

        Form_Owner_t                    Owner(Bool_t do_check_locations = true);
        maybe<Actor_Base_t*>            Actor_Base_Owner(Bool_t do_check_locations = true);
        maybe<Faction_t*>               Faction_Owner(Bool_t do_check_locations = true);

        maybe<Worldspace_t*>            Worldspace(Bool_t do_search = true);
        Vector_t<some<Worldspace_t*>>   Worldspaces();
        void                            Worldspaces(Vector_t<some<Worldspace_t*>>& results);

        String_t                        Any_Name();

        void                            Iterate_References(Iterator_i<some<Reference_t*>>& iterator);

    public:
        void    Log_Locations(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Cell_t) == 0x140);

}

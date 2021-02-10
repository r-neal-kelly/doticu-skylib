/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/forward_list.h"
#include "doticu_skylib/interface.h"

#include "doticu_skylib/enum_cell_flags.h"
#include "doticu_skylib/enum_cell_state.h"

#include "doticu_skylib/component_name.h"

#include "doticu_skylib/form.h"
#include "doticu_skylib/reference_handle.h"
#include "doticu_skylib/script_type.h"

#include "doticu_skylib/extra_list.h"

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

    class Cell_t :
        public Form_t,
        public Name_c
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::CELL,
        };

        union Cellterior_u
        {
            Exterior_Cell_t* exterior;
            void* interior;
        };

    public:
        static size_t                   Interior_Cell_Count();
        static size_t                   Loaded_Exterior_Cell_Count();
        static Vector_t<Cell_t*>        Interior_Cells();
        static Vector_t<Cell_t*>        Loaded_Exterior_Cells();
        static Vector_t<Cell_t*>        Loaded_Cells();
        static Vector_t<some<Cell_t*>>  Cells_In_Grid();
        static void                     Cells_In_Grid(Vector_t<some<Cell_t*>>& results);

    public:
        virtual ~Cell_t();

    public:
        u64                     spin_lock_1;        // 030
        u64                     spin_lock_2;        // 038
        Cell_Flags_e            cell_flags;         // 040
        u16                     unk_042;            // 042
        Cell_State_e            cell_state;         // 044
        Bool_t                  unk_045;            // 045
        Bool_t                  is_cell_detached;   // 046
        u8                      pad_047;            // 047
        Extra_List_t            x_list;             // 048
        Cellterior_u            cellterior;         // 060
        Land_t*                 land;               // 068
        Float_t                 water_height;       // 070
        void*                   nav_meshes;         // 078
        Set_t<Reference_t*>     references;         // 080
        Form_t*                 unk_0B0;            // 0B0
        Array_t<Reference_t*>   unk_0B8;            // 0B8
        Array_t<void*>          unk_0D0;            // 0D0
        Array_t<void*>          unk_0E8;            // 0E8
        Array_t<void*>          unk_100;            // 100
        u64                     spin_lock_3;        // 118
        Worldspace_t*           worldspace;         // 120
        Attached_Cell_t*        attached_cell;      // 128
        void*                   lighting_template;  // 130
        u64                     unk_138;            // 138

    public:
        Bool_t                          Is_Interior();
        Bool_t                          Is_Exterior();
        Bool_t                          Is_Attached();
        Bool_t                          Can_Travel_From();
        Bool_t                          Has_Reference(some<Reference_t*> reference);

        maybe<Actor_Base_t*>            Actor_Base_Owner(Bool_t do_check_locations = true);
        maybe<Encounter_Zone_t*>        Encounter_Zone(Bool_t do_check_locations = true);
        maybe<Faction_t*>               Faction_Owner(Bool_t do_check_locations = true);
        Location_t*                     Location();
        Vector_t<Location_t*>           Locations();
        void                            Locations(Vector_t<Location_t*>& results);
        Vector_t<String_t>              Location_Names();
        void                            Location_Names(Vector_t<String_t>& results);
        maybe<Form_t*>                  Owner(Bool_t do_check_locations = true);
        maybe<Worldspace_t*>            Worldspace(Bool_t do_check_locations = true);
        Vector_t<some<Worldspace_t*>>   Worldspaces();
        void                            Worldspaces(Vector_t<some<Worldspace_t*>>& results);

        String_t                        Any_Name();

        void                            References(Iterator_i<void, Reference_t*>& iterator);
    };
    STATIC_ASSERT(sizeof(Cell_t) == 0x140);

}

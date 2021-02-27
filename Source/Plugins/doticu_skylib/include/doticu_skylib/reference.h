/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/alias_id.h"
#include "doticu_skylib/collections.h"
#include "doticu_skylib/enum_collision_layer_type.h"
#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/extra_list.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/interface.h"
#include "doticu_skylib/ni_collidable.h"
#include "doticu_skylib/ni_point.h"
#include "doticu_skylib/reference_count.h"
#include "doticu_skylib/reference_handle.h"
#include "doticu_skylib/unique.h"
#include "doticu_skylib/unknown.h"

namespace doticu_skylib {

    class Actor_t;
    class Actor_Base_t;
    class Cell_t;
    class Container_c;
    class Container_Changes_t;
    class Dialogue_Branch_t;
    class Faction_t;
    class Form_List_t;
    class Keyword_t;
    class Location_t;
    class NI_3D_t;
    class Quest_t;
    class Reference_Attached_State_t;
    class Worldspace_t;

    class Reference_t :             // TESObjectREFR
        public Form_t,              // 00
        public Reference_Count_t,   // 20
        public Event_Sink_t<void*>, // 30
        public Animation_Graphs_t   // 38
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::REFERENCE,
        };

        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI                            = 0x01E13798, // 513899

                CREATE_REFERENCE_HANDLE         = 0x001320F0, // 12193
                LOOKUP_REFERENCE_HANDLE_1       = 0x001328A0, // 12203
                INVALID_REFERENCE_HANDLE        = 0x01EBEABC, // 514164

                GET_NAME                        = 0x002961F0, // 19354
                GET_OWNER                       = 0x002A6670, // 19789
                GET_WORLDSPACE                  = 0x00299750, // 19389

                INITIALIZE_CONTAINER_CHANGES    = 0x001D8E40, // 15802

                PLACE_AT_ME                     = 0x009951F0, // 55672
                MOVE_TO_OFFSET                  = 0x009AE5C0, // 56227
            };
            using Enum_t::Enum_t;
        };

        class Form_Flags_e :
            public Enum_t<u32>
        {
        public:
            enum : value_type
            {
                IS_DELETED      = static_cast<value_type>(1 << 5),
                IS_PERSISTENT   = static_cast<value_type>(1 << 10),
                IS_DISABLED     = static_cast<value_type>(1 << 11),
            };
            using Enum_t::Enum_t;
        };

        class Form_Change_Flags_e :
            public Enum_t<u32>
        {
        public:
            enum : value_type
            {
                CONTAINER   = static_cast<value_type>(1 << 5),
                EXTRA_LIST  = static_cast<value_type>(1 << 10), // this might be more specific
            };
            using Enum_t::Enum_t;
        };

    public:
        static Vector_t<some<Reference_t*>> Loaded_References(Filter_i<some<Reference_t*>>* filter = nullptr);
        static void                         Loaded_References(Vector_t<some<Reference_t*>>& results,
                                                              Filter_i<some<Reference_t*>>* filter = nullptr);

        static Vector_t<some<Reference_t*>> Loaded_Grid_References(Filter_i<some<Reference_t*>>* filter = nullptr);
        static void                         Loaded_Grid_References(Vector_t<some<Reference_t*>>& results,
                                                                   Filter_i<some<Reference_t*>>* filter = nullptr);
        static void                         Loaded_Grid_References(some<Form_List_t*> results,
                                                                   Filter_i<some<Reference_t*>>* filter = nullptr);

        static Reference_t*                 Create(some<Form_t*> base, u32 count, some<Reference_t*> at, Bool_t force_persist, Bool_t initially_disable);
        static Reference_t*                 From_Handle(Reference_Handle_t reference_handle);
        static Reference_Handle_t           Invalid_Handle(); // this should go on Reference_Handle_t, but I need to be careful that we don't use it with virtual functions from Skyrim types

    public:
        virtual             ~Reference_t();                             // 00

        virtual void        _3B(void);                                  // 3B
        virtual void        _3C(void);                                  // 3C
        virtual void        _3D(void);                                  // 3D
        virtual void        _3E(void);                                  // 3E
        virtual void        _3F(void);                                  // 3F
        virtual void        _40(void);                                  // 40
        virtual void        _41(void);                                  // 41
        virtual void        _42(void);                                  // 42
        virtual void        _43(void);                                  // 43
        virtual void        _44(void);                                  // 44
        virtual void        _45(void);                                  // 45
        virtual void        _46(void);                                  // 46
        virtual void        _47(void);                                  // 47
        virtual Bool_t      Has_Keyword(const Keyword_t* keyword);      // 48
        virtual void        _49(void);                                  // 49
        virtual void        _4A(void);                                  // 4A
        virtual void        _4B(void);                                  // 4B
        virtual void        _4C(void);                                  // 4C
        virtual Dialogue_Branch_t*  Get_Exclusive_Dialogue_Branch();    // 4D
        virtual void        _4E(void);                                  // 4E
        virtual void        _4F(void);                                  // 4F
        virtual void        _50(void);                                  // 50
        virtual void        _51(void);                                  // 51
        virtual void        _52(void);                                  // 52
        virtual void        _53(void);                                  // 53
        virtual void        _54(void);                                  // 54
        virtual void        _55(void);                                  // 55
        virtual void        _56(void);                                  // 56
        virtual void        _57(void);                                  // 57
        virtual void        _58(void);                                  // 58
        virtual void        _59(void);                                  // 59
        virtual void        _5A(void);                                  // 5A
        virtual void        _5B(void);                                  // 5B
        virtual void        _5C(void);                                  // 5C
        virtual void        _5D(void);                                  // 5D
        virtual void        _5E(void);                                  // 5E
        virtual void        _5F(void);                                  // 5F
        virtual void        _60(void);                                  // 60
        virtual void        _61(void);                                  // 61
        virtual void        _62(void);                                  // 62
        virtual void        _63(void);                                  // 63
        virtual void        _64(void);                                  // 64
        virtual void        _65(void);                                  // 65
        virtual void        _66(void);                                  // 66
        virtual void        _67(void);                                  // 67
        virtual void        _68(void);                                  // 68
        virtual void        _69(void);                                  // 69
        virtual void        _6A(void);                                  // 6A
        virtual void        _6B(void);                                  // 6B
        virtual void        _6C(void);                                  // 6C
        virtual void        _6D(void);                                  // 6D
        virtual void        _6E(void);                                  // 6E
        virtual NI_3D_t*    Get_3D_1(Bool_t get_first_person);          // 6F
        virtual NI_3D_t*    Get_3D_2();                                 // 70
        virtual void        _71(void);                                  // 71
        virtual void        _72(void);                                  // 72
        virtual void        _73(void);                                  // 73
        virtual void        _74(void);                                  // 74
        virtual void        _75(void);                                  // 75
        virtual void        _76(void);                                  // 76
        virtual void        _77(void);                                  // 77
        virtual void        _78(void);                                  // 78
        virtual void        _79(void);                                  // 79
        virtual void        _7A(void);                                  // 7A
        virtual void        _7B(void);                                  // 7B
        virtual void        _7C(void);                                  // 7C
        virtual void        _7D(void);                                  // 7D
        virtual void        _7E(void);                                  // 7E
        virtual void        _7F(void);                                  // 7F
        virtual void        _80(void);                                  // 80
        virtual void        _81(void);                                  // 81
        virtual void        _82(void);                                  // 82
        virtual void        _83(void);                                  // 83
        virtual void        _84(void);                                  // 84
        virtual void        _85(void);                                  // 85
        virtual void        _86(void);                                  // 86
        virtual void        _87(void);                                  // 87
        virtual void        _88(void);                                  // 88
        virtual void        _89(void);                                  // 89
        virtual void        _8A(void);                                  // 8A
        virtual void        _8B(void);                                  // 8B
        virtual void        _8C(void);                                  // 8C
        virtual NI_3D_t*    Get_Current_3D() const;                     // 8D (this is getting skeleton for actors.)
        virtual void        _8E(void);                                  // 8E
        virtual void        _8F(void);                                  // 8F
        virtual void        _90(void);                                  // 90
        virtual void        _91(void);                                  // 91
        virtual void        _92(void);                                  // 92
        virtual void        _93(void);                                  // 93
        virtual void        _94(void);                                  // 94
        virtual void        _95(void);                                  // 95
        virtual void        _96(void);                                  // 96
        virtual void        _97(void);                                  // 97
        virtual void        _98(void);                                  // 98
        virtual Bool_t      Get_Is_Dead(Bool_t is_not_essential);       // 99 (not sure about the bool...)
        virtual void        _9A(void);                                  // 9A
        virtual void        _9B(void);                                  // 9B
        virtual void        _9C(void);                                  // 9C
        virtual void        _9D(void);                                  // 9D
        virtual void        _9E(void);                                  // 9E
        virtual void        _9F(void);                                  // 9F
        virtual void        _A0(void);                                  // A0
        virtual void        _A1(void);                                  // A1

    public:
        maybe<Form_t*>                      base_form;          // 40
        NI_Point_3_t                        rotation;           // 48
        NI_Point_3_t                        position;           // 54
        maybe<Cell_t*>                      parent_cell;        // 60
        maybe<Reference_Attached_State_t*>  attached_state;     // 68
        Extra_List_t                        x_list;             // 70
        u64                                 unk_88;             // 88
        u16                                 scale;              // 90
        s8                                  model_state;        // 92
        Bool_t                              is_pre_destroyed;   // 93
        u32                                 pad_94;             // 94

    public:
        Bool_t Is_Alive();
        Bool_t Is_Dead();
        Bool_t Is_Deleted();
        Bool_t Isnt_Deleted();
        Bool_t Is_Enabled();
        Bool_t Is_Disabled();
        Bool_t Is_Persistent();
        Bool_t Is_Temporary();
        Bool_t Is_Attached();
        Bool_t Is_Detached();
        Bool_t Is_Quest_Item();
        Bool_t Is_Aliased(some<Quest_t*> quest);
        Bool_t Is_Aliased(some<Quest_t*> quest, Alias_ID_t alias_id);

        Bool_t Has_Owner(some<Actor_t*> actor);
        Bool_t Has_Potential_Thief(some<Actor_t*> actor);

        const char*                         Name();
        String_t                            Any_Name();

        maybe<Actor_Base_t*>                Actor_Base_Owner();
        Cell_t*                             Cell(Bool_t do_check_worldspace = true);
        Vector_t<some<NI_Collidable_t*>>    Collidables();
        void                                Collidables(Vector_t<some<NI_Collidable_t*>>& results);
        maybe<Collision_Layer_Type_e>       Collision_Layer_Type();
        void                                Collision_Layer_Type(some<Collision_Layer_Type_e> collision_layer_type);
        maybe<Container_c*>                 Component_Container();
        maybe<Container_Changes_t*>         Container_Changes(Bool_t do_force_create);
        maybe<Faction_t*>                   Faction_Owner();
        Location_t*                         Location();
        maybe<Form_t*>                      Owner();
        maybe<Worldspace_t*>                Worldspace(Bool_t do_check_locations = true);
        
        Vector_t<Location_t*>               Locations();
        void                                Locations(Vector_t<Location_t*>& results);
        Vector_t<Quest_t*>                  Quests();
        void                                Quests(Vector_t<Quest_t*>& results);
        Vector_t<some<Worldspace_t*>>       Worldspaces();
        void                                Worldspaces(Vector_t<some<Worldspace_t*>>& results);

        Reference_Handle_t  To_Handle();

        Float_t Distance_Between(some<Reference_t*> other);

        void Move_To_Offset(some<Reference_t*> target,
                            maybe<Cell_t*> target_cell,
                            maybe<Worldspace_t*> target_worldspace,
                            f32_xyz& offset,
                            f32_xyz& rotation);
        void Move_To_Offset(some<Reference_t*> target, f32_xyz& offset, f32_xyz& rotation);
        void Move_To_Orbit(some<Reference_t*> origin, Float_t radius, Float_t degree);

        void Select_In_Console();

        void Enable();
        void Disable();

        void Mark_For_Delete(Bool_t do_disable = true);

        void Add_Item(some<Form_t*> item, s16 delta);

    public:
        void Activate(some<Reference_t*> activator, unique<Callback_i<Bool_t>> callback);
        void Is_In_Dialogue_With_Player(unique<Callback_i<Bool_t>> callback);
    };
    STATIC_ASSERT(sizeof(Reference_t) == 0x98);

}

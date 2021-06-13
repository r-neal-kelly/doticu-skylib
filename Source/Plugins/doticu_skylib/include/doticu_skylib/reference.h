/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/alias_id.h"
#include "doticu_skylib/collections.h"
#include "doticu_skylib/enum_collision_layer_type.h"
#include "doticu_skylib/enum_remove_reason.h"
#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/event_handler.h"
#include "doticu_skylib/extra_list.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/form_owner.h"
#include "doticu_skylib/interface.h"
#include "doticu_skylib/ni_collidable.h"
#include "doticu_skylib/ni_point.h"
#include "doticu_skylib/read_write_lock.h"
#include "doticu_skylib/reference_container.h"
#include "doticu_skylib/reference_count.h"
#include "doticu_skylib/reference_handle.h"
#include "doticu_skylib/sp32.h"
#include "doticu_skylib/unique.h"
#include "doticu_skylib/unknown.h"

namespace doticu_skylib {

    class Actor_t;
    class Actor_Base_t;
    class Alias_Base_t;
    class Alias_Reference_t;
    class Bound_Object_t;
    class Cell_t;
    class Container_c;
    class Container_Changes_t;
    class Container_Changes_Entry_t;
    class Container_Entry_t;
    class Dialogue_Branch_t;
    class Extra_Container_Changes_t;
    class Extra_List_t;
    class Faction_t;
    class Form_List_t;
    class Keyword_t;
    class Location_t;
    class NI_3D_t;
    class NI_Point_3_t;
    class Package_t;
    class Quest_t;
    class Reference_t;
    class Reference_Attached_State_t;
    class Worldspace_t;

    class Reference_t :                 // TESObjectREFR
        public Form_t,                  // 00
        public Reference_Count_t,       // 20
        public Event_Handler_t<void*>,  // 30
        public Animation_Graphs_t       // 38
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::REFERENCE,
        };

        static constexpr const char* SCRIPT_NAME = "ObjectReference";

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI                        = 0x01E13798, // 513899

                CREATE_REFERENCE_HANDLE     = 0x001320F0, // 12193
                LOOKUP_REFERENCE_HANDLE_1   = 0x001328A0, // 12203
                INVALID_REFERENCE_HANDLE    = 0x01EBEABC, // 514164

                IS_STEALABLE                = 0x0029A330, // 19400

                MAY_LAWFULLY_BE_TAKEN_BY    = 0x002A6EE0, // 19805

                GET_NAME                    = 0x002961F0, // 19354
                GET_THIS_OR_CELL_OWNER      = 0x002A6670, // 19789
                GET_WORLDSPACE              = 0x00299750, // 19389

                SOME_CONTAINER_CHANGES      = 0x001D8E40, // 15802

                PLACE_AT_ME                 = 0x009951F0, // 55672
                MOVE_TO_OFFSET              = 0x009AE5C0, // 56227
            };
            using Enum_t::Enum_t;
        };

        class Form_Flags_e :
            public Enum_t<u32>
        {
        public:
            enum enum_type : value_type
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
            enum enum_type : value_type
            {
                CONTAINER   = static_cast<value_type>(1 << 5),
                BASE_FORM   = static_cast<value_type>(1 << 7),
                EXTRA_LIST  = static_cast<value_type>(1 << 10), // this might be more specific
            };
            using Enum_t::Enum_t;
        };

    public:
        static Vector_t<some<Reference_t*>> All_References();
        static void                         All_References(Vector_t<some<Reference_t*>>& results);

        static Vector_t<some<Reference_t*>> All_References(Filter_i<some<Reference_t*>>& filter);
        static void                         All_References(Vector_t<some<Reference_t*>>& results, Filter_i<some<Reference_t*>>& filter);

        static Vector_t<some<Reference_t*>> All_References_In_Cells();
        static void                         All_References_In_Cells(Vector_t<some<Reference_t*>>& results);

        static Vector_t<some<Reference_t*>> All_References_In_Cells(Filter_i<some<Reference_t*>>& filter);
        static void                         All_References_In_Cells(Vector_t<some<Reference_t*>>& results, Filter_i<some<Reference_t*>>& filter);

        static Vector_t<some<Reference_t*>> Grid_References();
        static void                         Grid_References(Vector_t<some<Reference_t*>>& results);
        static void                         Grid_References(some<Form_List_t*> results);

        static Vector_t<some<Reference_t*>> Grid_References(Filter_i<some<Reference_t*>>& filter);
        static void                         Grid_References(Vector_t<some<Reference_t*>>& results, Filter_i<some<Reference_t*>>& filter);
        static void                         Grid_References(some<Form_List_t*> results, Filter_i<some<Reference_t*>>& filter);

        static void                         Iterate_All_References_Periodically(Iterator_i<some<Reference_t*>>& iterator,
                                                                                std::chrono::nanoseconds interval);

        static maybe<Reference_t*>          Create(some<Form_t*> base,
                                                   u32 count,
                                                   maybe<Reference_t*> at,
                                                   Bool_t do_force_persist,
                                                   Bool_t do_initially_disable,
                                                   Bool_t do_place_exactly);

        static Reference_t*                 From_Handle(Reference_Handle_t reference_handle);
        static Reference_Handle_t           Invalid_Handle(); // this should go on Reference_Handle_t, but I need to be careful that we don't use it with virtual functions from Skyrim types

    public:
        virtual                     ~Reference_t();                                     // 00

        virtual void                _3B(void);                                          // 3B
        virtual void                _3C(void);                                          // 3C
        virtual void                _3D(void);                                          // 3D
        virtual void                _3E(void);                                          // 3E
        virtual void                Do_Update_3D_Position(Bool_t do_warp);              // 3F
        virtual void                _40(void);                                          // 40
        virtual void                _41(void);                                          // 41
        virtual void                _42(void);                                          // 42
        virtual void                _43(void);                                          // 43
        virtual void                _44(void);                                          // 44
        virtual void                _45(void);                                          // 45
        virtual void                _46(void);                                          // 46
        virtual void                _47(void);                                          // 47
        virtual Bool_t              Get_Has_Keyword(const Keyword_t* keyword) const;    // 48
        virtual Package_t*          Get_Current_Alias_Package();                        // 49
        virtual void                _4A(void);                                          // 4A
        virtual void                _4B(void);                                          // 4B
        virtual void                _4C(void);                                          // 4C
        virtual Dialogue_Branch_t*  Get_Exclusive_Dialogue_Branch();                    // 4D
        virtual void                _4E(void);                                          // 4E
        virtual void                _4F(void);                                          // 4F
        virtual void                _50(void);                                          // 50
        virtual void                _51(void);                                          // 51
        virtual void                _52(void);                                          // 52
        virtual void                _53(void);                                          // 53
        virtual void                _54(void);                                          // 54
        virtual void                _55(void);                                          // 55
        virtual Reference_Handle_t  Do_Remove_Item(Bound_Object_t*      object,
                                                   s32                  count,
                                                   Raw_Remove_Reason_t  remove_reason,
                                                   Extra_List_t*        x_list,
                                                   Reference_t*         to,
                                                   NI_Point_3_t*        drop_position,
                                                   NI_Point_3_t*        rotation);      // 56 (keeps crashing.)
        virtual void                _57(void);                                          // 57
        virtual void                _58(void);                                          // 58
        virtual void                _59(void);                                          // 59
        virtual void                Do_Add_Item(Bound_Object_t* object,
                                                Extra_List_t*   x_list,
                                                s32             count,
                                                Reference_t*    from);                  // 5A
        virtual NI_Point_3_t        _5B(void);                                          // 5B
        virtual void                _5C(void);                                          // 5C
        virtual void                _5D(void);                                          // 5D
        virtual Bool_t              Get_Is_Child() const;                               // 5E
        virtual void                _5F(void);                                          // 5F
        virtual void                _60(void);                                          // 60
        virtual void                _61(void);                                          // 61
        virtual void                _62(void);                                          // 62
        virtual void                _63(void);                                          // 63
        virtual void                _64(void);                                          // 64
        virtual Bool_t              Do_Detach_3D(NI_3D_t* ni_3d);                       // 65
        virtual void                Do_Init_3D();                                       // 66
        virtual void                _67(void);                                          // 67
        virtual void                _68(void);                                          // 68
        virtual void                _69(void);                                          // 69
        virtual NI_3D_t*            Do_Load_3D(Bool_t unk_1);                           // 6A
        virtual void                _6B(void);                                          // 6B
        virtual void                _6C(void);                                          // 6C
        virtual void                _6D(void);                                          // 6D
        virtual void                _6E(void);                                          // 6E
        virtual NI_3D_t*            Get_3D_1(Bool_t get_first_person);                  // 6F
        virtual NI_3D_t*            Get_3D_2();                                         // 70
        virtual void                _71(void);                                          // 71
        virtual void                _72(void);                                          // 72
        virtual void                _73(void);                                          // 73
        virtual void                _74(void);                                          // 74
        virtual void                _75(void);                                          // 75
        virtual void                _76(void);                                          // 76
        virtual void                _77(void);                                          // 77
        virtual void                _78(void);                                          // 78
        virtual void                _79(void);                                          // 79
        virtual void                _7A(void);                                          // 7A
        virtual void                _7B(void);                                          // 7B
        virtual void                _7C(void);                                          // 7C
        virtual void                Do_Update_Animation(Float_t delta);                 // 7D
        virtual void                _7E(void);                                          // 7E
        virtual void                _7F(void);                                          // 7F
        virtual void                _80(void);                                          // 80
        virtual void                _81(void);                                          // 81
        virtual void                _82(void);                                          // 82
        virtual void                _83(void);                                          // 83
        virtual void                _84(void);                                          // 84
        virtual void                Do_Havok_Move(Bool_t do_force);                     // 85
        virtual void                _86(void);                                          // 86
        virtual void                _87(void);                                          // 87
        virtual void                _88(void);                                          // 88
        virtual void                _89(void);                                          // 89
        virtual void                Do_Reset_Inventory(Bool_t do_only_leveled);         // 8A
        virtual void                _8B(void);                                          // 8B
        virtual void                _8C(void);                                          // 8C
        virtual NI_3D_t*            Get_Current_3D() const;                             // 8D (this is getting skeleton for actors.)
        virtual void                _8E(void);                                          // 8E
        virtual void                _8F(void);                                          // 8F
        virtual void                _90(void);                                          // 90
        virtual void                _91(void);                                          // 91
        virtual void                _92(void);                                          // 92
        virtual void                _93(void);                                          // 93
        virtual void                _94(void);                                          // 94
        virtual void                _95(void);                                          // 95
        virtual void                _96(void);                                          // 96
        virtual void                _97(void);                                          // 97
        virtual void                _98(void);                                          // 98
        virtual Bool_t              Get_Is_Dead(Bool_t is_not_essential);               // 99 (not sure about the bool...)
        virtual void                _9A(void);                                          // 9A
        virtual void                _9B(void);                                          // 9B
        virtual void                _9C(void);                                          // 9C
        virtual void                _9D(void);                                          // 9D
        virtual void                _9E(void);                                          // 9E
        virtual void                _9F(void);                                          // 9F
        virtual void                _A0(void);                                          // A0
        virtual void                _A1(void);                                          // A1

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
        Bool_t Is_Based_On_Actor_Base();
        Bool_t Is_Based_On_Component_Container();
        Bool_t Is_Based_On_Container();

    public:
        Bool_t          Is_Alive();
        Bool_t          Is_Dead();
        Bool_t          Is_Deleted();
        Bool_t          Isnt_Deleted();
        Bool_t          Is_Enabled();
        Bool_t          Is_Disabled();
        Bool_t          Is_Persistent();
        Bool_t          Is_Temporary();
        Bool_t          Is_Attached();
        Bool_t          Is_Detached();

        Bool_t          Is_Stealable();

        maybe<Bool_t>   Is_In_Interior_Cell();
        maybe<Bool_t>   Is_In_Exterior_Cell();

        Bool_t          Is_In_Dialogue_With_Player();

        Bool_t          Is_Aliased();
        Bool_t          Is_Aliased(some<Quest_t*> quest);
        Bool_t          Is_Aliased(some<Quest_t*> quest, Alias_ID_t alias_id);
        Bool_t          Is_Aliased_As_Protected();
        Bool_t          Is_Aliased_As_Essential();
        Bool_t          Is_Quest_Item();

        Bool_t          May_Lawfully_Be_Taken_By(some<Actor_t*> actor, Bool_t do_test_factions, Bool_t must_be_owned);

        Bool_t          Has_Owner();
        Bool_t          Has_Owner(some<Actor_t*> actor);
        Bool_t          Has_Potential_Thief(some<Actor_t*> actor);

        Bool_t          Has_Keyword(some<Keyword_t*> keyword) const;

        Bool_t          Has_Extra_Text_Display();
        Bool_t          Has_Custom_Name();
        Bool_t          Has_Quest_Text_Display(some<Quest_t*> quest);

    public:
        const char*                         Name();
        void                                Name(String_t name);
        String_t                            Any_Name();

        void                                Add_Item(some<Bound_Object_t*> object,
                                                     maybe<Extra_List_t*> loose_x_list,
                                                     s32 non_zero_count,
                                                     maybe<Reference_t*> from);

        Vector_t<some<Alias_Base_t*>>       Alias_Bases();
        Vector_t<some<Alias_Reference_t*>>  Alias_References();

        maybe<Cell_t*>                      Cell(Bool_t do_check_worldspace);
        Vector_t<some<NI_Collidable_t*>>    Collidables();
        void                                Collidables(Vector_t<some<NI_Collidable_t*>>& results);
        maybe<Collision_Layer_Type_e>       Collision_Layer_Type();
        void                                Collision_Layer_Type(some<Collision_Layer_Type_e> collision_layer_type);

        maybe<Container_c*>                 Base_Component_Container();
        maybe<Container_Entry_t*>           Base_Component_Container_Entry(some<Bound_Object_t*> object);
        maybe<Extra_Container_Changes_t*>   Maybe_Extra_Container_Changes();
        some<Extra_Container_Changes_t*>    Some_Extra_Container_Changes();
        maybe<Container_Changes_t*>         Maybe_Container_Changes();
        some<Container_Changes_t*>          Some_Container_Changes();
        maybe<Container_Changes_Entry_t*>   Maybe_Container_Changes_Entry(some<Bound_Object_t*> object);
        some<Container_Changes_Entry_t*>    Some_Container_Changes_Entry(some<Bound_Object_t*> object);
        Reference_Container_t               Container();
        maybe<Reference_Container_Entry_t>  Maybe_Container_Entry(some<Bound_Object_t*> object);
        some<Reference_Container_Entry_t>   Some_Container_Entry(some<Bound_Object_t*> object);
        sp32                                Container_Entry_Count(some<Bound_Object_t*> object);

        Vector_t<some<Reference_t*>>        Contained_References() const;
        void                                Contained_References(Vector_t<some<Reference_t*>>& results) const;

        maybe<Location_t*>                  Location();
        maybe<Location_t*>                  Cell_Location();
        maybe<Location_t*>                  Worldspace_Location();
        
        maybe<Worldspace_t*>                Worldspace(Bool_t do_check_cell_locations = true);
        
        Vector_t<some<Location_t*>>         Locations();
        void                                Locations(Vector_t<some<Location_t*>>& results);
        Vector_t<some<Quest_t*>>            Quests();
        void                                Quests(Vector_t<some<Quest_t*>>& results);
        Vector_t<some<Worldspace_t*>>       Worldspaces();
        void                                Worldspaces(Vector_t<some<Worldspace_t*>>& results);

        s32                                 Gold_Value();

        Reference_Handle_t                  To_Handle();

        Float_t                             Distance_Between(some<Reference_t*> other);

        void                                Move_To_Offset(maybe<Reference_t*> target_reference,
                                                           maybe<Cell_t*> target_cell,
                                                           maybe<Worldspace_t*> target_worldspace,
                                                           f32_xyz offset,
                                                           f32_xyz rotation);
        void                                Move_To_Offset(some<Reference_t*> reference_target, f32_xyz offset, f32_xyz rotation);
        void                                Move_To_Offset(some<Cell_t*> interior_cell_target, f32_xyz offset, f32_xyz rotation);
        void                                Move_To_Offset(some<Worldspace_t*> worldspace_target, f32_xyz offset, f32_xyz rotation);

        void                                Move_To_Orbit(some<Reference_t*> origin, Float_t radius, Float_t degree);

        void                                Copy_Worn_Items(some<Reference_t*> other);
        void                                Destroy_Non_Quest_Items();

        Bool_t                              Remove_Blank_Name(Bool_t whitespace_counts_as_blank);

    public:
        void                        Add_Item(some<Form_t*> item, s16 delta);                                // AddItem
        void                        Remove_Item(some<Form_t*> item, s16 delta);                             // RemoveItem

        void                        Enable();                                                               // Enable
        void                        Disable();                                                              // Disable

        void                        Mark_For_Delete(Bool_t do_disable = true);                              // MarkForDelete

        Form_Owner_t                This_Or_Cell_Owner();
        maybe<Actor_Base_t*>        This_Or_Cell_Actor_Base_Owner();
        maybe<Faction_t*>           This_Or_Cell_Faction_Owner();
        maybe<Form_Owner_t>         This_Owner();
        void                        This_Owner(Form_Owner_t owner);                                         // SetOwnership
        maybe<maybe<Actor_Base_t*>> This_Actor_Base_Owner();
        void                        This_Actor_Base_Owner(maybe<Actor_Base_t*> actor_base);
        maybe<maybe<Faction_t*>>    This_Faction_Owner();
        void                        This_Faction_Owner(maybe<Faction_t*> faction);
        Form_Owner_t                Cell_Owner();

        void                        Push_Away(some<Actor_t*> actor, Int_t force);                           // PushActorAway
        void                        Apply_Havok_Impulse(Float_t x, Float_t y, Float_t z, Float_t force);    // ApplyHavokImpulse

        void                        Select_In_Console();                                                    // prid

    public:
        void Is_Activation_Blocked(Bool_t value, maybe<Virtual::Callback_i*> v_callback);               // BlockActivation
        void Is_Activation_Blocked(Bool_t value, maybe<unique<Callback_i<>>> callback);

        void Is_Open(Bool_t value, maybe<Virtual::Callback_i*> v_callback);                             // SetOpen
        void Is_Open(Bool_t value, maybe<unique<Callback_i<>>> callback);

        void Actor_Base_Owner(some<Virtual::Callback_i*> v_callback);                                   // GetActorOwner
        void Actor_Base_Owner(some<unique<Callback_i<maybe<Actor_Base_t*>>>> callback);

        void Faction_Owner(some<Virtual::Callback_i*> v_callback);                                      // GetFactionOwner
        void Faction_Owner(some<unique<Callback_i<maybe<Faction_t*>>>> callback);

        void Activate(some<Reference_t*> activator,
                      Bool_t do_only_default_processing,
                      maybe<Virtual::Callback_i*> v_callback);                                          // Activate
        void Activate(some<Reference_t*> activator,
                      Bool_t do_only_default_processing,
                      maybe<unique<Callback_i<Bool_t>>> callback);

        void Add_Item(some<Form_t*> item,
                      Int_t count,
                      Bool_t do_silently,
                      maybe<Virtual::Callback_i*> v_callback);                                          // AddItem
        void Add_Item(some<Form_t*> item,
                      Int_t count,
                      Bool_t do_silently,
                      maybe<unique<Callback_i<>>> callback);

        void Find_Closest_Actor(Float_t radius, some<Virtual::Callback_i*> v_callback);
        void Find_Closest_Actor(Float_t radius, some<unique<Callback_i<maybe<Actor_t*>>>> callback);

        void Open_Inventory(maybe<unique<Callback_i<Bool_t>>> callback);

        void Play_Animation(String_t animation_event_name, maybe<Virtual::Callback_i*> v_callback); // (we can use consle SendAnimEvent)
        void Play_Animation(String_t animation_event_name, maybe<unique<Callback_i<>>> callback);
        void Reset_Animation(maybe<Virtual::Callback_i*> v_callback);
        void Reset_Animation(maybe<unique<Callback_i<>>> callback);

        void Push_Away(some<Actor_t*> actor, Float_t force, maybe<Virtual::Callback_i*> v_callback);    // PushActorAway
        void Push_Away(some<Actor_t*> actor, Float_t force, maybe<unique<Callback_i<>>> callback);

        void    Remove_Item(some<Form_t*> form,
                            Int_t count,
                            Bool_t do_silently,
                            maybe<Reference_t*> to,
                            maybe<Virtual::Callback_i*> v_callback);                                                // RemoveItem
        void    Remove_Item(some<Form_t*> form,
                            Int_t count,
                            Bool_t do_silently,
                            maybe<Reference_t*> to,
                            maybe<unique<Callback_i<>>> callback);

        void Start_Translation_To(Float_t x_position, Float_t y_position, Float_t z_position,
                                  Float_t x_degree, Float_t y_degree, Float_t z_degree,
                                  Float_t movement_speed, Float_t max_rotation_speed,
                                  maybe<Virtual::Callback_i*> v_callback);                              // TranslateTo
        void Start_Translation_To(Float_t x_position, Float_t y_position, Float_t z_position,
                                  Float_t x_degree, Float_t y_degree, Float_t z_degree,
                                  Float_t movement_speed, Float_t max_rotation_speed,
                                  maybe<unique<Callback_i<>>> callback);
        void Stop_Translation(maybe<Virtual::Callback_i*> v_callback);                                  // StopTranslation
        void Stop_Translation(maybe<unique<Callback_i<>>> callback);

        void Apply_Havok_Impulse(Float_t x, Float_t y, Float_t z, Float_t force,
                                 maybe<Virtual::Callback_i*> v_callback);                               // ApplyHavokImpulse
        void Apply_Havok_Impulse(Float_t x, Float_t y, Float_t z, Float_t force,
                                 maybe<unique<Callback_i<>>> callback);

        void Unfill_Aliases(maybe<unique<Callback_i<>>> callback);

    public:
        void    Log_Name_And_Type(std::string indent = "");
        void    Log_Contained_References(std::string indent = "");
        void    Log_Extra_List(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Reference_t) == 0x98);

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/actor_handle.h"
#include "doticu_skylib/actor_state.h"
#include "doticu_skylib/actor_value_modifiers.h"
#include "doticu_skylib/actor_values.h"
#include "doticu_skylib/actor_values_data.h"
#include "doticu_skylib/atomic_number.h"
#include "doticu_skylib/dynamic_array.h"
#include "doticu_skylib/enum_actor_critical_stage.h"
#include "doticu_skylib/enum_actor_flags.h"
#include "doticu_skylib/enum_magic_slot.h"
#include "doticu_skylib/enum_relation.h"
#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/enum_sex.h"
#include "doticu_skylib/event_handler.h"
#include "doticu_skylib/faction_and_rank.h"
#include "doticu_skylib/form_owner.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/magic_target.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/ni_point.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/reference_handle.h"
#include "doticu_skylib/small_dynamic_array.h"
#include "doticu_skylib/string.h"

namespace doticu_skylib {

    class Actor_AI_t;
    class Actor_Base_t;
    class Actor_High_AI_t;
    class Actor_Mover_t;
    class Color_t;
    class Dialogue_Branch_t;
    class Faction_t;
    class Havok_Actor_Controller_t;
    class Havok_Actor_Rigid_Body_Controller_t;
    class Keyword_t;
    class Leveled_Actor_Base_t;
    class Magic_Base_t;
    class Movement_Actor_Controller_t;
    class Outfit_t;
    class Race_t;
    class Script_t;
    class Spell_t;
    class Voice_Type_t;

    class Actor_t :                         // Actor
        public Reference_t,                 // 000
        public Magic_Target_t,              // 098
        public Actor_Values_t,              // 0B0
        public Actor_State_t,               // 0B8
        public Event_Handler_t<void**>,     // 0C8
        public Event_Handler_t<void***>,    // 0D0
        public Animation_Updater_i          // 0D8
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::ACTOR,
        };

        static constexpr const char* SCRIPT_NAME = "Actor";

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI                    = 0x01E14AD8, // 513915

                ADD_SPELL               = 0x0062F560, // 37771
                EVALUATE_PACKAGE        = 0x005DB310, // 36407
                GET_LEVEL               = 0x005D62E0, // 36344
                QUEUE_NI_NODE_UPDATE    = 0x00693110, // 39181
                REMOVE_SPELL            = 0x0062F720, // 37772
            };
            using Enum_t::Enum_t;
        };

        class Form_Flags_e :
            public Enum_t<u32>
        {
        public:
            enum enum_type : value_type
            {
                STARTS_DEAD         = static_cast<value_type>(1 << 9),
                IGNORES_ALLY_HITS   = static_cast<value_type>(1 << 20),
            };
            using Enum_t::Enum_t;
        };

        class Form_Change_Flags_e :
            public Enum_t<u32>
        {
        public:
            enum enum_type : value_type
            {
                FORM_FLAGS = static_cast<value_type>(1 << 0),
            };
            using Enum_t::Enum_t;
        };

    public:
        static Vector_t<some<Actor_t*>> All();
        static void                     All(Vector_t<some<Actor_t*>>& results);

        static Vector_t<some<Actor_t*>> All(Filter_i<some<Actor_t*>>& filter);
        static void                     All(Vector_t<some<Actor_t*>>& results, Filter_i<some<Actor_t*>>& filter);

        static Vector_t<some<Actor_t*>> All_Actors_In_Cells();
        static void                     All_Actors_In_Cells(Vector_t<some<Actor_t*>>& results);

        static maybe<Actor_t*>          Create(some<Form_t*> base, Bool_t do_persist, Bool_t do_pacify);
        static maybe<Actor_t*>          Create(some<Actor_Base_t*> base, Bool_t do_persist, Bool_t do_pacify, Bool_t do_static);
        static maybe<Actor_t*>          Create(some<Leveled_Actor_Base_t*> base, Bool_t do_persist, Bool_t do_pacify, Bool_t do_static);

    public:
        virtual         ~Actor_t();                                                                                     // 000

        // Reference_t
        virtual Bool_t  Get_Is_Dead(Bool_t is_not_essential) override;                                                  // 099

        // Actor_t
        virtual void    _0A2(void);                                                                                     // 0A2
        virtual void    _0A3(void);                                                                                     // 0A3
        virtual void    _0A4(void);                                                                                     // 0A4
        virtual void    _0A5(void);                                                                                     // 0A5
        virtual void    _0A6(void);                                                                                     // 0A6
        virtual void    _0A7(void);                                                                                     // 0A7
        virtual void    _0A8(void);                                                                                     // 0A8
        virtual void    _0A9(void);                                                                                     // 0A9
        virtual void    _0AA(void);                                                                                     // 0AA
        virtual void    Do_Resurrect(Bool_t do_reset_inventory, Bool_t do_attach_3d);                                   // 0AB
        virtual void    _0AC(void);                                                                                     // 0AC
        virtual void    Do_Update(Float_t delta);                                                                       // 0AD
        virtual void    _0AE(void);                                                                                     // 0AE
        virtual void    _0AF(some<Havok_Actor_Controller_t*> actor_controller);                                         // 0AF
        virtual void    _0B0(void);                                                                                     // 0B0
        virtual void    _0B1(void);                                                                                     // 0B1
        virtual void    _0B2(void);                                                                                     // 0B2
        virtual void    _0B3(void);                                                                                     // 0B3
        virtual void    _0B4(void);                                                                                     // 0B4
        virtual void    _0B5(void);                                                                                     // 0B5
        virtual void    _0B6(void);                                                                                     // 0B6
        virtual void    _0B7(void);                                                                                     // 0B7
        virtual void    _0B8(void);                                                                                     // 0B8
        virtual void    _0B9(void);                                                                                     // 0B9
        virtual void    _0BA(void);                                                                                     // 0BA
        virtual void    _0BB(void);                                                                                     // 0BB
        virtual void    _0BC(void);                                                                                     // 0BC
        virtual void    _0BD(void);                                                                                     // 0BD
        virtual void    _0BE(void);                                                                                     // 0BE
        virtual void    _0BF(void);                                                                                     // 0BF
        virtual void    _0C0(void);                                                                                     // 0C0
        virtual void    _0C1(void);                                                                                     // 0C1
        virtual void    _0C2(void);                                                                                     // 0C2
        virtual void    _0C3(void);                                                                                     // 0C3
        virtual void    _0C4(void);                                                                                     // 0C4
        virtual void    _0C5(void);                                                                                     // 0C5
        virtual void    _0C6(void);                                                                                     // 0C6
        virtual void    _0C7(void);                                                                                     // 0C7
        virtual void    _0C8(void);                                                                                     // 0C8
        virtual void    _0C9(void);                                                                                     // 0C9
        virtual void    _0CA(void);                                                                                     // 0CA
        virtual void    _0CB(void);                                                                                     // 0CB
        virtual void    _0CC(void);                                                                                     // 0CC
        virtual void    _0CD(void);                                                                                     // 0CD
        virtual void    _0CE(void);                                                                                     // 0CE
        virtual void    _0CF(void);                                                                                     // 0CF
        virtual void    _0D0(void);                                                                                     // 0D0
        virtual void    _0D1(void);                                                                                     // 0D1
        virtual void    _0D2(void);                                                                                     // 0D2
        virtual void    _0D3(void);                                                                                     // 0D3
        virtual void    _0D4(void);                                                                                     // 0D4
        virtual void    _0D5(void);                                                                                     // 0D5
        virtual void    _0D6(void);                                                                                     // 0D6
        virtual void    _0D7(void);                                                                                     // 0D7
        virtual void    _0D8(void);                                                                                     // 0D8
        virtual void    _0D9(void);                                                                                     // 0D9
        virtual void    _0DA(void);                                                                                     // 0DA
        virtual void    _0DB(void);                                                                                     // 0DB
        virtual void    _0DC(void);                                                                                     // 0DC
        virtual void    _0DD(void);                                                                                     // 0DD
        virtual void    _0DE(void);                                                                                     // 0DE
        virtual void    _0DF(void);                                                                                     // 0DF
        virtual void    Do_Update_Alpha();                                                                              // 0E0
        virtual void    Set_Alpha(Float_t alpha);                                                                       // 0E1
        virtual Float_t Get_Alpha();                                                                                    // 0E2
        virtual Bool_t  Get_Is_In_Combat();                                                                             // 0E3
        virtual void    Do_Update_Combat();                                                                             // 0E4
        virtual void    Do_Stop_Combat();                                                                               // 0E5
        virtual void    _0E6(void);                                                                                     // 0E6
        virtual void    _0E7(void);                                                                                     // 0E7
        virtual void    _0E8(void);                                                                                     // 0E8
        virtual void    _0E9(void);                                                                                     // 0E9
        virtual void    _0EA(void);                                                                                     // 0EA
        virtual void    _0EB(void);                                                                                     // 0EB
        virtual void    _0EC(void);                                                                                     // 0EC
        virtual void    _0ED(void);                                                                                     // 0ED
        virtual void    _0EE(void);                                                                                     // 0EE
        virtual void    _0EF(void);                                                                                     // 0EF
        virtual void    _0F0(void);                                                                                     // 0F0
        virtual void    _0F1(void);                                                                                     // 0F1
        virtual void    _0F2(void);                                                                                     // 0F2
        virtual void    _0F3(void);                                                                                     // 0F3
        virtual void    _0F4(void);                                                                                     // 0F4
        virtual void    _0F5(void);                                                                                     // 0F5
        virtual void    _0F6(void);                                                                                     // 0F6
        virtual void    _0F7(void);                                                                                     // 0F7
        virtual void    _0F8(void);                                                                                     // 0F8
        virtual Bool_t  Get_Is_In_Faction(const Faction_t* faction) const;                                              // 0F9
        virtual void    _0FA(void);                                                                                     // 0FA
        virtual void    _0FB(void);                                                                                     // 0FB
        virtual void    _0FC(void);                                                                                     // 0FC
        virtual void    _0FD(void);                                                                                     // 0FD
        virtual void    _0FE(void);                                                                                     // 0FE
        virtual void    _0FF(void);                                                                                     // 0FF
        virtual void    _100(void);                                                                                     // 100
        virtual void    _101(void);                                                                                     // 101
        virtual void    _102(void);                                                                                     // 102
        virtual void    _103(void);                                                                                     // 103
        virtual void    _104(void);                                                                                     // 104
        virtual void    _105(void);                                                                                     // 105
        virtual void    _106(void);                                                                                     // 106
        virtual void    _107(void);                                                                                     // 107
        virtual void    _108(void);                                                                                     // 108
        virtual void    _109(void);                                                                                     // 109
        virtual void    _10A(void);                                                                                     // 10A
        virtual void    _10B(void);                                                                                     // 10B
        virtual void    _10C(void);                                                                                     // 10C
        virtual void    _10D(void);                                                                                     // 10D
        virtual void    Do_Kill(Actor_t* killer, Float_t damage, Bool_t do_send_event, Bool_t do_ragdoll_instantly);    // 10E
        virtual void    _10F(void);                                                                                     // 10F
        virtual void    _110(void);                                                                                     // 110
        virtual void    _111(void);                                                                                     // 111
        virtual void    _112(void);                                                                                     // 112
        virtual void    _113(void);                                                                                     // 113
        virtual void    _114(void);                                                                                     // 114
        virtual void    _115(void);                                                                                     // 115
        virtual void    _116(void);                                                                                     // 116
        virtual void    _117(void);                                                                                     // 117
        virtual void    _118(void);                                                                                     // 118
        virtual void    _119(void);                                                                                     // 119
        virtual void    _11A(void);                                                                                     // 11A
        virtual void    _11B(void);                                                                                     // 11B
        virtual void    _11C(void);                                                                                     // 11C
        virtual void    _11D(void);                                                                                     // 11D
        virtual void    _11E(void);                                                                                     // 11E
        virtual void    _11F(void);                                                                                     // 11F
        virtual void    _120(void);                                                                                     // 120
        virtual void    _121(void);                                                                                     // 121
        virtual void    _122(void);                                                                                     // 122
        virtual void    _123(void);                                                                                     // 123
        virtual void    _124(void);                                                                                     // 124
        virtual void    _125(void);                                                                                     // 125
        virtual void    _126(void);                                                                                     // 126
        virtual void    _127(void);                                                                                     // 127

    public:
        Actor_Flags_1_e                     actor_flags_1;                              // 0E0
        Float_t                             update_target_timer;                        // 0E4
        Actor_Critical_Stage_e              actor_critical_stage;                       // 0E8
        u32                                 pad_0EC;                                    // 0EC
        maybe<Actor_AI_t*>                  actor_ai;                                   // 0F0
        Reference_Handle_t                  last_dialogue_target;                       // 0F8 (connected to Dialogue_Info_Instance_t?)
        Actor_Handle_t                      current_combat_target;                      // 0FC
        Actor_Handle_t                      current_killer;                             // 100
        Float_t                             check_dead_body_timer;                      // 104
        Float_t                             voice_timer;                                // 108
        Float_t                             under_water_timer;                          // 10C
        s32                                 thief_crime_stamp;                          // 110
        s32                                 action_value;                               // 114
        Float_t                             action_timer;                               // 118
        u32                                 unk_11C;                                    // 11C
        NI_Point_3_t                        editor_location_position;                   // 120
        Float_t                             editor_location_rotation;                   // 12C
        maybe<Form_t*>                      editor_location_form;                       // 130
        maybe<Location_t*>                  editor_location_location;                   // 138
        maybe<Actor_Mover_t*>               actor_mover;                                // 140
        maybe<Movement_Actor_Controller_t*> actor_movement_controller;                  // 148
        void*                               unk_150;                                    // 150
        void*                               actor_combat_controller;                    // 158
        maybe<Faction_t*>                   vendor_faction;                             // 160
        Float_t                             vendor_faction_timer;                       // 168
        u32                                 unk_16C;                                    // 16C
        u32                                 unk_170;                                    // 170
        u32                                 unk_174;                                    // 174
        u32                                 unk_178;                                    // 178
        u32                                 unk_17C;                                    // 17C
        u64                                 unk_180;                                    // 180
        Small_Array_t<maybe<Spell_t*>>      added_spells;                               // 188
        void*                               actor_magic_casters[Magic_Slot_e::_TOTAL_]; // 1A0
        maybe<Magic_Base_t*>                equipped_spells[Magic_Slot_e::_TOTAL_];     // 1C0
        maybe<Form_t*>                      equipped_power;                             // 1E0
        u32                                 unk_1E8;                                    // 1E8
        u32                                 pad_1EC;                                    // 1EC
        maybe<Race_t*>                      race;                                       // 1F0
        Float_t                             equipped_weight;                            // 1F8
        Actor_Flags_2_e                     actor_flags_2;                              // 1FC
        Actor_Values_Data_t                 actor_values_data;                          // 200
        maybe<Dialogue_Branch_t*>           exclusive_dialogue_branch;                  // 220
        Actor_Value_Modifiers_t             health_modifiers;                           // 228
        Actor_Value_Modifiers_t             magicka_modifiers;                          // 234
        Actor_Value_Modifiers_t             stamina_modifiers;                          // 240
        Actor_Value_Modifiers_t             voice_points_modifiers;                     // 24C
        Float_t                             last_update;                                // 258
        u32                                 last_seen_time;                             // 25C
        void*                               biped_animation;                            // 260
        Float_t                             armor_rating;                               // 268
        Float_t                             armor_base_faction_sum;                     // 26C
        s8                                  unk_270;                                    // 270
        u8                                  unk_271;                                    // 271
        u8                                  unk_272;                                    // 272
        u8                                  unk_273;                                    // 273
        u32                                 unk_274;                                    // 274
        u64                                 unk_278;                                    // 278
        u64                                 unk_280;                                    // 280
        CRITICAL_SECTION                    havok_critical_section;                     // 288

    public:
        Bool_t                                      Is_Unique();
        Bool_t                                      Is_Generic();
        Bool_t                                      Is_Child();
        Bool_t                                      Isnt_Child();
        Bool_t                                      Is_Vampire();
        Bool_t                                      Isnt_Vampire();
        Bool_t                                      Is_In_Combat();
        Bool_t                                      Isnt_In_Combat();

        Bool_t                                      Has_Mount();
        Bool_t                                      Has_Rider();
        Bool_t                                      Has_Actor_Base(some<Actor_Base_t*> actor_base);
        Bool_t                                      Hasnt_Actor_Base(some<Actor_Base_t*> actor_base);

        Bool_t                                      Is_In_Faction(some<Faction_t*> faction);
        Bool_t                                      Isnt_In_Faction(some<Faction_t*> faction);
        Bool_t                                      Is_Owner_Of(some<Reference_t*> reference);
        Bool_t                                      Is_Potential_Thief_Of(some<Reference_t*> reference);

    public:
        Sex_e                                       Sex();
        maybe<Race_t*>                              Race();

        u16                                         Level() const;

        maybe<Havok_Actor_Controller_t*>            Havok_Actor_Controller();
        maybe<Havok_Actor_Rigid_Body_Controller_t*> Havok_Actor_Rigid_Body_Controller();
        Vector_t<Keyword_t*>                        Keywords(Bool_t include_templates = true);
        void                                        Keywords(Vector_t<Keyword_t*>& results, Bool_t include_templates = true);
        maybe<Actor_t*>                             Mount();
        maybe<Actor_t*>                             Rider();

        maybe<Actor_Base_t*>                        Actor_Base();
        void                                        Actor_Base(some<Actor_Base_t*> actor_base, Bool_t do_save);
        maybe<Actor_Base_t*>                        Actor_Base_Root();
        maybe<Actor_Base_t*>                        Actor_Base_Template_Root();
        maybe<Actor_Base_t*>                        Identifiable_Static_Actor_Base();
        Vector_t<Actor_Base_t*>                     Actor_Bases();
        void                                        Actor_Bases(Vector_t<Actor_Base_t*>& results);

        maybe<Outfit_t*>                            Base_Default_Outfit();
        void                                        Base_Default_Outfit(maybe<Outfit_t*> outfit);
        maybe<Outfit_t*>                            Base_Sleep_Outfit();
        void                                        Base_Sleep_Outfit(maybe<Outfit_t*> outfit);

        maybe<Voice_Type_t*>                        Base_Voice_Type();
        void                                        Base_Voice_Type(maybe<Voice_Type_t*> voice_type);
        maybe<Voice_Type_t*>                        Race_Voice_Type();
        void                                        Race_Voice_Type(maybe<Voice_Type_t*> voice_type);
        maybe<Voice_Type_t*>                        Voice_Type();

        maybe<Actor_AI_t*>                          Actor_AI();
        maybe<Actor_High_AI_t*>                     Actor_High_AI();

        const char*                                 Base_Name();
        String_t                                    Any_Name();

        maybe<Raw_Faction_Rank_t>                   Faction_Rank(some<Faction_t*> faction);
        void                                        Faction_Rank(some<Faction_t*> faction, some<Raw_Faction_Rank_t> rank);
        maybe<Raw_Faction_Rank_t>                   Base_Faction_Rank(some<Faction_t*> faction);
        void                                        Base_Faction_Rank(some<Faction_t*> faction, some<Raw_Faction_Rank_t> rank);
        Vector_t<Faction_And_Rank_t>                Factions_And_Ranks(Bool_t remove_negatives = true);
        void                                        Factions_And_Ranks(Vector_t<Faction_And_Rank_t>& results, Bool_t remove_negatives = true);
        maybe<Faction_t*>                           Crime_Faction();
        void                                        Crime_Faction(some<Faction_t*> crime_faction);
        maybe<Faction_t*>                           Base_Crime_Faction();
        void                                        Base_Crime_Faction(maybe<Faction_t*> crime_faction);

        some<Relation_e>                            Base_Relation(some<Actor_Base_t*> other);
        void                                        Base_Relation(some<Actor_Base_t*> other, some<Relation_e> relation);

        Bool_t                                      Is_Player_Teammate();
        void                                        Is_Player_Teammate(Bool_t value);

        Bool_t                                      Can_Do_Favors();
        void                                        Can_Do_Favors(Bool_t value);

        Bool_t                                      Can_Talk_To_Player();
        void                                        Can_Talk_To_Player(Bool_t value);

        Bool_t                                      Ignores_Ally_Hits();
        void                                        Ignores_Ally_Hits(Bool_t value);

        Bool_t                                      Is_Hidden_From_Stealth_Eye();
        void                                        Is_Hidden_From_Stealth_Eye(Bool_t value);

        Bool_t                                      Has_AI();
        void                                        Has_AI(Bool_t value);
        void                                        Reset_AI();

        Bool_t                                      Add_Spell(some<Spell_t*> spell);
        Bool_t                                      Remove_Spell(some<Spell_t*> spell);
        void                                        Reset_Spell(some<Spell_t*> spell);

        Bool_t                                      Is_Ghost();
        void                                        Is_Ghost(Bool_t value);

        Bool_t                                      Can_Autostart_Bard_Performance();
        void                                        Can_Autostart_Bard_Performance(Bool_t value);

        Bool_t                                      Can_Be_Resurrected();
        void                                        Can_Be_Resurrected(Bool_t value);

        void                                        Evaluate_Package(Bool_t do_immediately, Bool_t do_reset_ai);
        void                                        Pacify();
        void                                        Queue_NI_Node_Update(Bool_t do_update_weight);
        void                                        Reset_Actor_Value(Actor_Value_Type_e actor_value_type);
        void                                        Stop_Combat();
        void                                        Stop_Combat_And_Alarm();
        void                                        Update_3D(maybe<Script_t*> script);
        void                                        Update_Equipment();

        maybe<Actor_t*>                             Current_Combat_Target();

    public:
        Float_t Alpha();
        void    Alpha(Float_t alpha, maybe<Script_t*> script);              // SetActorAlpha

        Float_t Base_Weight();
        void    Base_Weight(Float_t weight, maybe<Script_t*> script);       // SetNPCWeight

        void    Is_Doing_Favor(Bool_t value, maybe<Script_t*> script);      // SetFavorState

        Bool_t  Is_Forced_To_Sneak();
        void    Is_Forced_To_Sneak(Bool_t value, maybe<Script_t*> script);  // SetForceSneak

    public:
        void    Alpha(Float_t alpha, Bool_t do_fade_in, maybe<Virtual::Callback_i*> v_callback);    // SetAlpha
        void    Alpha(Float_t alpha, Bool_t do_fade_in, maybe<unique<Callback_i<>>> callback);

        void    Kill(maybe<Actor_t*> killer,
                     Bool_t do_silently,
                     maybe<Virtual::Callback_i*> v_callback);                                       // Kill, KillSilent
        void    Kill(maybe<Actor_t*> killer,
                     Bool_t do_silently,
                     Bool_t do_force,
                     maybe<unique<Callback_i<>>> callback);

        void    Open_Inventory(Bool_t allow_non_teammates, maybe<Virtual::Callback_i*> v_callback); // OpenInventory
        void    Open_Inventory(Bool_t allow_non_teammates, maybe<unique<Callback_i<>>> callback);

        void    Resurrect(maybe<Virtual::Callback_i*> v_callback);                                  // Resurrect
        void    Resurrect(Bool_t do_keep_inventory,
                          Bool_t do_pacify,
                          Bool_t do_force,
                          maybe<unique<Callback_i<>>> callback);

        void    Stop_Bard_Performance(maybe<unique<Callback_i<>>> callback);

        void    Update_Equipment(maybe<unique<Callback_i<>>> callback);

    public:
        void    Log_Actor_Values(std::string indent = "");
        void    Log_Added_Spells(std::string indent = "");
        void    Log_Factions_And_Ranks(std::string indent = "");
        void    Log_Magic_Target(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Actor_t) == 0x2B0);

}

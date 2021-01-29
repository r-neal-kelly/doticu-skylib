/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"

#include "doticu_skylib/enum_actor_critical_stage.h"
#include "doticu_skylib/enum_actor_flags.h"

#include "doticu_skylib/actor_state.h"
#include "doticu_skylib/actor_values.h"
#include "doticu_skylib/faction_and_rank.h"
#include "doticu_skylib/magic_target.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/script_type.h"
#include "doticu_skylib/sex.h"

namespace doticu_skylib {

    class Actor_AI_t;
    class Actor_Base_t;
    class Actor_Controller_t;
    class Faction_t;
    class Keyword_t;
    class Leveled_Actor_Base_t;

    class Actor_t :
        public Reference_t,
        public Magic_Target_t,
        public Actor_Values_t,
        public Actor_State_t,
        public Event_Sink_t<void**>,
        public Event_Sink_t<void***>,
        public Animation_Updater_i
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::ACTOR,
        };

        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E14AD8,
            };
            using Enum_t::Enum_t;
        };

        class Form_Flags_e : public Enum_t<u32>
        {
        public:
            enum : value_type
            {
                IGNORES_FRIENDLY_HITS = 1 << 20,
            };
            using Enum_t::Enum_t;
        };

    public:
        static Vector_t<Actor_t*>   Loaded_Actors();
        static void                 Loaded_Actors(Vector_t<Actor_t*>& results);
        static void                 Log_Loaded_Actors();

        static maybe<Actor_t*> Create(some<Form_t*> base, Bool_t do_persist, Bool_t do_uncombative);
        static maybe<Actor_t*> Create(some<Actor_Base_t*> base, Bool_t do_persist, Bool_t do_uncombative, Bool_t do_static);
        static maybe<Actor_t*> Create(some<Leveled_Actor_Base_t*> base, Bool_t do_persist, Bool_t do_uncombative, Bool_t do_static);

    public:
        virtual         ~Actor_t();                                     // 000

        // Reference_t
        virtual Bool_t  Is_Dead(Bool_t is_not_essential) override;      // 099

        // Actor_t
        virtual void    _0A2(void);                                     // 0A2
        virtual void    _0A3(void);                                     // 0A3
        virtual void    _0A4(void);                                     // 0A4
        virtual void    _0A5(void);                                     // 0A5
        virtual void    _0A6(void);                                     // 0A6
        virtual void    _0A7(void);                                     // 0A7
        virtual void    _0A8(void);                                     // 0A8
        virtual void    _0A9(void);                                     // 0A9
        virtual void    _0AA(void);                                     // 0AA
        virtual void    _0AB(void);                                     // 0AB
        virtual void    _0AC(void);                                     // 0AC
        virtual void    _0AD(void);                                     // 0AD
        virtual void    _0AE(void);                                     // 0AE
        virtual void    _0AF(some<Actor_Controller_t*> actor_controller);   // 0AF
        virtual void    _0B0(void);                                     // 0B0
        virtual void    _0B1(void);                                     // 0B1
        virtual void    _0B2(void);                                     // 0B2
        virtual void    _0B3(void);                                     // 0B3
        virtual void    _0B4(void);                                     // 0B4
        virtual void    _0B5(void);                                     // 0B5
        virtual void    _0B6(void);                                     // 0B6
        virtual void    _0B7(void);                                     // 0B7
        virtual void    _0B8(void);                                     // 0B8
        virtual void    _0B9(void);                                     // 0B9
        virtual void    _0BA(void);                                     // 0BA
        virtual void    _0BB(void);                                     // 0BB
        virtual void    _0BC(void);                                     // 0BC
        virtual void    _0BD(void);                                     // 0BD
        virtual void    _0BE(void);                                     // 0BE
        virtual void    _0BF(void);                                     // 0BF
        virtual void    _0C0(void);                                     // 0C0
        virtual void    _0C1(void);                                     // 0C1
        virtual void    _0C2(void);                                     // 0C2
        virtual void    _0C3(void);                                     // 0C3
        virtual void    _0C4(void);                                     // 0C4
        virtual void    _0C5(void);                                     // 0C5
        virtual void    _0C6(void);                                     // 0C6
        virtual void    _0C7(void);                                     // 0C7
        virtual void    _0C8(void);                                     // 0C8
        virtual void    _0C9(void);                                     // 0C9
        virtual void    _0CA(void);                                     // 0CA
        virtual void    _0CB(void);                                     // 0CB
        virtual void    _0CC(void);                                     // 0CC
        virtual void    _0CD(void);                                     // 0CD
        virtual void    _0CE(void);                                     // 0CE
        virtual void    _0CF(void);                                     // 0CF
        virtual void    _0D0(void);                                     // 0D0
        virtual void    _0D1(void);                                     // 0D1
        virtual void    _0D2(void);                                     // 0D2
        virtual void    _0D3(void);                                     // 0D3
        virtual void    _0D4(void);                                     // 0D4
        virtual void    _0D5(void);                                     // 0D5
        virtual void    _0D6(void);                                     // 0D6
        virtual void    _0D7(void);                                     // 0D7
        virtual void    _0D8(void);                                     // 0D8
        virtual void    _0D9(void);                                     // 0D9
        virtual void    _0DA(void);                                     // 0DA
        virtual void    _0DB(void);                                     // 0DB
        virtual void    _0DC(void);                                     // 0DC
        virtual void    _0DD(void);                                     // 0DD
        virtual void    _0DE(void);                                     // 0DE
        virtual void    _0DF(void);                                     // 0DF
        virtual void    _0E0(void);                                     // 0E0
        virtual void    _0E1(void);                                     // 0E1
        virtual void    _0E2(void);                                     // 0E2
        virtual void    _0E3(void);                                     // 0E3
        virtual void    _0E4(void);                                     // 0E4
        virtual void    _0E5(void);                                     // 0E5
        virtual void    _0E6(void);                                     // 0E6
        virtual void    _0E7(void);                                     // 0E7
        virtual void    _0E8(void);                                     // 0E8
        virtual void    _0E9(void);                                     // 0E9
        virtual void    _0EA(void);                                     // 0EA
        virtual void    _0EB(void);                                     // 0EB
        virtual void    _0EC(void);                                     // 0EC
        virtual void    _0ED(void);                                     // 0ED
        virtual void    _0EE(void);                                     // 0EE
        virtual void    _0EF(void);                                     // 0EF
        virtual void    _0F0(void);                                     // 0F0
        virtual void    _0F1(void);                                     // 0F1
        virtual void    _0F2(void);                                     // 0F2
        virtual void    _0F3(void);                                     // 0F3
        virtual void    _0F4(void);                                     // 0F4
        virtual void    _0F5(void);                                     // 0F5
        virtual void    _0F6(void);                                     // 0F6
        virtual void    _0F7(void);                                     // 0F7
        virtual void    _0F8(void);                                     // 0F8
        virtual Bool_t  Is_In_Faction(const Faction_t* faction) const;  // 0F9
        virtual void    _0FA(void);                                     // 0FA
        virtual void    _0FB(void);                                     // 0FB
        virtual void    _0FC(void);                                     // 0FC
        virtual void    _0FD(void);                                     // 0FD
        virtual void    _0FE(void);                                     // 0FE
        virtual void    _0FF(void);                                     // 0FF
        virtual void    _100(void);                                     // 100
        virtual void    _101(void);                                     // 101
        virtual void    _102(void);                                     // 102
        virtual void    _103(void);                                     // 103
        virtual void    _104(void);                                     // 104
        virtual void    _105(void);                                     // 105
        virtual void    _106(void);                                     // 106
        virtual void    _107(void);                                     // 107
        virtual void    _108(void);                                     // 108
        virtual void    _109(void);                                     // 109
        virtual void    _10A(void);                                     // 10A
        virtual void    _10B(void);                                     // 10B
        virtual void    _10C(void);                                     // 10C
        virtual void    _10D(void);                                     // 10D
        virtual void    _10E(void);                                     // 10E
        virtual void    _10F(void);                                     // 10F
        virtual void    _110(void);                                     // 110
        virtual void    _111(void);                                     // 111
        virtual void    _112(void);                                     // 112
        virtual void    _113(void);                                     // 113
        virtual void    _114(void);                                     // 114
        virtual void    _115(void);                                     // 115
        virtual void    _116(void);                                     // 116
        virtual void    _117(void);                                     // 117
        virtual void    _118(void);                                     // 118
        virtual void    _119(void);                                     // 119
        virtual void    _11A(void);                                     // 11A
        virtual void    _11B(void);                                     // 11B
        virtual void    _11C(void);                                     // 11C
        virtual void    _11D(void);                                     // 11D
        virtual void    _11E(void);                                     // 11E
        virtual void    _11F(void);                                     // 11F
        virtual void    _120(void);                                     // 120
        virtual void    _121(void);                                     // 121
        virtual void    _122(void);                                     // 122
        virtual void    _123(void);                                     // 123
        virtual void    _124(void);                                     // 124
        virtual void    _125(void);                                     // 125
        virtual void    _126(void);                                     // 126
        virtual void    _127(void);                                     // 127

    public:
        Actor_Flags_1_e         actor_flags_1;          // 0E0
        Float_t                 update_target_timer;    // 0E4
        Actor_Critical_Stage_e  actor_critical_stage;   // 0E8
        u32                     pad_0EC;                // 0EC
        maybe<Actor_AI_t*>      actor_ai;               // 0F0
        Byte_t                  unk_data[0x1B8];        // 0F8

    public:
        Bool_t                          Is_Alive();
        Bool_t                          Is_Dead();
        Bool_t                          Is_Player_Teammate();
        Bool_t                          Isnt_Player_Teammate();

        Bool_t                          Is_Owner_Of(some<Reference_t*> reference);
        Bool_t                          Is_Potential_Thief_Of(some<Reference_t*> reference);

        Sex_e                           Sex();
        Race_t*                         Race();
        Actor_Base_t*                   Actor_Base();
        Actor_Base_t*                   Highest_Static_Actor_Base();
        Vector_t<Actor_Base_t*>         Actor_Bases();
        void                            Actor_Bases(Vector_t<Actor_Base_t*>& results);
        maybe<Actor_Controller_t*>      Actor_Controller();
        Vector_t<Faction_And_Rank_t>    Factions_And_Ranks(Bool_t remove_negatives = true);
        void                            Factions_And_Ranks(Vector_t<Faction_And_Rank_t>& results, Bool_t remove_negatives = true);
        Vector_t<Keyword_t*>            Keywords(Bool_t include_templates = true);
        void                            Keywords(Vector_t<Keyword_t*>& results, Bool_t include_templates = true);

        const char*                     Base_Name();
        String_t                        Any_Name();

    public:
        void                            Log_Factions_And_Ranks(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Actor_t) == 0x2B0);

}

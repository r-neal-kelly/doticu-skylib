/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/atomic_count.h"
#include "doticu_skylib/character.h"
#include "doticu_skylib/dynamic_array.h"
#include "doticu_skylib/forward_list.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/quest_objective_state.h"
#include "doticu_skylib/reference_handle.h"
#include "doticu_skylib/unknown.h"

namespace doticu_skylib {

    class Faction_t;
    class Havok_Player_t;
    class Havok_Player_Controller_t;
    class Package_Dialogue_t;
    class Perk_t;
    class Quest_Objective_t;

    class Crime_Counts_t
    {
    public:
        Float_t unk_0;  // 0
        Float_t unk_4;  // 4
        Float_t unk_8;  // 8
        Float_t unk_C;  // c
    };
    STATIC_ASSERT(sizeof(Crime_Counts_t) == 0x10);

    class Stolen_Counts_t
    {
    public:
        u32 unwitnessed;    // 0
        u32 witnessed;      // 4
    };
    STATIC_ASSERT(sizeof(Stolen_Counts_t) == 0x8);

    class Perk_And_Rank_t
    {
    public:
        Perk_t* perk;   // 0
        u8      rank;   // 8
        u8      pad_9;  // 9
        u16     pad_A;  // A
        u32     pad_C;  // C
    };
    STATIC_ASSERT(sizeof(Perk_And_Rank_t) == 0x10);

    class Friend_Counts_t
    {
    public:
        u16 friend_counts[4];   // 0
    };
    STATIC_ASSERT(sizeof(Friend_Counts_t) == 0x8);

    class Player_Objective_t
    {
    public:
        Quest_Objective_t*      objective;      // 0
        u32                     instance_id;    // 8
        Quest_Objective_State_e state;          // C
        u8                      pad_D;          // D
        u16                     pad_E;          // E

        void Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Player_Objective_t) == 0x10);

    class Player_t :
        public Character_t,
        public Event_Source_t<void*>,
        public Event_Source_t<void**>,
        public Event_Source_t<void***>,
        public Event_Sink_t<void****>,
        public Event_Sink_t<void*****>,
        public Event_Sink_t<void******>,
        public Event_Sink_t<void*******>
    {
    public:
        static some<Player_t*> Self();

    public:
        virtual ~Player_t(); // 0

    public:
        u32                                     unk_3D8;                    // 3D8
        u32                                     unk_3DC;                    // 3DC
        Hash_Map_t<Faction_t*, Crime_Counts_t>  crime_counts_map;           // 3E0
        Hash_Map_t<Faction_t*, Stolen_Counts_t> stolen_counts_map;          // 410
        Reference_Handle_t                      unk_440;                    // 440
        u32                                     unk_444;                    // 444
        Hash_Map_t<Faction_t*, Friend_Counts_t> friend_counts_map;          // 448
        f32_xyz                                 unk_478;                    // 478
        f32_xyz                                 unk_484;                    // 484
        f32_xyz                                 unk_490;                    // 490
        Float_t                                 unk_49C;                    // 49C
        u64                                     unk_4A0;                    // 4A0
        u64                                     unk_4A8;                    // 4A8
        Array_t<Perk_And_Rank_t*>               added_perks;                // 4B0
        Array_t<Perk_t*>                        perks;                      // 4C8
        Array_t<Perk_t*>                        standing_stone_perks;       // 4E0
        Array_t<Reference_Handle_t>             map_markers;                // 4F8
        Array_t<void*>                          unk_510;                    // 510
        Array_t<void*>                          unk_528;                    // 528
        Array_t<void*>                          unk_540;                    // 540
        Array_t<void*>                          unk_558;                    // 558
        List_t<void*>                           quest_log;                  // 570
        Array_t<Player_Objective_t>             objectives;                 // 580
        Hash_Map_t<void*, void*>                unk_598;                    // 598
        Hash_Map_t<void*, void*>                unk_5C8;                    // 5C8
        List_t<Reference_Handle_t>              dropped_references;         // 5F8

        Byte_t                                  unk_608[0xA8];              // 608

        maybe<Package_Dialogue_t*>              closest_dialogue;           // 6B0
        u32                                     unk_6B8;                    // 6B8
        u32                                     unk_6BC;                    // 6BC
        maybe<Package_Dialogue_t*>              ai_running_dialogue;        // 6C0
        s32                                     steal_warning_count;        // 6C8
        Float_t                                 steal_warning_timer;        // 6CC
        s32                                     pickpocket_warning_count;   // 6D0
        Float_t                                 pickpocket_warning_timer;   // 6D4

        Byte_t                                  unk_6D8[0x330];             // 6D8

        Atomic_Count_t                          teammate_count;             // A08

        Byte_t                                  unk_A0C[0x1D4];             // A0C

    public:
        maybe<Havok_Player_t*>              Havok_Player();
        maybe<Havok_Player_Controller_t*>   Havok_Player_Controller();

        u32                                 Teammate_Count();
        u32                                 Increment_Teammate_Count();
        u32                                 Decrement_Teammate_Count();

    public:
        void Log_Objectives(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Player_t) == 0xBE0);

}

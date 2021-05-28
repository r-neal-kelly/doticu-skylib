/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/atomic_count.h"
#include "doticu_skylib/character.h"
#include "doticu_skylib/dynamic_array.h"
#include "doticu_skylib/enum_quest_objective_state.h"
#include "doticu_skylib/event_dispatcher.h"
#include "doticu_skylib/event_handler.h"
#include "doticu_skylib/forward_list.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/player_objective.h"
#include "doticu_skylib/reference_handle.h"
#include "doticu_skylib/unique.h"
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

    class Relation_Counts_t
    {
    public:
        u16 lover_count;        // 00
        u16 ally_count;         // 02
        u16 confidant_count;    // 04
        u16 friend_count;       // 06

    public:
        Relation_Counts_t(u16 lover_count, u16 ally_count, u16 confidant_count, u16 friend_count) :
            lover_count(lover_count), ally_count(ally_count), confidant_count(confidant_count), friend_count(friend_count)
        {
        }

        Relation_Counts_t& operator =(const Relation_Counts_t& other)
        {
            if (std::addressof(other) != this) {
                this->lover_count = other.lover_count;
                this->ally_count = other.ally_count;
                this->confidant_count = other.confidant_count;
                this->friend_count = other.friend_count;
            }
            return *this;
        }
    };
    STATIC_ASSERT(sizeof(Relation_Counts_t) == 0x8);

    class Player_t :                        // PlayerCharacter
        public Character_t,                 // 000
        public Event_Dispatcher_t<void*>,   // 2B0
        public Event_Dispatcher_t<void**>,  // 308
        public Event_Dispatcher_t<void***>, // 360
        public Event_Handler_t<void****>,   // 3B8
        public Event_Handler_t<void*****>,  // 3C0
        public Event_Handler_t<void******>, // 3C8
        public Event_Handler_t<void*******> // 3D0
    {
    public:
        static some<Player_t*> Self();

    public:
        virtual ~Player_t(); // 0

    public:
        u32                                                 unk_3D8;                    // 3D8
        u32                                                 unk_3DC;                    // 3DC
        Hash_Map_t<maybe<Faction_t*>, Crime_Counts_t>       crime_counts_map;           // 3E0
        Hash_Map_t<maybe<Faction_t*>, Stolen_Counts_t>      stolen_counts_map;          // 410
        Reference_Handle_t                                  unk_440;                    // 440
        u32                                                 unk_444;                    // 444
        Hash_Map_t<maybe<Faction_t*>, Relation_Counts_t>    friend_counts_map;          // 448
        f32_xyz                                             unk_478;                    // 478
        f32_xyz                                             unk_484;                    // 484
        f32_xyz                                             unk_490;                    // 490
        Float_t                                             unk_49C;                    // 49C
        u64                                                 unk_4A0;                    // 4A0
        u64                                                 unk_4A8;                    // 4A8
        Array_t<Perk_And_Rank_t*>                           added_perks;                // 4B0
        Array_t<Perk_t*>                                    perks;                      // 4C8
        Array_t<Perk_t*>                                    standing_stone_perks;       // 4E0
        Array_t<Reference_Handle_t>                         map_markers;                // 4F8
        Array_t<void*>                                      unk_510;                    // 510
        Array_t<void*>                                      unk_528;                    // 528
        Array_t<void*>                                      unk_540;                    // 540
        Array_t<void*>                                      unk_558;                    // 558
        List_t<void*>                                       quest_log;                  // 570
        Array_t<Player_Objective_t>                         objectives;                 // 580
        Hash_Map_t<void*, void*>                            unk_598;                    // 598
        Hash_Map_t<void*, void*>                            unk_5C8;                    // 5C8
        List_t<Reference_Handle_t>                          dropped_references;         // 5F8

        Byte_t                                              unk_608[0xA8];              // 608

        maybe<Package_Dialogue_t*>                          closest_dialogue;           // 6B0
        u32                                                 unk_6B8;                    // 6B8
        u32                                                 unk_6BC;                    // 6BC
        maybe<Package_Dialogue_t*>                          ai_running_dialogue;        // 6C0
        s32                                                 steal_warning_count;        // 6C8
        Float_t                                             steal_warning_timer;        // 6CC
        s32                                                 pickpocket_warning_count;   // 6D0
        Float_t                                             pickpocket_warning_timer;   // 6D4

        Byte_t                                              unk_6D8[0x298];             // 6D8

        s64                                                 total_play_time_updated;    // 970
        s64                                                 total_play_time;            // 978

        Byte_t                                              unk_980[0x88];              // 980

        Atomic_Count_t                                      teammate_count;             // A08

        Byte_t                                              unk_A0C[0x1D4];             // A0C

    public:
        maybe<Havok_Player_t*>              Havok_Player();
        maybe<Havok_Player_Controller_t*>   Havok_Player_Controller();

        u32                                 Teammate_Count();
        u32                                 Increment_Teammate_Count();
        u32                                 Decrement_Teammate_Count();

        maybe<Relation_Counts_t*>           Relation_Counts(some<Faction_t*> faction);

        void                                Iterate_Player_Objectives(Iterator_i<some<Player_Objective_t*>>& iterator, Read_Locker_t& forms_locker);
        void                                Iterate_Player_Objectives(Iterator_i<some<Player_Objective_t*>>& iterator, Read_Write_Lock_t& forms_lock = Game_t::Form_IDs_To_Forms_Lock());

        maybe<Player_Objective_t>           Highest_Displayed_Player_Objective(some<Quest_t*> quest, Read_Locker_t& forms_locker);
        maybe<Player_Objective_t>           Highest_Displayed_Player_Objective(some<Quest_t*> quest, Read_Write_Lock_t& forms_lock = Game_t::Form_IDs_To_Forms_Lock());

        Vector_t<some<Quest_Objective_t*>>  Quest_Objectives(Read_Locker_t& forms_locker);
        void                                Quest_Objectives(Vector_t<some<Quest_Objective_t*>>& results, Read_Locker_t& forms_locker);
        Vector_t<some<Quest_Objective_t*>>  Quest_Objectives(Filter_i<some<Quest_Objective_t*>>& filter, Read_Locker_t& forms_locker);
        void                                Quest_Objectives(Vector_t<some<Quest_Objective_t*>>& results, Filter_i<some<Quest_Objective_t*>>& filter, Read_Locker_t& forms_locker);

    public:
        static void Open_Inventory(maybe<unique<Callback_i<>>> callback);

    public:
        void Log_Objectives(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Player_t) == 0xBE0);

}

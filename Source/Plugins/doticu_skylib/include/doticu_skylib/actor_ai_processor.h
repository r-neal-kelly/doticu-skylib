/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/dynamic_array.h"
#include "doticu_skylib/enum.h"
#include "doticu_skylib/forward_list.h"
#include "doticu_skylib/maybe.h"

#include "doticu_skylib/enum_crime_type.h"

#include "doticu_skylib/actor_handle.h"
#include "doticu_skylib/reference_handle.h"

namespace doticu_skylib {

    class Actor_t;
    class NI_Temp_Effect_t;
    class Sync_Object_t;

    class Actor_AI_Processor_t // ProcessLists
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                SELF                    = 0x01EBEAD0, // 514167
                STOP_COMBAT_AND_ALARM   = 0x006D9490, // 40330
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Actor_AI_Processor_t*> Self();

    public:
        u8                                  pad_000;                                // 000
        Bool_t                              run_detection;                          // 001
        Bool_t                              show_detection;                         // 002
        u8                                  pad_003;                                // 003
        Actor_Handle_t                      dectector;                              // 004
        Bool_t                              do_high_process;                        // 008
        Bool_t                              do_low_process;                         // 009
        Bool_t                              do_middle_high_process;                 // 00A
        Bool_t                              do_middle_low_process;                  // 00B
        u16                                 unk_00C;                                // 00C
        u8                                  unk_00E;                                // 00E
        u8                                  pad_00F;                                // 00F
        s32                                 high_actor_count;                       // 010
        Float_t                             unk_014;                                // 014
        u32                                 unk_018;                                // 018
        Float_t                             remove_excess_dead_timer;               // 01C
        u64                                 unk_020;                                // 020
        u32                                 unk_028;                                // 028
        u32                                 pad_02C;                                // 02C
        Array_t<Actor_Handle_t>             high_actor_handles;                     // 030
        Array_t<Actor_Handle_t>             low_actor_handles;                      // 048
        Array_t<Actor_Handle_t>             middle_high_actor_handles;              // 060
        Array_t<Actor_Handle_t>             middle_low_actor_handles;               // 078
        maybe<Array_t<Actor_Handle_t>*>     all_processes[4];                       // 090
        maybe<Forward_List_t<void*>*>       global_crimes[Crime_Type_e::_TOTAL_];   // 0B0
        Array_t<maybe<NI_Temp_Effect_t*>>   global_temp_effects;                    // 0E8
        u64                                 global_temp_effects_lock;               // 100
        Array_t<maybe<NI_Temp_Effect_t*>>   magic_temp_effects;                     // 108
        u64                                 magic_temp_effects_lock;                // 120
        Array_t<maybe<NI_Temp_Effect_t*>>   interface_temp_effects;                 // 128
        u64                                 interface_temp_effects_lock;            // 140
        u64                                 unk_148;                                // 148
        u64                                 unk_150;                                // 150
        Array_t<Reference_Handle_t>         should_move_references;                 // 158
        Forward_List_t<Actor_Handle_t>      unk_170;                                // 170
        Array_t<Actor_Handle_t>             init_package_locations_queue;           // 180
        u64                                 init_package_locations_queue_lock;      // 198
        Array_t<Actor_Handle_t>             init_animation_position_queue;          // 1A0
        Array_t<Sync_Object_t*>             sync_objects;                           // 1B8
        Float_t                             comment_player_actor_timer;             // 1D0
        Float_t                             comment_player_knock_object_timer;      // 1D4
        u32                                 current_low_actor;                      // 1D8
        u32                                 current_middle_high_actor;              // 1DC
        u32                                 current_middle_low_actor;               // 1E0
        Bool_t                              do_run_schedules;                       // 1E4
        Bool_t                              do_run_movement;                        // 1E5
        Bool_t                              do_run_animations;                      // 1E6
        Bool_t                              do_update_actors_in_player_cell;        // 1E7
        u64                                 unk_1E8;                                // 1E8

    public:
        void Stop_Combat_And_Alarm(some<Actor_t*> actor, Bool_t stop_combat_only);
    };
    STATIC_ASSERT(sizeof(Actor_AI_Processor_t) == 0x1F0);

}

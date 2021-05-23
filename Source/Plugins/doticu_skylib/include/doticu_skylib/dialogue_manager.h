/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/dynamic_array.h"
#include "doticu_skylib/enum.h"
#include "doticu_skylib/event_handler.h"
#include "doticu_skylib/forward_list.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/reference_handle.h"
#include "doticu_skylib/unknown.h"

namespace doticu_skylib {

    class Dialogue_Branch_t;
    class Dialogue_Info_t;
    class Dialogue_Topic_t;
    class Dialogue_Topic_Instance_t;
    class Reference_t;

    class Dialogue_Manager_t :          // MenuTopicManager
        public Event_Handler_t<void*>,  // 00
        public Event_Handler_t<void**>  // 08
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E3A7F0, // 686590
                SELF = 0x02EFF988, // 514959
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Dialogue_Manager_t*> Self();

    public:
        virtual ~Dialogue_Manager_t(); // 0

    public:
        u64                                                 pad_10;                         // 10
        maybe<List_t<maybe<Dialogue_Topic_Instance_t*>>*>   unk_18;                         // 18
        maybe<List_t<maybe<Dialogue_Topic_Instance_t*>>*>   unk_20;                         // 20
        u64                                                 unk_28;                         // 28
        maybe<Dialogue_Info_t*>                             root_info;                      // 30
        maybe<Dialogue_Topic_Instance_t*>                   last_selected_topic_instance;   // 38
        CRITICAL_SECTION                                    critical_section;               // 40
        Reference_Handle_t                                  current_speaker;                // 68
        Reference_Handle_t                                  finishing_speaker;              // 6C
        maybe<Dialogue_Info_t*>                             current_info;                   // 70
        maybe<Dialogue_Info_t*>                             finishing_info;                 // 78
        Array_t<maybe<Dialogue_Branch_t*>>                  blocking_branches;              // 80
        Array_t<maybe<Dialogue_Branch_t*>>                  top_level_branches;             // 98
        Bool_t                                              is_saying_hello;                // B0
        Bool_t                                              unk_B1;                         // B1
        Bool_t                                              is_saying_goodbye;              // B2
        Bool_t                                              unk_B3;                         // B3
        Bool_t                                              unk_B4;                         // B4
        Bool_t                                              unk_B5;                         // B5
        Bool_t                                              unk_B6;                         // B6
        Bool_t                                              unk_B7;                         // B7
        Bool_t                                              unk_B8;                         // B8
        Bool_t                                              unk_B9;                         // B9
        Bool_t                                              unk_BA;                         // BA
        Bool_t                                              unk_BB;                         // BB
        u32                                                 pad_BC;                         // BC
        Array_t<Dialogue_Topic_t*>                          topics;                         // C0

    public:
        maybe<Reference_t*>     Current_Speaker();
        maybe<Dialogue_Info_t*> Current_Dialogue_Info();
    };
    STATIC_ASSERT(sizeof(Dialogue_Manager_t) == 0xD8);

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/forward_list.h"
#include "doticu_skylib/string.h"

#include "doticu_skylib/atomic_count.h"

namespace doticu_skylib {

    class Actor_t;
    class Dialogue_Info_t;
    class Dialogue_Response_Instance_t;
    class Dialogue_Topic_t;
    class Quest_t;
    class Reference_t;

    class Dialogue_Info_Instance_t :    // DialogueItem
        public Atomic_Count_t           // 00
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                CTOR = 0x0056C9D0, // 34413
            };
            using Enum_t::Enum_t;
        };

    public:
        u32                                                     pad_04;                     // 04
        Forward_List_t<Dialogue_Response_Instance_t*>           response_instances;         // 08
        Forward_List_t<Dialogue_Response_Instance_t*>::Node_t*  current_response_instance;  // 18
        Dialogue_Info_t*                                        info;                       // 20
        Dialogue_Topic_t*                                       topic;                      // 28
        Quest_t*                                                quest;                      // 30
        Reference_t*                                            speaker;                    // 38 (Actor_t*?)
        void*                                                   extra_topic;                // 40

    public:
        Dialogue_Info_Instance_t(some<Quest_t*> quest,
                                 some<Dialogue_Topic_t*> topic,
                                 some<Dialogue_Info_t*> info,
                                 maybe<Actor_t*> speaker);
    };
    STATIC_ASSERT(sizeof(Dialogue_Info_Instance_t) == 0x48);

}

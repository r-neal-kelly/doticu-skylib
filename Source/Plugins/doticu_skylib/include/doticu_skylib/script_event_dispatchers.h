/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/event_dispatcher.h"
#include "doticu_skylib/event_quest_stage.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Script_Event_Dispatchers_t
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                SELF = 0x00186790, // 14108
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        static some<Script_Event_Dispatchers_t*>        Self();

        static Event_Dispatcher_t<Event_Quest_Stage_t>& Quest_Stage();

    public:
        Event_Dispatcher_t<void*>   dispatchers[54];    // 0000
    };
    STATIC_ASSERT(sizeof(Script_Event_Dispatchers_t) == 0x1290);

}

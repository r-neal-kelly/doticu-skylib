/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/game.h"
#include "doticu_skylib/script_event_dispatchers.h"

namespace doticu_skylib {

    some<Script_Event_Dispatchers_t*> Script_Event_Dispatchers_t::Self()
    {
        static auto get_self = reinterpret_cast
            <Script_Event_Dispatchers_t*(*)()>
            (Game_t::Base_Address() + Offset_e::SELF);

        return get_self();
    }

    Event_Dispatcher_t<Event_Quest_Stage_t>& Script_Event_Dispatchers_t::Quest_Stage()
    {
        return *reinterpret_cast<Event_Dispatcher_t<Event_Quest_Stage_t>*>(&Self()->dispatchers[30]);
    }

}

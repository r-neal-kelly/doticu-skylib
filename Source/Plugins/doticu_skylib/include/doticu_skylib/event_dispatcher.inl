/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/event_dispatcher.h"
#include "doticu_skylib/game.h"

namespace doticu_skylib {

    template <typename Event_t>
    inline void Event_Dispatcher_t<Event_t>::Add_Handler(some<Handler_t*> handler)
    {
        static auto add_handler = reinterpret_cast
            <void(*)(Event_Dispatcher_t<Event_t>*, Handler_t*)>
            (Game_t::Base_Address() + Offset_e::ADD_HANDLER);

        SKYLIB_ASSERT_SOME(handler);

        add_handler(this, handler());
    }

    template <typename Event_t>
    inline void Event_Dispatcher_t<Event_t>::Remove_Handler(some<Handler_t*> handler)
    {
        static auto remove_handler = reinterpret_cast
            <void(*)(Event_Dispatcher_t<Event_t>*, Handler_t*)>
            (Game_t::Base_Address() + Offset_e::REMOVE_HANDLER);

        SKYLIB_ASSERT_SOME(handler);

        remove_handler(this, handler());
    }

    template <typename Event_t>
    inline void Event_Dispatcher_t<Event_t>::Dispatch_Event(some<Event_t*> event)
    {
        static auto dispatch_event = reinterpret_cast
            <void(*)(Event_Dispatcher_t<Event_t>*, Event_t*)>
            (Game_t::Base_Address() + Offset_e::DISPATCH_EVENT);

        SKYLIB_ASSERT_SOME(event);

        dispatch_event(this, event());
    }

}

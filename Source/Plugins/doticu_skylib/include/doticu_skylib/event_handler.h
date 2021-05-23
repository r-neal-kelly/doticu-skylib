/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_iterator.h"
#include "doticu_skylib/event_dispatcher.h"
#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    template <typename T>
    class Event_Handler_t   // BSTEventSink
    {
    public:
        using Event_t = T;
        using Dispatcher_t = Event_Dispatcher_t<Event_t>;

    public:
        virtual                         ~Event_Handler_t()                                          = default;  // 0
        virtual Iterator_e::value_type  On_Event(const Event_t& event, Dispatcher_t& dispatcher)    = 0;        // 1
    };
    STATIC_ASSERT(sizeof(Event_Handler_t<void*>) == 0x8);

}

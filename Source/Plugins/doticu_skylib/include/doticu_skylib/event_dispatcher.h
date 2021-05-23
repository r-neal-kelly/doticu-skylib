/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/dynamic_array.h"
#include "doticu_skylib/enum.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/spin_lock.h"

namespace doticu_skylib {

    template <typename T>
    class Event_Handler_t;

    template <typename T>
    class Event_Dispatcher_t    // BSTEventSource, EventDispatcher
    {
    public:
        using Event_t = T;
        using Handler_t = Event_Handler_t<Event_t>;

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                ADD_HANDLER     = 0x0056B600, // 34381
                REMOVE_HANDLER  = 0x00423B70, // 28367
                DISPATCH_EVENT  = 0x00177DC0, // 13805
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        Array_t<maybe<Handler_t*>>  handlers;               // 00
        Array_t<maybe<Handler_t*>>  handlers_to_register;   // 18
        Array_t<maybe<Handler_t*>>  handlers_to_unregister; // 30
        mutable Spin_Lock_t         spin_lock;              // 48
        Bool_t                      is_dispatching;         // 50
        u8                          pad_51;                 // 51
        u16                         pad_52;                 // 52
        u32                         pad_54;                 // 54

    public:
        void Add_Handler(some<Handler_t*> handler);
        void Remove_Handler(some<Handler_t*> handler);
        void Dispatch_Event(some<Event_t*> event);
    };
    STATIC_ASSERT(sizeof(Event_Dispatcher_t<void*>) == 0x58);

}

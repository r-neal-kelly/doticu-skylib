/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

namespace doticu_skylib {

    class Animation_Updater_i
    {
    public:
        virtual ~Animation_Updater_i();
    };
    STATIC_ASSERT(sizeof(Animation_Updater_i) == 0x8);

    class Animation_Graphs_t
    {
    public:
        virtual ~Animation_Graphs_t();
    };
    STATIC_ASSERT(sizeof(Animation_Graphs_t) == 0x8);

    template <typename Type_t>
    class Event_Source_t
    {
        Byte_t unk_data[0x58];
    };
    STATIC_ASSERT(sizeof(Event_Source_t<Int_t>) == 0x58);

    template <typename Event>
    class Event_Sink_t
    {
        virtual ~Event_Sink_t();
    };
    STATIC_ASSERT(sizeof(Event_Sink_t<void*>) == 0x8);

}

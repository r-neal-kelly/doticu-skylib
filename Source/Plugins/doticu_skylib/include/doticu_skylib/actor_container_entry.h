/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/container_entry_count.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Bound_Object_t;
    class Container_Entry_t;
    class Container_Changes_Entry_t;

    class Actor_Container_Entry_t
    {
    public:
        maybe<Container_Entry_t*>           base_entry;
        maybe<Container_Changes_Entry_t*>   reference_entry;

    public:
        Actor_Container_Entry_t(maybe<Container_Entry_t*> base_entry, maybe<Container_Changes_Entry_t*> reference_entry);
        Actor_Container_Entry_t(const Actor_Container_Entry_t& other);
        Actor_Container_Entry_t(Actor_Container_Entry_t&& other) noexcept;
        Actor_Container_Entry_t& operator =(const Actor_Container_Entry_t& other);
        Actor_Container_Entry_t& operator =(Actor_Container_Entry_t&& other) noexcept;
        ~Actor_Container_Entry_t();

    public:
        some<Bound_Object_t*>   Object();
        Container_Entry_Count_t Base_Count();
        Container_Entry_Count_t Count();

    public:
        void Log(std::string indent = "");
    };

}

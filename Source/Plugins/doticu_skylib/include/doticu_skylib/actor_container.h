/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/actor_container_entry.h"
#include "doticu_skylib/collections.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    // this needs to be renamed to Reference_Container_t and Reference_Container_Entry_t.
    // we need to limit usage to references that have Container_c on their base_forms. (e.g. Actor_t Container_t)
    // we may want to rename Container_Entry_t to Component_Container_Entry_t a,d Container_c to Component_Container_t
    // maybe put a method on Reference that tries to get the component container and if it doesn't have it, not big deal, we just don't use it.

    class Actor_t;
    class Bound_Object_t;
    class Container_c;
    class Container_Changes_t;
    class Container_Changes_Entry_t;

    class Actor_Container_t
    {
    public:
        some<Actor_t*>                      actor;
        some<Container_Changes_t*>          reference_container;
        Vector_t<Actor_Container_Entry_t>   entries;

    public:
        Actor_Container_t(some<Actor_t*> actor);
        Actor_Container_t(const Actor_Container_t& other)                   = delete;
        Actor_Container_t(Actor_Container_t&& other) noexcept               = delete;
        Actor_Container_t& operator =(const Actor_Container_t& other)       = delete;
        Actor_Container_t& operator =(Actor_Container_t&& other) noexcept   = delete;
        ~Actor_Container_t();

    public:
        maybe<Actor_Container_Entry_t*> Maybe_Entry(some<Bound_Object_t*> object);
        some<Actor_Container_Entry_t*>  Some_Entry(some<Bound_Object_t*> object);

        Container_Entry_Count_t         Count(some<Bound_Object_t*> object);

        Container_Entry_Count_t         Increment_Count(some<Bound_Object_t*> object, Container_Entry_Count_t amount);
        Container_Entry_Count_t         Decrement_Count(some<Bound_Object_t*> object, Container_Entry_Count_t amount);

    public:
        void Log(std::string indent = "");
    };

}

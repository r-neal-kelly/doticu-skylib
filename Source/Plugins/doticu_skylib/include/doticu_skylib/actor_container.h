/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/actor_container_entry.h"
#include "doticu_skylib/collections.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Actor_t;
    class Container_c;
    class Container_Changes_t;

    class Actor_Container_t
    {
    public:
        some<Actor_t*>                      owner;
        maybe<Container_c*>                 base_container;
        maybe<Container_Changes_t*>         reference_container;
        Vector_t<Actor_Container_Entry_t>   entries;

    public:
        Actor_Container_t(some<Actor_t*> actor);
        Actor_Container_t(const Actor_Container_t& other)                   = delete;
        Actor_Container_t(Actor_Container_t&& other) noexcept               = delete;
        Actor_Container_t& operator =(const Actor_Container_t& other)       = delete;
        Actor_Container_t& operator =(Actor_Container_t&& other) noexcept   = delete;
        ~Actor_Container_t();

    public:
        void Log(std::string indent = "");
    };

}

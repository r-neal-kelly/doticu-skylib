/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/actor_handle.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Active_Magic_Effect_t;
    class Magic_Base_t;

    class Dispelled_Magic_t // SpellDispelData
    {
    public:
        maybe<Magic_Base_t*>            magic_base;             // 00
        Actor_Handle_t                  actor_handle;           // 08
        u32                             pad_0C;                 // 0C
        maybe<Active_Magic_Effect_t*>   active_magic_effect;    // 10
        maybe<Dispelled_Magic_t*>       next;                   // 18

    public:
        void    Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Dispelled_Magic_t) == 0x20);

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/actor_ai_cached_value.h"
#include "doticu_skylib/dynamic_array.h"
#include "doticu_skylib/enum_actor_ai_cached_values_flags.h"
#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Actor_AI_Cached_Values_t // CachedValues
    {
    public:
        Float_t                             radius;                     // 00
        Float_t                             width;                      // 04
        Float_t                             length;                     // 08
        Float_t                             forward_length;             // 0C
        Float_t                             damage_per_second;          // 10
        Float_t                             eye_level;                  // 14
        Float_t                             walk_speed;                 // 18
        Float_t                             run_speed;                  // 1C
        Float_t                             jog_speed;                  // 20
        Float_t                             fast_walk_speed;            // 24
        Actor_AI_Cached_Values_Flags_1_e    cached_values_flags_1;      // 28
        Actor_AI_Cached_Values_Flags_2_e    cached_values_flags_2;      // 2C
        Array_t<Actor_AI_Cached_Value_t>    temporary_cached_values;    // 30
        Array_t<Actor_AI_Cached_Value_t>    permanent_cached_values;    // 48

    public:
        Bool_t  Is_Ghost();
        void    Is_Ghost(Bool_t value);
    };
    STATIC_ASSERT(sizeof(Actor_AI_Cached_Values_t) == 0x60);

}

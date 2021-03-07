/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/actor_handle.h"
#include "doticu_skylib/dynamic_array.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/reference_handle.h"

namespace doticu_skylib {

    class Actor_High_AI_t // HighProcessData
    {
    public:
        Byte_t                  data_000[0x02C];            // 000
        u32                     unk_02C;                    // 02C
        Array_t<Actor_Handle_t> last_actors_spoken_to;      // 030
        Byte_t                  data_048[0x130];            // 048
        Reference_Handle_t      last_target;                // 178
        Reference_Handle_t      look_target;                // 17C
        Byte_t                  data_180[0x174];            // 180
        Reference_Handle_t      currently_greeted_target;   // 2F4
        Byte_t                  data_2F8[0x180];            // 2F8
    };
    STATIC_ASSERT(sizeof(Actor_High_AI_t) == 0x478);

}

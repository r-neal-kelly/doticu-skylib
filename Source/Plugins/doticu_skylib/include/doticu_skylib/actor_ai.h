/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_update_3d_flags.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Actor_t;
    class Actor_AI_Cached_Values_t;
    class Actor_High_AI_t;
    class Actor_Middle_Low_AI_t;
    class Actor_Middle_High_AI_t;

    class Actor_AI_t // ActorProcessManager, AIProcess
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                UPDATE_3D = 0x00650DF0, // 38404
            };
            using Enum_t::Enum_t;
        };

    public:
        maybe<Actor_Middle_Low_AI_t*>       middle_low_ai;  // 000
        maybe<Actor_Middle_High_AI_t*>      middle_high_ai; // 008
        maybe<Actor_High_AI_t*>             high_ai;        // 010
        Byte_t                              unk_018[0x30];  // 018
        Float_t                             unk_048;        // 048
        u32                                 unk_04C;        // 04C
        maybe<Actor_AI_Cached_Values_t*>    cached_values;  // 050
        Byte_t                              unk_data[0xE8]; // 058

    public:
        void Flag_Update_3D(Update_3D_Flags_e flag);
        void Unflag_Update_3D(Update_3D_Flags_e flag);
        void Update_3D(some<Actor_t*> owning_actor);
    };
    STATIC_ASSERT(sizeof(Actor_AI_t) == 0x140);

}

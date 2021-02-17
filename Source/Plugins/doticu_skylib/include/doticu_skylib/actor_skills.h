/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_actor_skill.h"

namespace doticu_skylib {

    class Actor_Skills_t
    {
    public:
        u8      values[Actor_Skill_e::_TOTAL_];     // 00
        u8      offsets[Actor_Skill_e::_TOTAL_];    // 12
        u16     health;                             // 24
        u16     magicka;                            // 26
        u16     stamina;                            // 28
        u16     pad_2A;                             // 2A
        Float_t unk_2C;                             // 2C
    };
    STATIC_ASSERT(sizeof(Actor_Skills_t) == 0x30);

}

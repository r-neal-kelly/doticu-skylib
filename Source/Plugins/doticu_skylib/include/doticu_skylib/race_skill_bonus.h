/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_actor_skill.h"

namespace doticu_skylib {

    class Race_Skill_Bonus_t // SkillBoost
    {
    public:
        Actor_Skill_e   skill; // 0
        u8              bonus; // 1
    };
    STATIC_ASSERT(sizeof(Race_Skill_Bonus_t) == 0x2);

}

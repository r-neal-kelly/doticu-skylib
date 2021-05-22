/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_quest_objective_state.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/string.h"

namespace doticu_skylib {

    class Quest_Objective_t;

    class Player_Objective_t
    {
    public:
        static String_t Parse_Display_Text(some<Quest_Objective_t*> objective, u32 instance_id);

    public:
        maybe<Quest_Objective_t*>   objective;      // 0
        u32                         instance_id;    // 8
        Quest_Objective_State_e     state;          // C
        u8                          pad_D;          // D
        u16                         pad_E;          // E

    public:
        Player_Objective_t();
        Player_Objective_t(some<Quest_Objective_t*> objective, u32 instance_id);
        Player_Objective_t(const Player_Objective_t& other);
        Player_Objective_t(Player_Objective_t&& other) noexcept;
        Player_Objective_t& operator =(const Player_Objective_t& other);
        Player_Objective_t& operator =(Player_Objective_t&& other) noexcept;
        ~Player_Objective_t();

    public:
        String_t    Parse_Display_Text();

    public:
        friend Bool_t operator ==(const Player_Objective_t& a, const Player_Objective_t& b);
        friend Bool_t operator !=(const Player_Objective_t& a, const Player_Objective_t& b);

    public:
        void    Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Player_Objective_t) == 0x10);

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/enum_quest_objective_flags.h"
#include "doticu_skylib/enum_quest_objective_state.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/quest_objective_index.h"
#include "doticu_skylib/string.h"

namespace doticu_skylib {

    class Quest_t;
    class Quest_Target_t;

    class Quest_Objective_t
    {
    public:
        String_t                        display_text;           // 00
        maybe<Quest_t*>                 quest;                  // 08
        maybe<maybe<Quest_Target_t*>*>  targets;                // 10
        u32                             target_count;           // 18
        Quest_Objective_Index_t         index;                  // 1C
        Bool_t                          is_initialized;         // 1E
        Quest_Objective_State_e         state;                  // 1F
        Quest_Objective_Flags_e         quest_objective_flags;  // 20
        u32                             pad_24;                 // 24

    public:
        Bool_t  Is_Displayed() const;

    public:
        void    Log(std::string indent = "") const;
    };
    STATIC_ASSERT(sizeof(Quest_Objective_t) == 0x28);

}

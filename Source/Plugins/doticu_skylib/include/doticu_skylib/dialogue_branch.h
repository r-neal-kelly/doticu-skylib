/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_dialogue_branch_flags.h"
#include "doticu_skylib/enum_dialogue_branch_type.h"

#include "doticu_skylib/form.h"
#include "doticu_skylib/enum_script_type.h"

namespace doticu_skylib {

    class Dialogue_Topic_t;
    class Quest_t;

    class Dialogue_Branch_t : public Form_t // BGSDialogueBranch
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::DIALOGUE_BRANCH,
        };

    public:
        virtual ~Dialogue_Branch_t(); // 0

    public:
        Dialogue_Branch_Flags_e branch_flags;   // 20
        u32                     pad_24;         // 24
        Quest_t*                quest;          // 28
        Dialogue_Topic_t*       starting_topic; // 30
        Dialogue_Branch_Type_e  branch_type;    // 38
        u8                      pad_39;         // 39
        u16                     pad_3A;         // 3A
        u32                     pad_3C;         // 3C
    };
    STATIC_ASSERT(sizeof(Dialogue_Branch_t) == 0x40);

}

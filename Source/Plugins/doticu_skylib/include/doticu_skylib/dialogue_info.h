/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_dialogue_info_flags.h"
#include "doticu_skylib/enum_favor_level.h"

#include "doticu_skylib/form.h"
#include "doticu_skylib/enum_script_type.h"

namespace doticu_skylib {

    class Dialogue_Branch_t;
    class Dialogue_Topic_t;
    class Quest_t;

    class Dialogue_Info_t : public Form_t // TESTopicInfo
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::DIALOGUE_INFO,
        };

    public:
        virtual ~Dialogue_Info_t(); // 0

    public:
        Dialogue_Topic_t*       topic;              // 20
        Dialogue_Info_t*        shared_info;        // 28 (could this be previous info?)
        void*                   conditions;         // 30
        u16                     info_index;         // 38
        Bool_t                  has_been_said;      // 3A
        Favor_Level_e           favor_level;        // 3B
        Dialogue_Info_Flags_e   info_flags;         // 3C
        u16                     reset_hours;        // 3E
        u32                     first_mod_offset;   // 40
        u32                     pad_44;             // 44

    public:
        Bool_t Is_In_Branch(some<Dialogue_Branch_t*> branch);
        Bool_t Is_In_Quest(some<Quest_t*> quest);
        Bool_t Is_In_Topic(some<Dialogue_Topic_t*> topic);

        maybe<Dialogue_Branch_t*>   Branch();
        maybe<Quest_t*>             Quest();
        maybe<Dialogue_Topic_t*>    Topic();
    };
    STATIC_ASSERT(sizeof(Dialogue_Info_t) == 0x48);

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/string.h"

#include "doticu_skylib/enum_dialogue_topic_flags.h"
#include "doticu_skylib/enum_dialogue_topic_subtype.h"
#include "doticu_skylib/enum_dialogue_topic_type.h"

#include "doticu_skylib/component_name.h"

#include "doticu_skylib/form.h"
#include "doticu_skylib/enum_script_type.h"

namespace doticu_skylib {

    class Dialogue_Branch_t;
    class Dialogue_Info_t;
    class Quest_t;

    class Dialogue_Topic_t :    // TESTopic
        public Form_t,          // 00
        public Name_c           // 20
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::DIALOGUE_TOPIC,
        };

    public:
        virtual ~Dialogue_Topic_t(); // 0

    public:
        Dialogue_Topic_Flags_e      topic_flags;        // 30
        Dialogue_Topic_Type_e       topic_type;         // 31
        Dialogue_Topic_Subtype_e    topic_subtype;      // 32
        u32                         priority;           // 34 (PNAM)
        Dialogue_Branch_t*          branch;             // 38
        Quest_t*                    quest;              // 40
        Dialogue_Info_t**           infos;              // 48
        u32                         info_count;         // 50
        u32                         first_mod_offset;   // 54
        String_t                    editor_id;          // 58
    };
    STATIC_ASSERT(sizeof(Dialogue_Topic_t) == 0x60);

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_relation.h" // should be enum_relation_type.h"
#include "doticu_skylib/enum_relation_flags.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Actor_Base_t;
    class Association_t;

    class Relation_t :  // BGSRelationship
        public Form_t   // 00
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::RELATION,
        };

        //static constexpr const char* SCRIPT_NAME = "";

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E1F0E8, // 685399
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        maybe<Actor_Base_t*>    parent;         // 20
        maybe<Actor_Base_t*>    child;          // 28
        maybe<Association_t*>   association;    // 30
        maybe<Relation_e>       relation_type;  // 38
        u8                      unk_39;         // 39
        u8                      unk_3A;         // 3A
        Relation_Flags_e        relation_flags; // 3B
        u32                     pad_3C;         // 3C

    public:
        maybe<String_t> Association_String(some<Actor_Base_t*> actor_base) const;
    };
    STATIC_ASSERT(sizeof(Relation_t) == 0x40);

}

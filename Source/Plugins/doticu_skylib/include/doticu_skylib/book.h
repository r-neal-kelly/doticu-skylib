/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/bound_object.h"
#include "doticu_skylib/component_description.h"
#include "doticu_skylib/component_destructible.h"
#include "doticu_skylib/component_grab_sounds.h"
#include "doticu_skylib/component_icon.h"
#include "doticu_skylib/component_keywords.h"
#include "doticu_skylib/component_message_icon.h"
#include "doticu_skylib/component_model_alternates.h"
#include "doticu_skylib/component_name.h"
#include "doticu_skylib/component_value.h"
#include "doticu_skylib/component_weight.h"
#include "doticu_skylib/enum_actor_value_type.h"
#include "doticu_skylib/enum_book_flags.h"
#include "doticu_skylib/enum_book_type.h"
#include "doticu_skylib/enum_script_type.h"

namespace doticu_skylib {

    class Spell_t;
    class Static_t;

    class Book_t :                  // TESObjectBOOK
        public Bound_Object_t,      // 000
        public Name_c,              // 030
        public Model_Alternates_c,  // 040
        public Icon_c,              // 078
        public Value_c,             // 088
        public Weight_c,            // 098
        public Description_c,       // 0A8
        public Destructible_c,      // 0B8
        public Message_Icon_c,      // 0C8
        public Grab_Sounds_c,       // 0E0
        public Keywords_c           // 0F8
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::BOOK,
        };

        static constexpr const char* SCRIPT_NAME = "Book";

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E191B8, // 513977
            };

        public:
            using Enum_t::Enum_t;
        };

        union Teachable_u
        {
        public:
            Actor_Value_Type_e  skill;
            maybe<Spell_t*>     spell;

        public:
            Teachable_u();
            ~Teachable_u();
        };

    public:
        virtual ~Book_t(); // 0

    public:
        Book_Flags_e        book_flags;             // 110
        Book_Type_e         book_type;              // 111
        u16                 pad_112;                // 112
        u32                 pad_114;                // 114
        Teachable_u         teachable;              // 118
        maybe<Static_t*>    inventory_model;        // 120 (INAM)
        Description_c       inventory_description;  // 128 (CNAM)

    public:
        Bool_t      Can_Take() const;
        Bool_t      Cant_Take() const;
        Bool_t      Can_Teach_Skill() const;
        Bool_t      Can_Teach_Spell() const;

        Bool_t      Has_Been_Read() const;
        Bool_t      Hasnt_Been_Read() const;

        Bool_t      Is_Skill_Book() const;
        Bool_t      Is_Spell_Tome() const;
        Bool_t      Is_Recipe() const;

        DString_t   Unparsed_Text() const;

    public:
        void Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Book_t) == 0x138);

}

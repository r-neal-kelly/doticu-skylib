/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Form_t;

    class Relation_e : public Enum_t<s8>
    {
    public:
        enum : value_type
        {
            NONE            = -1,
            LOVER           = 0,
            ALLY            = 1,
            CONFIDANT       = 2,
            FRIEND          = 3,
            ACQUAINTANCE    = 4,
            RIVAL           = 5,
            FOE             = 6,
            ENEMY           = 7,
            ARCHNEMESIS     = 8,

            _END_,
        };

        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum
            {
                GET = 0x00345ED0, // 23624
                SET = 0x00345B80, // 23623
            };
        };

        static constexpr const char* NONE_STRING            = "None";
        static constexpr const char* LOVER_STRING           = "Lover";
        static constexpr const char* ALLY_STRING            = "Ally";
        static constexpr const char* CONFIDANT_STRING       = "Confidant";
        static constexpr const char* FRIEND_STRING          = "Friend";
        static constexpr const char* ACQUAINTANCE_STRING    = "Acquaintance";
        static constexpr const char* RIVAL_STRING           = "Rival";
        static constexpr const char* FOE_STRING             = "Foe";
        static constexpr const char* ENEMY_STRING           = "Enemy";
        static constexpr const char* ARCHNEMESIS_STRING     = "Archnemesis";

    public:
        using Enum_t::Enum_t;

        static Relation_e           Between(Form_t* form_a, Form_t* form_b);
        static void                 Between(Form_t* form_a, Form_t* form_b, Relation_e relation);
        static some<const char*>    To_String(Relation_e relation);
        static Relation_e           From_String(maybe<const char*> relation);
    };

}

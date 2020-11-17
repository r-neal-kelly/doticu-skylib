/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Form_t;

    class Relation_e : public Enum_t<s8>
    {
    public:
        enum
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

        static Relation_e   Between(Form_t* form_a, Form_t* form_b);
        static void         Between(Form_t* form_a, Form_t* form_b, Relation_e relation);

    public:
        using Enum_t::Enum_t;
    };

}

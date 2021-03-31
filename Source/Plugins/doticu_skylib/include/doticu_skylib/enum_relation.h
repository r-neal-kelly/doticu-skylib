/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_type.h"

namespace doticu_skylib {

    class Form_t;

    class Relation_e_data :
        public Enum_Type_Data_t<s8>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_          = -1,

            LOVER           = 0,
            ALLY            = 1,
            CONFIDANT       = 2,
            FRIEND          = 3,
            ACQUAINTANCE    = 4,
            RIVAL           = 5,
            FOE             = 6,
            ENEMY           = 7,
            ARCHNEMESIS     = 8,

            _TOTAL_         = 9,
            _DEFAULT_       = ACQUAINTANCE,
        };

    public:
        static Bool_t                   Is_Valid(value_type value);

        static some<const char* const*> Strings();
        static some<const char*>        To_String(value_type value);
        static value_type               From_String(maybe<const char*> string);
    };

    class Relation_e :
        public Enum_Type_t<Relation_e_data>
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                GET = 0x00345ED0, // 23624
                SET = 0x00345B80, // 23623
            };
        };

    public:
        static some<Relation_e> Between(some<Form_t*> form_a, some<Form_t*> form_b);
        static void             Between(some<Form_t*> form_a, some<Form_t*> form_b, some<Relation_e> relation);

    public:
        using Enum_Type_t::Enum_Type_t;
    };

    template <>
    class none<Relation_e> :
        public none_enum<Relation_e>
    {
    public:
        using none_enum::none_enum;
    };

    template <>
    class maybe<Relation_e> :
        public maybe_enum<Relation_e>
    {
    public:
        using maybe_enum::maybe_enum;
    };

    template <>
    class some<Relation_e> :
        public some_enum<Relation_e>
    {
    public:
        using some_enum::some_enum;
    };

}

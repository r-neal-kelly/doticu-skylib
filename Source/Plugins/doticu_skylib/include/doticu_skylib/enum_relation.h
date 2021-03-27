/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/maybe_enum.h"

namespace doticu_skylib {

    class Form_t;

    class Relation_e :
        public Enum_t<s8>
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
        static Bool_t                   Is_Valid(enum_type value);
        static Bool_t                   Is_Valid(value_type value);

        static some<const char* const*> Strings();
        static some<const char*>        To_String(maybe<Relation_e> relation);
        static maybe<Relation_e>        From_String(maybe<const char*> relation);

        static some<Relation_e>         Between(some<Form_t*> form_a, some<Form_t*> form_b);
        static void                     Between(some<Form_t*> form_a, some<Form_t*> form_b, some<Relation_e> relation);

    public:
        Relation_e();
        Relation_e(enum_type value);
        Relation_e(value_type value);
        Relation_e(const Relation_e& other);
        Relation_e(Relation_e&& other) noexcept;
        Relation_e& operator =(const Relation_e& other);
        Relation_e& operator =(Relation_e&& other) noexcept;
        ~Relation_e();

    public:
        some<const char*>   As_String() const;

    public:
        explicit operator   Bool_t() const;
        operator            value_type() const;

    public:
        Bool_t      operator !() const;
        value_type  operator ()() const;
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

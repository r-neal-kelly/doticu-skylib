/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/maybe_numeric.h"

namespace doticu_skylib {

    class Form_t;

    class Relation_e :
        public Enum_t<u8>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_          = static_cast<value_type>(-1),

            LOVER           = static_cast<value_type>(0),
            ALLY            = static_cast<value_type>(1),
            CONFIDANT       = static_cast<value_type>(2),
            FRIEND          = static_cast<value_type>(3),
            ACQUAINTANCE    = static_cast<value_type>(4),
            RIVAL           = static_cast<value_type>(5),
            FOE             = static_cast<value_type>(6),
            ENEMY           = static_cast<value_type>(7),
            ARCHNEMESIS     = static_cast<value_type>(8),

            _TOTAL_         = static_cast<value_type>(9),
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
        static some<const char* const*> Strings();
        static some<const char*>        To_String(maybe<Relation_e> relation);
        static maybe<Relation_e>        From_String(maybe<const char*> relation);

    public:
        static some<Relation_e> Between(some<Form_t*> form_a, some<Form_t*> form_b);
        static void             Between(some<Form_t*> form_a, some<Form_t*> form_b, some<Relation_e> relation);

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
        some<const char*> As_String();

    public:
        explicit operator   Bool_t() const;
        operator            value_type() const;

    public:
        Bool_t      operator !() const;
        value_type  operator ()() const;
    };

    template <>
    inline Bool_t Is_Equal(const none<Relation_e>& a, const Relation_e& b)
    {
        return !b;
    }

    template <>
    class none<Relation_e> : public none_numeric<Relation_e>
    {
    public:
        none() : none_numeric(Relation_e::_NONE_) {}
    };

    template <>
    class maybe<Relation_e> : public maybe_numeric<Relation_e>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<Relation_e> : public some_numeric<Relation_e>
    {
    public:
        using some_numeric::some_numeric;
    };

}

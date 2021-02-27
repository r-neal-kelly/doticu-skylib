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
        static some<const char* const*> Strings();
        static some<const char*>        To_String(maybe<Relation_e> relation);
        static maybe<Relation_e>        From_String(maybe<const char*> relation);

    public:
        static some<Relation_e> Between(some<Form_t*> form_a, some<Form_t*> form_b);
        static void             Between(some<Form_t*> form_a, some<Form_t*> form_b, some<Relation_e> relation);

    public:
        Relation_e()                            : Enum_t(_NONE_) {}
        Relation_e(enum_type value)             : Enum_t(value < _TOTAL_ ? value : _NONE_) {}
        Relation_e(value_type value)            : Enum_t(Relation_e(static_cast<enum_type>(value)).value) {}
        Relation_e(const Relation_e& other)     : Enum_t(other.value) {}
        Relation_e(Relation_e&& other) noexcept : Enum_t(std::exchange(other.value, _NONE_)) {}

        Relation_e& operator = (const Relation_e& other)
        {
            if (std::addressof(other) != this) {
                this->value = other.value;
            }
            return *this;
        }

        Relation_e& operator = (Relation_e&& other) noexcept
        {
            if (std::addressof(other) != this) {
                this->value = std::exchange(other.value, _NONE_);
            }
            return *this;
        }

        ~Relation_e()
        {
            this->value = _NONE_;
        }

    public:
        explicit operator   Bool_t () const     { return this->value < _TOTAL_; }
        operator            value_type () const { return static_cast<Bool_t>(*this) ? this->value : _NONE_; }

    public:
        Bool_t      operator !  () const    { return !static_cast<Bool_t>(*this); }
        value_type  operator () () const    { return static_cast<value_type>(*this); }
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

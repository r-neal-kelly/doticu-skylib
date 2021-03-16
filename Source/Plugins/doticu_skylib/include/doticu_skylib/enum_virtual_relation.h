/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/enum_relation.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/maybe_numeric.h"

namespace doticu_skylib {

    class Virtual_Relation_e :
        public Enum_t<s8>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_          = static_cast<value_type>(-128),

            LOVER           = static_cast<value_type>(4),
            ALLY            = static_cast<value_type>(3),
            CONFIDANT       = static_cast<value_type>(2),
            FRIEND          = static_cast<value_type>(1),
            ACQUAINTANCE    = static_cast<value_type>(0),
            RIVAL           = static_cast<value_type>(-1),
            FOE             = static_cast<value_type>(-2),
            ENEMY           = static_cast<value_type>(-3),
            ARCHNEMESIS     = static_cast<value_type>(-4),

            _TOTAL_         = static_cast<value_type>(9),
            _DEFAULT_       = ACQUAINTANCE,
        };

    public:
        static maybe<Relation_e>            To_Relation(maybe<Virtual_Relation_e> v_relation);
        static maybe<Virtual_Relation_e>    From_Relation(maybe<Relation_e> relation);
        static some<const char*>            To_String(maybe<Virtual_Relation_e> v_relation);
        static maybe<Virtual_Relation_e>    From_String(maybe<const char*> v_relation);

    public:
        Virtual_Relation_e();
        Virtual_Relation_e(enum_type value);
        Virtual_Relation_e(value_type value);
        Virtual_Relation_e(const Virtual_Relation_e& other);
        Virtual_Relation_e(Virtual_Relation_e&& other) noexcept;
        Virtual_Relation_e& operator =(const Virtual_Relation_e& other);
        Virtual_Relation_e& operator =(Virtual_Relation_e&& other) noexcept;
        ~Virtual_Relation_e();

    public:
        maybe<Relation_e>   As_Relation();
        some<const char*>   As_String();

    public:
        explicit operator   Bool_t() const;
        operator            value_type() const;

    public:
        Bool_t      operator !() const;
        value_type  operator ()() const;

    public:
        static void Log_Test(std::string indent = "");
    };

    template <>
    inline Bool_t Is_Equal(const none<Virtual_Relation_e>& a, const Virtual_Relation_e& b)
    {
        return !b;
    }

    template <>
    class none<Virtual_Relation_e> : public none_numeric<Virtual_Relation_e>
    {
    public:
        none() : none_numeric(Virtual_Relation_e::_NONE_) {}
    };

    template <>
    class maybe<Virtual_Relation_e> : public maybe_numeric<Virtual_Relation_e>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<Virtual_Relation_e> : public some_numeric<Virtual_Relation_e>
    {
    public:
        using some_numeric::some_numeric;
    };

}

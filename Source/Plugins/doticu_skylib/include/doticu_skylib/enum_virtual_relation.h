/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/enum_relation.h"
#include "doticu_skylib/maybe_enum.h"

namespace doticu_skylib {

    class Virtual_Relation_e :
        public Enum_t<s8>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_          = -128,

            LOVER           = 4,
            ALLY            = 3,
            CONFIDANT       = 2,
            FRIEND          = 1,
            ACQUAINTANCE    = 0,
            RIVAL           = -1,
            FOE             = -2,
            ENEMY           = -3,
            ARCHNEMESIS     = -4,

            _TOTAL_         = 9,
            _DEFAULT_       = ACQUAINTANCE,
        };

    public:
        static Bool_t                       Is_Valid(enum_type value);
        static Bool_t                       Is_Valid(value_type value);

        static maybe<Relation_e>            To_Relation(Virtual_Relation_e::enum_type v_relation);
        static maybe<Relation_e>            To_Relation(Virtual_Relation_e::value_type v_relation);
        static maybe<Relation_e>            To_Relation(Virtual_Relation_e v_relation);
        static maybe<Relation_e>            To_Relation(maybe<Virtual_Relation_e> v_relation);
        static some<Relation_e>             To_Relation(some<Virtual_Relation_e> v_relation);
        static maybe<Virtual_Relation_e>    From_Relation(Relation_e::enum_type relation);
        static maybe<Virtual_Relation_e>    From_Relation(Relation_e::value_type relation);
        static maybe<Virtual_Relation_e>    From_Relation(Relation_e relation);
        static maybe<Virtual_Relation_e>    From_Relation(maybe<Relation_e> relation);
        static some<Virtual_Relation_e>     From_Relation(some<Relation_e> relation);

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
        maybe<Relation_e>   As_Relation() const;
        some<const char*>   As_String() const;

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
    class none<Virtual_Relation_e> :
        public none_enum<Virtual_Relation_e>
    {
    public:
        using none_enum::none_enum;
    };

    template <>
    class maybe<Virtual_Relation_e> :
        public maybe_enum<Virtual_Relation_e>
    {
    public:
        using maybe_enum::maybe_enum;
    };

    template <>
    class some<Virtual_Relation_e> :
        public some_enum<Virtual_Relation_e>
    {
    public:
        using some_enum::some_enum;
    };

}

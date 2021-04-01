/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_relation.h"
#include "doticu_skylib/enum_type.h"

namespace doticu_skylib {

    class Virtual_Relation_e_data :
        public Enum_Type_Data_t<s8>
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
        static Bool_t               Is_Valid(value_type value);

        static some<const char*>    To_String(value_type value);
        static value_type           From_String(maybe<const char*> string);
    };

    class Virtual_Relation_e :
        public Enum_Type_t<Virtual_Relation_e_data>
    {
    public:
        static maybe<Relation_e>            To_Relation(maybe<Virtual_Relation_e> v_relation);
        static maybe<Virtual_Relation_e>    From_Relation(maybe<Relation_e> relation);

    public:
        using Enum_Type_t::Enum_Type_t;

        Virtual_Relation_e() = default;
        Virtual_Relation_e(Relation_e relation);
        Virtual_Relation_e(maybe<Relation_e> relation);
        Virtual_Relation_e(some<Relation_e> relation);

    public:
        maybe<Relation_e>   As_Relation() const;

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

        maybe() = default;

        maybe(maybe<Relation_e> relation) :
            maybe_enum(Virtual_Relation_e(relation))
        {
        }
    };

    template <>
    class some<Virtual_Relation_e> :
        public some_enum<Virtual_Relation_e>
    {
    public:
        using some_enum::some_enum;

        some() = default;

        some(some<Relation_e> relation) :
            some_enum(Virtual_Relation_e(relation))
        {
        }
    };

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/enum_relation.h"
#include "doticu_skylib/game.h"

namespace doticu_skylib {

    Bool_t Relation_e_data::Is_Valid(value_type value)
    {
        return value > _NONE_ && value < _TOTAL_;
    }

    some<const char* const*> Relation_e_data::Strings()
    {
        static const char* const strings[_TOTAL_] =
        {
            SKYLIB_ENUM_TO_STRING(LOVER),
            SKYLIB_ENUM_TO_STRING(ALLY),
            SKYLIB_ENUM_TO_STRING(CONFIDANT),
            SKYLIB_ENUM_TO_STRING(FRIEND),
            SKYLIB_ENUM_TO_STRING(ACQUAINTANCE),
            SKYLIB_ENUM_TO_STRING(RIVAL),
            SKYLIB_ENUM_TO_STRING(FOE),
            SKYLIB_ENUM_TO_STRING(ENEMY),
            SKYLIB_ENUM_TO_STRING(ARCHNEMESIS),
        };

        return strings;
    }

    some<const char*> Relation_e_data::To_String(value_type value)
    {
        return Enum_Type_Data_t::To_String(Strings(), "NONE", &Is_Valid, value);
    }

    Relation_e_data::value_type Relation_e_data::From_String(maybe<const char*> string)
    {
        return Enum_Type_Data_t::From_String(Strings(), _NONE_, _TOTAL_, string);
    }

    some<Relation_e> Relation_e::Between(some<Form_t*> form_a, some<Form_t*> form_b)
    {
        static auto get = reinterpret_cast
            <u32(*)(Form_t*, Form_t*)>
            (Game_t::Base_Address() + Offset_e::GET);

        SKYLIB_ASSERT_SOME(form_a);
        SKYLIB_ASSERT_SOME(form_b);

        maybe<Relation_e> relation = get(form_a(), form_b());
        if (relation) {
            return relation();
        } else {
            return _DEFAULT_;
        }
    }

    void Relation_e::Between(some<Form_t*> form_a, some<Form_t*> form_b, some<Relation_e> relation)
    {
        static auto set = reinterpret_cast
            <void(*)(Form_t*, Form_t*, u32)>
            (Game_t::Base_Address() + Offset_e::SET);

        SKYLIB_ASSERT_SOME(form_a);
        SKYLIB_ASSERT_SOME(form_b);
        SKYLIB_ASSERT_SOME(relation);

        set(form_a(), form_b(), relation());
    }

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cstring.h"
#include "doticu_skylib/enum_relation.h"
#include "doticu_skylib/game.h"

namespace doticu_skylib {

    some<const char* const*> Relation_e::Strings()
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

    some<const char*> Relation_e::To_String(maybe<Relation_e> relation)
    {
        if (relation) {
            return Strings()[relation()];
        } else {
            return "NONE";
        }
    }

    maybe<Relation_e> Relation_e::From_String(maybe<const char*> relation)
    {
        if (relation) {
            some<const char* const*> strings = Strings();
            for (size_t idx = 0, end = _TOTAL_; idx < end; idx += 1) {
                some<const char*> string = strings[idx];
                if (CString_t::Is_Same(string(), relation(), true)) {
                    return static_cast<Relation_e::value_type>(idx);
                }
            }
            return _NONE_;
        } else {
            return _NONE_;
        }
    }

    some<Relation_e> Relation_e::Between(some<Form_t*> form_a, some<Form_t*> form_b)
    {
        static auto get = reinterpret_cast
            <Relation_e::value_type(*)(Form_t*, Form_t*)>
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
            <void(*)(Form_t*, Form_t*, Relation_e::value_type)>
            (Game_t::Base_Address() + Offset_e::SET);

        SKYLIB_ASSERT_SOME(form_a);
        SKYLIB_ASSERT_SOME(form_b);
        SKYLIB_ASSERT_SOME(relation);

        set(form_a(), form_b(), relation());
    }

}

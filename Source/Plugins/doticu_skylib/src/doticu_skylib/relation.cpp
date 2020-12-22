/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cstring.h"

#include "doticu_skylib/game.h"
#include "doticu_skylib/relation.h"

namespace doticu_skylib {

    Relation_e Relation_e::Between(Form_t* form_a, Form_t* form_b)
    {
        static auto get = reinterpret_cast
            <u8(*)(Form_t*, Form_t*)>
            (Game_t::Base_Address() + Offset_e::GET);

        if (form_a && form_b) {
            return get(form_a, form_b);
        } else {
            return Relation_e::NONE;
        }
    }

    void Relation_e::Between(Form_t* form_a, Form_t* form_b, Relation_e relation)
    {
        static auto set = reinterpret_cast
            <void(*)(Form_t*, Form_t*, u8)>
            (Game_t::Base_Address() + Offset_e::SET);

        if (form_a && form_b && relation > Relation_e::NONE && relation < Relation_e::_END_) {
            set(form_a, form_b, relation);
        }
    }

    some<const char*> Relation_e::To_String(Relation_e relation)
    {
        if (relation == Relation_e::LOVER) {
            return LOVER_STRING;
        } else if (relation == Relation_e::ALLY) {
            return ALLY_STRING;
        } else if (relation == Relation_e::CONFIDANT) {
            return CONFIDANT_STRING;
        } else if (relation == Relation_e::FRIEND) {
            return FRIEND_STRING;
        } else if (relation == Relation_e::ACQUAINTANCE) {
            return ACQUAINTANCE_STRING;
        } else if (relation == Relation_e::RIVAL) {
            return RIVAL_STRING;
        } else if (relation == Relation_e::FOE) {
            return FOE_STRING;
        } else if (relation == Relation_e::ENEMY) {
            return ENEMY_STRING;
        } else if (relation == Relation_e::ARCHNEMESIS) {
            return ARCHNEMESIS_STRING;
        } else {
            return NONE_STRING;
        }
    }

    Relation_e Relation_e::From_String(maybe<const char*> relation)
    {
        if (relation) {
            char* str = const_cast<char*>(relation());
            while (*str == ' ') {
                str += 1;
            }

            if (CString_t::Starts_With(LOVER_STRING, str, true)) {
                return Relation_e::LOVER;
            } else if (CString_t::Starts_With(ALLY_STRING, str, true)) {
                return Relation_e::ALLY;
            } else if (CString_t::Starts_With(CONFIDANT_STRING, str, true)) {
                return Relation_e::CONFIDANT;
            } else if (CString_t::Starts_With(FRIEND_STRING, str, true)) {
                return Relation_e::FRIEND;
            } else if (CString_t::Starts_With(ACQUAINTANCE_STRING, str, true)) {
                return Relation_e::ACQUAINTANCE;
            } else if (CString_t::Starts_With(RIVAL_STRING, str, true)) {
                return Relation_e::RIVAL;
            } else if (CString_t::Starts_With(FOE_STRING, str, true)) {
                return Relation_e::FOE;
            } else if (CString_t::Starts_With(ENEMY_STRING, str, true)) {
                return Relation_e::ENEMY;
            } else if (CString_t::Starts_With(ARCHNEMESIS_STRING, str, true)) {
                return Relation_e::ARCHNEMESIS;
            } else {
                return Relation_e::NONE;
            }
        } else {
            return Relation_e::NONE;
        }
    }

}

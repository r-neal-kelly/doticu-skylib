/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/utils.h"
#include "doticu_skylib/relation.h"

namespace doticu_skylib {

    Relation_e Relation_e::Between(Form_t* form_a, Form_t* form_b)
    {
        static auto get = reinterpret_cast
            <u8(*)(Form_t*, Form_t*)>
            (RelocationManager::s_baseAddr + Offset_e::GET);
        return get(form_a, form_b);
    }

    void Relation_e::Between(Form_t* form_a, Form_t* form_b, Relation_e relation)
    {
        static auto set = reinterpret_cast
            <void(*)(Form_t*, Form_t*, u8)>
            (RelocationManager::s_baseAddr + Offset_e::SET);
        if (relation > -1) {
            set(form_a, form_b, relation);
        }
    }

    const char* Relation_e::To_String(Relation_e relation)
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

    Relation_e Relation_e::From_String(const char* relation)
    {
        constexpr Word_t MAX_LENGTH = 15;
        char copy[MAX_LENGTH + 1];
        Index_t copy_idx = 0;
        for (Index_t idx = 0; relation[idx] != 0 && copy_idx < MAX_LENGTH; idx += 1) {
            if (relation[idx] != ' ') {
                copy[copy_idx] = relation[idx];
                copy_idx += 1;
            }
        }
        copy[copy_idx] = 0;

        if (CString_t::Is_Same(copy, LOVER_STRING, true)) {
            return Relation_e::LOVER;
        } else if (CString_t::Is_Same(copy, ALLY_STRING, true)) {
            return Relation_e::ALLY;
        } else if (CString_t::Is_Same(copy, CONFIDANT_STRING, true)) {
            return Relation_e::CONFIDANT;
        } else if (CString_t::Is_Same(copy, FRIEND_STRING, true)) {
            return Relation_e::FRIEND;
        } else if (CString_t::Is_Same(copy, ACQUAINTANCE_STRING, true)) {
            return Relation_e::ACQUAINTANCE;
        } else if (CString_t::Is_Same(copy, RIVAL_STRING, true)) {
            return Relation_e::RIVAL;
        } else if (CString_t::Is_Same(copy, FOE_STRING, true)) {
            return Relation_e::FOE;
        } else if (CString_t::Is_Same(copy, ENEMY_STRING, true)) {
            return Relation_e::ENEMY;
        } else if (CString_t::Is_Same(copy, ARCHNEMESIS_STRING, true)) {
            return Relation_e::ARCHNEMESIS;
        } else {
            return Relation_e::NONE;
        }
    }

}

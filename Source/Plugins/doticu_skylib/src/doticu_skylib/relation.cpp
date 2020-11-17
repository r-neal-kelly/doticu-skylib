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

}

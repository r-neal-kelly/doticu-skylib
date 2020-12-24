/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"

#include "doticu_skylib/form_type.h"
#include "doticu_skylib/virtual.h"
#include "doticu_skylib/virtual_type.h"

namespace doticu_skylib { namespace Virtual {

    class Variable_t;

    class Array_t
    {
    public:
        static Array_t* Create(Type_e item_type, u32 count);
        static void Destroy(Array_t* arr);

    public:
        UInt32 ref_count; // 00
        UInt32 pad_04; // 04
        Type_e item_type; // 08
        UInt32 count; // 10
        UInt32 pad_14; // 14
        UInt64 lock; // 18
        //Variable_t* variables[0]; // 20

        void Increment_Count();
        void Decrement_Count();

        Type_e      Array_Type();
        Variable_t* Variables();
        Variable_t* Point(Word_t idx);

        template <typename Arrayable_t>
        Vector_t<Arrayable_t>   Unpack();
        template <typename Arrayable_t>
        void                    Unpack(Vector_t<Arrayable_t>& results);

        /*template <typename Type>
        Int_t Find(Type element); // Index_Of
        template <typename Type>
        Int_t Find(Form_Type_e form_type, Type* element);
        template <typename Type>
        Bool_t Has(Type element);
        template <typename Type>
        Bool_t Has(Form_Type_e form_type, Type* element);*/
    };
    STATIC_ASSERT(sizeof(Array_t) == 0x20);

}}

namespace doticu_skylib { namespace Virtual {

    template <typename Arrayable_t>
    inline Vector_t<Arrayable_t> Array_t::Unpack()
    {
        Vector_t<Arrayable_t> results;
        Unpack(results);
        return results;
    }

    template <typename Arrayable_t>
    inline void Array_t::Unpack(Vector_t<Arrayable_t>& results)
    {
        results.reserve(count);
        for (Index_t idx = 0, end = count; idx < end; idx += 1) {
            Variable_t* variable = Point(idx);
            if (variable) {
                results.push_back(variable->Unpack<Arrayable_t>());
            }
        }
    }

}}

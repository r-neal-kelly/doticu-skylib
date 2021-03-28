/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/atomic_count.h"
#include "doticu_skylib/collections.h"
#include "doticu_skylib/enum_form_type.h"
#include "doticu_skylib/virtual.h"
#include "doticu_skylib/virtual_type.h"

namespace doticu_skylib { namespace Virtual {

    class Variable_t;

    class Array_t : public Atomic_Count_t
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                DESTROY = 0x01241E40, // 97723
            };
            using Enum_t::Enum_t;
        };

    public:
        u32             pad_04;         // 04
        Type_e          item_type;      // 08
        u32             count;          // 10
        u32             pad_14;         // 14
        u64             lock;           // 18 (Spin_Lock_t)
        //Variable_t*   variables[0];   // 20

    public:
        void        Destroy();

        u32         Reference_Count();
        u32         Increment_Reference();
        u32         Decrement_Reference();

        Type_e      Array_Type();
        Variable_t* Variables();
        Variable_t* Point(u32 idx);

        template <typename Arrayable_t, enable_if_arrayable_t<Arrayable_t> = true>
        Arrayable_t Unpack();
        template <typename Arrayable_t, enable_if_arrayable_t<Arrayable_t> = true>
        void        Unpack(Arrayable_t& results);

        template <typename Arrayable_t, enable_if_arrayable_t<Arrayable_t> = true>
        void        Pack(const Arrayable_t& values);

        template <typename Intrinsic_t>
        u32         Index_Of(const Intrinsic_t& intrinsic);
        template <typename Intrinsic_t>
        Bool_t      Has(const Intrinsic_t& intrinsic);
    };
    STATIC_ASSERT(sizeof(Array_t) == 0x20);

}}

#include "doticu_skylib/virtual_variable.inl"

namespace doticu_skylib { namespace Virtual {

    template <typename Arrayable_t, enable_if_arrayable_t<Arrayable_t>>
    inline Arrayable_t Array_t::Unpack()
    {
        Arrayable_t results;
        Unpack(results);
        return results;
    }

    template <typename Arrayable_t, enable_if_arrayable_t<Arrayable_t>>
    inline void Array_t::Unpack(Arrayable_t& results)
    {
        results.reserve(count);
        for (size_t idx = 0, end = count; idx < end; idx += 1) {
            Variable_t* variable = Point(idx);
            if (variable) {
                results.push_back(variable->Unpack<Arrayable_t::value_type>());
            }
        }
    }

    template <typename Arrayable_t, enable_if_arrayable_t<Arrayable_t>>
    inline void Array_t::Pack(const Arrayable_t& values)
    {
        for (size_t idx = 0, end = count; idx < end; idx += 1) {
            Variable_t* variable = Point(idx);
            if (variable) {
                variable->Pack<Arrayable_t::value_type>(values[idx]);
            }
        }
    }

    template <typename Intrinsic_t>
    inline u32 Array_t::Index_Of(const Intrinsic_t& intrinsic)
    {
        Type_e intrinsic_type = Type_e::From<Intrinsic_t>();
        if (this->item_type == intrinsic_type) {
            for (size_t idx = 0, end = this->count; idx < end; idx += 1) {
                Variable_tt<Intrinsic_t>* variable =
                    static_cast<Variable_tt<Intrinsic_t>*>(this->Point(idx));
                if (variable && variable == intrinsic) {
                    return static_cast<u32>(idx);
                }
            }
            return ~static_cast<u32>(0);
        } else {
            return ~static_cast<u32>(0);
        }
    }

    template <typename Intrinsic_t>
    inline Bool_t Array_t::Has(const Intrinsic_t& intrinsic)
    {
        return Index_Of(intrinsic) != ~static_cast<u32>(0);
    }

}}

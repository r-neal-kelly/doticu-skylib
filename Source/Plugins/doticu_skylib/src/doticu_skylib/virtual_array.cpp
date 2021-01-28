/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.inl"

#include "doticu_skylib/virtual_array.h"
#include "doticu_skylib/virtual_variable.inl"

namespace doticu_skylib { namespace Virtual {

    void Array_t::Destroy()
    {
        static auto destroy = reinterpret_cast
            <void(*)(Array_t*)>
            (Game_t::Base_Address() + static_cast<Word_t>(Offset_e::DESTROY));

        destroy(this);
    }

    u32 Array_t::Reference_Count()
    {
        return Atomic_Count_t::Atomic_Count();
    }

    u32 Array_t::Increment_Reference()
    {
        return Atomic_Count_t::Increment_Atomic();
    }

    u32 Array_t::Decrement_Reference()
    {
        u32 count = Atomic_Count_t::Decrement_Atomic();
        if (count < 1) {
            Destroy();
            Game_t::Deallocate<Array_t>(this);
        }
        return count;
    }

    Type_e Array_t::Array_Type()
    {
        return item_type.As_Array();
    }

    Variable_t* Array_t::Variables()
    {
        SKYLIB_ASSERT(count > 0);
        return reinterpret_cast<Variable_t*>(this + 1);
    }

    Variable_t* Array_t::Point(u32 idx)
    {
        SKYLIB_ASSERT(idx < count);
        return Variables() + idx;
    }

}}

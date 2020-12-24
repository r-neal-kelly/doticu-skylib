/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/virtual_array.h"
#include "doticu_skylib/virtual_variable.h"

namespace doticu_skylib { namespace Virtual {

    Type_e Array_t::Array_Type()
    {
        return item_type.As_Array();
    }

    Variable_t* Array_t::Variables()
    {
        SKYLIB_ASSERT(count > 0);
        return reinterpret_cast<Variable_t*>(this + 1);
    }

    Variable_t* Array_t::Point(Word_t idx)
    {
        SKYLIB_ASSERT(idx < count);
        return Variables() + idx;
    }

}}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_list.h"

namespace doticu_skylib {

    template <typename Type_t>
    inline Bool_t List_x::Has()
    {
        return Has(Type_t::EXTRA_TYPE);
    }

    template <typename Type_t>
    inline Type_t* List_x::Get()
    {
        return static_cast<Type_t*>(Get(Type_t::EXTRA_TYPE));
    }

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_list.h"

namespace doticu_skylib {

    template <typename Extra_t>
    inline Bool_t List_x::Has()
    {
        return Has(Extra_t::EXTRA_TYPE);
    }

    template <typename Extra_t>
    inline maybe<Extra_t*> List_x::Get()
    {
        return static_cast<maybe<Extra_t*>>(Get(Extra_t::EXTRA_TYPE));
    }

    template <typename Extra_t>
    Bool_t List_x::Add(some<Extra_t*> extra)
    {
        return Add(static_cast<some<Data_x*>>(extra));
    }

    template <typename Extra_t>
    Bool_t List_x::Remove(some<Extra_t*> extra)
    {
        return Remove(static_cast<some<Data_x*>>(extra));
    }

}

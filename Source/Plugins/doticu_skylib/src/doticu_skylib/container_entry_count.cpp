/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/container_entry_count.h"

namespace doticu_skylib {

    Container_Entry_Count_t::Container_Entry_Count_t() :
        value(NONE_VALUE)
    {
    }

    Container_Entry_Count_t::Container_Entry_Count_t(value_type value) :
        value(value > NONE_VALUE ? value : NONE_VALUE)
    {
    }

    Container_Entry_Count_t::operator value_type() const
    {
        return this->value;
    }

}

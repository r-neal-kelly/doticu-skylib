/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/container_entry_count.h"
#include "doticu_skylib/math.h"

namespace doticu_skylib {

    Container_Entry_Count_t::Container_Entry_Count_t() :
        value(0)
    {
    }

    Container_Entry_Count_t::Container_Entry_Count_t(value_type value) :
        value(value < 0 ? std::numeric_limits<value_type>::max() : value)
    {
    }

    Container_Entry_Count_t::operator value_type() const
    {
        return this->value < 0 ? std::numeric_limits<value_type>::max() : this->value;
    }

}

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
        value(value)
    {
    }

    Container_Entry_Count_t::operator value_type() const
    {
        if (this->operator Bool_t()) {
            return this->value;
        } else {
            return NONE_VALUE;
        }
    }

    Container_Entry_Count_t::operator Bool_t() const
    {
        return this->value > NONE_VALUE;
    }

    Bool_t Container_Entry_Count_t::operator !() const
    {
        return !static_cast<Bool_t>(*this);
    }

    Container_Entry_Count_t::value_type Container_Entry_Count_t::operator -() const
    {
        return -static_cast<value_type>(*this);
    }

}

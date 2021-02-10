/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/virtual_stack_id.h"

namespace doticu_skylib { namespace Virtual {

    Stack_ID_t::Stack_ID_t() :
        value(NONE_VALUE)
    {
    }

    Stack_ID_t::Stack_ID_t(value_type value) :
        value(value)
    {
    }

    Stack_ID_t::operator value_type() const
    {
        return this->value;
    }

    Stack_ID_t::operator Bool_t() const
    {
        return this->value != NONE_VALUE;
    }

    Bool_t Stack_ID_t::operator !() const
    {
        return !static_cast<Bool_t>(*this);
    }

}}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/global.h"

namespace doticu_skylib {

    template <typename Type_t>
    Type_t Global_t::As()
    {
        return static_cast<Type_t>(this->value);
    }

    template <typename Type_t>
    void Global_t::As(Type_t value)
    {
        this->value = static_cast<Float_t>(value);
    }

}

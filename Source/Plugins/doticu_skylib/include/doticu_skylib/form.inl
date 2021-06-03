/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/form.h"
#include "doticu_skylib/game.inl"

namespace doticu_skylib {

    template <typename T>
    inline maybe<T*> Form_t::As() const
    {
        return Game_t::Runtime_Cast<Form_t, T>(this);
    }

    template <typename T>
    inline Bool_t Form_t::Is() const
    {
        return As<T>() != none<T*>();
    }

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    constexpr Float_t PI = 3.141592741f;

    template <typename Num>
    inline Bool_t Is_Odd(Num num)
    {
        return num & static_cast<Num>(1);
    }

    template <typename Num>
    inline Bool_t Is_Even(Num num)
    {
        return !Is_Odd(num);
    }

}

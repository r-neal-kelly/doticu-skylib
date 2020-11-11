/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "common/IErrors.h"

#include "doticu_skylib/intrinsic.h"

#define M \
    do {

#define W \
    } while (0)

#if 1

#define SKYLIB_ASSERT(IS_TRUE)                                      \
M                                                                   \
    if (!(IS_TRUE)) {                                               \
        _MESSAGE("Asserted. Exiting Skyrim. Failed: %s", #IS_TRUE); \
        _AssertionFailed(__FILE__, __LINE__, #IS_TRUE);             \
    }                                                               \
W

#else

#define SKYLIB_ASSERT(IGNORED_)

#endif

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

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <cstdint>

#include "common/IErrors.h"

#define SKYLIB_M \
    do {

#define SKYLIB_W \
    } while (0)

#if 1
    #define SKYLIB_ASSERT(IS_TRUE_, ...)                        \
    SKYLIB_M                                                    \
        if (!(IS_TRUE_)) {                                      \
            _MESSAGE("Asserted. Exiting Skyrim. " __VA_ARGS__); \
            _AssertionFailed(__FILE__, __LINE__, #IS_TRUE_);    \
        }                                                       \
    SKYLIB_W

    #define SKYLIB_ASSERT_SOME(SOME_, ...) \
        SKYLIB_ASSERT(SOME_, "Missing a required pointer. " __VA_ARGS__)
    #define SKYLIB_ASSERT_MAYBE(MAYBE_, ...) \
        SKYLIB_ASSERT(MAYBE_, "Failed to check an optional pointer. " __VA_ARGS__)
#else
    #define SKYLIB_ASSERT(IGNORED_)
    #define SKYLIB_ASSERT_SOME_P(IGNORED_)
    #define SKYLIB_ASSERT_MAYBE_P(IGNORED_)
#endif

namespace doticu_skylib {

    using u8        = std::uint8_t;
    using u16       = std::uint16_t;
    using u32       = std::uint32_t;
    using u64       = std::uint64_t;

    using s8        = std::int8_t;
    using s16       = std::int16_t;
    using s32       = std::int32_t;
    using s64       = std::int64_t;

    using f32       = float;
    using f64       = double;

    using Bool_t    = bool;
    using Int_t     = s32;
    using Float_t   = float;

    using Byte_t    = u8;
    using Word_t    = size_t;
    using Index_t   = s64;
    using Nullptr_t = decltype(nullptr);

}

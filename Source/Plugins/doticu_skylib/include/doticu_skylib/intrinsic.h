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

#define SKYLIB_TAB "    "

#define SKYLIB_DEFINE_FLAG(ENUM_BASE_, ENUM_)                           \
    ENUM_ = static_cast<ENUM_BASE_::value_type>(1 << ENUM_BASE_::ENUM_)

#define SKYLIB_ENUM_TO_STRING(ENUM_)    \
(                                       \
    ENUM_ ? #ENUM_ : #ENUM_             \
)

#define SKYLIB_ENUM_IS_FLAGGED_STRING(ENUM_)                                    \
(                                                                               \
    std::string(SKYLIB_ENUM_TO_STRING(ENUM_)) + ": " + Is_Flagged_String(ENUM_) \
)

#define SKYLIB_LOG(MESSAGE_, ...)\
    _MESSAGE(std::string(MESSAGE_).c_str(), __VA_ARGS__)

#define SKYLIB_GAME_LOG(MESSAGE_, ...)\
    doticu_skylib::Console_Log_t::Self()->Print(MESSAGE_, __VA_ARGS__);

#if 1
    #define SKYLIB_ASSERT(IS_TRUE_, ...)                            \
    (                                                               \
        !(IS_TRUE_) ? (                                             \
            SKYLIB_LOG("Asserted. Exiting Skyrim. " __VA_ARGS__),   \
            _AssertionFailed(__FILE__, __LINE__, #IS_TRUE_),        \
            false                                                   \
        ) : (                                                       \
            true                                                    \
        )                                                           \
    )

    #define SKYLIB_ASSERT_SOME(SOME_, ...) \
        SKYLIB_ASSERT(SOME_, "Missing some required object. " __VA_ARGS__)
#else
    #define SKYLIB_ASSERT(IGNORED_)
    #define SKYLIB_ASSERT_SOME(IGNORED_)
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
    using Double_t  = double;

    using Byte_t    = u8;
    using Word_t    = size_t;
    using Nullptr_t = decltype(nullptr);

}

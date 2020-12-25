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

#define SKYLIB_LOG(MESSAGE_, ...) _MESSAGE(std::string(MESSAGE_).c_str(), __VA_ARGS__)

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

namespace doticu_skylib {

    template <typename ...Ts>
    class traits_wrap_t
    {
    public:
    };

    template <typename T>
    using iterable_traits_t = traits_wrap_t<
        typename T::value_type,
        decltype(std::declval<T>().begin()),
        decltype(std::declval<T>().end())
    >;

    template <typename T, typename _ = void>
    class is_iterable : public std::false_type
    {
    public:
    };

    template <typename T>
    class is_iterable<T, std::conditional_t<false, iterable_traits_t<T>, void>> : public std::true_type
    {
    public:
    };

    template <typename T>
    using arrayable_traits_t = traits_wrap_t<
        typename T::value_type,
        typename T::size_type,
        decltype(std::declval<T>().size())
    >;

    template <typename T, typename _ = void>
    class is_arrayable : public std::false_type
    {
    public:
    };

    template <typename T>
    class is_arrayable<T, std::conditional_t<false, arrayable_traits_t<T>, void>> : public std::true_type
    {
    public:
    };

    template <typename T>
    using enable_if_iterable_t = std::enable_if_t<
        is_iterable<T>::value,
        Bool_t
    >;

    template <typename T>
    using enable_if_arrayable_t = std::enable_if_t<
        is_arrayable<T>::value,
        Bool_t
    >;

    template <typename T>
    using enable_if_void_t = std::enable_if_t <
        std::is_same<T, void>::value,
        Bool_t
    >;

    template <typename T>
    using enable_if_pointer_t = std::enable_if_t<
        std::is_pointer<T>::value,
        Bool_t
    >;

    template <typename T>
    using enable_if_not_pointer_t = std::enable_if_t<
        !std::is_pointer<T>::value,
        Bool_t
    >;

    template <typename T>
    using enable_if_boolean_t = std::enable_if_t<
        std::is_same<T, bool>::value,
        Bool_t
    >;

    template <typename T>
    using enable_if_integer_32_or_less_t = std::enable_if_t<
        std::is_integral<T>::value &&
        sizeof(T) <= sizeof(u32) &&
        !std::is_same<T, bool>::value,
        Bool_t
    >;

    template <typename T>
    using enable_if_float_32_or_less_t = std::enable_if_t<
        std::is_floating_point<T>::value &&
        sizeof(T) <= sizeof(f32),
        Bool_t
    >;

    template <typename T>
    using enable_if_not_pointer_and_not_arithmetic = std::enable_if_t<
        !std::is_pointer<T>::value &&
        !std::is_arithmetic<T>::value,
        Bool_t
    >;

}

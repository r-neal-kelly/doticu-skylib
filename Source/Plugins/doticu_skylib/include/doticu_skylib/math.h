/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#undef max
#undef min

#include <limits>
#include <mutex>
#include <random>

#include "doticu_skylib/enum.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/traits.h"

namespace doticu_skylib {

    // these really need to be put in Math_t

    constexpr Float_t PI = 3.141592741f;

    template <typename Num, std::enable_if_t<std::is_arithmetic<Num>::value, Bool_t> = true>
    inline Bool_t Is_Odd(Num num)
    {
        return num & static_cast<Num>(1);
    }

    template <typename Num, std::enable_if_t<std::is_arithmetic<Num>::value, Bool_t> = true>
    inline Bool_t Is_Even(Num num)
    {
        return !Is_Odd(num);
    }

    inline Float_t To_Degrees(Float_t radians)
    {
        return radians * (180.0f / PI);
    }

    inline Float_t To_Radians(Float_t degrees)
    {
        return degrees * PI / 180.0f;
    }

    template <typename T>
    inline T Limit(T value, T minimum, T maximum)
    {
        if (value < minimum) {
            return minimum;
        } else if (value > maximum) {
            return maximum;
        } else {
            return value;
        }
    }

    class Math_t
    {
    public:
        static std::random_device   random_device;
        static std::mt19937_64      random_generator;
        static std::mutex           random_lock;

    public:
        template <typename T>
        static T Max(T a, T b)
        {
            return a > b ? a : b;
        }

        template <typename T>
        static T Random(T min, T max)
        {
            std::lock_guard<std::mutex> random_locker(random_lock);
            return std::uniform_int_distribution<T>(min, max)(Math_t::random_generator);
        }

        static Bool_t Random_Bool()
        {
            return Random_Bool(50);
        }

        static Bool_t Random_Bool(u8 probability_percent)
        {
            if (probability_percent == 0) {
                return false;
            } else if (probability_percent >= 100) {
                return true;
            } else {
                return Random(1, 100) < probability_percent;
            }
        }
    };

    class CRC32_Hash_t
    {
    public:
        template <typename T>
        using enable_if_32 = std::enable_if_t<
            sizeof(T) == sizeof(u32),
            Bool_t
        >;
        template <typename T>
        using enable_if_64 = std::enable_if_t<
            sizeof(T) == sizeof(u64),
            Bool_t
        >;
        template <typename T>
        using enable_if_not_32_or_64 = std::enable_if_t<
            sizeof(T) != sizeof(u64) &&
            sizeof(T) != sizeof(u32),
            Bool_t
        >;

    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : Word_t
            {
                HASH_SIZE   = 0x00C06490,
                HASH_32     = 0x00C064F0,
                HASH_64     = 0x00C06570,
            };
            using Enum_t::Enum_t;
        };

        static u32 Hash(const void* value, u32 size);
        static u32 Hash(u32 value);
        static u32 Hash(u64 value);

        template <typename T, enable_if_32<T> = true>
        static u32 Hash(T value)
        {
            return Hash(*reinterpret_cast<u32*>(std::addressof(value)));
        }

        template <typename T, enable_if_64<T> = true>
        static u32 Hash(T value)
        {
            return Hash(*reinterpret_cast<u64*>(std::addressof(value)));
        }

        template <typename T, enable_if_not_32_or_64<T> = true>
        static u32 Hash(const T& value)
        {
            return Hash(reinterpret_cast<const void*>(std::addressof(value)), sizeof(T));
        }
    };

}

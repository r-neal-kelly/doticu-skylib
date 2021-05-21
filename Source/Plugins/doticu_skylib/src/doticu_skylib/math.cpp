/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.h"
#include "doticu_skylib/math.h"

namespace doticu_skylib {

    std::random_device  Math_t::random_device;
    std::mt19937_64     Math_t::random_generator(Math_t::random_device());
    std::mutex          Math_t::random_lock;

    u32 CRC32_Hash_t::Hash(const void* value, u32 size)
    {
        static auto hash_size = reinterpret_cast
            <void(*)(u32&, const void*, u32)>
            (Game_t::Base_Address() + Offset_e::HASH_SIZE);

        u32 result;
        hash_size(result, value, size);
        return result;
    }

    u32 CRC32_Hash_t::Hash(u32 value)
    {
        static auto hash_32 = reinterpret_cast
            <void(*)(u32&, u32)>
            (Game_t::Base_Address() + Offset_e::HASH_32);

        u32 result;
        hash_32(result, value);
        return result;
    }

    u32 CRC32_Hash_t::Hash(u64 value)
    {
        static auto hash_64 = reinterpret_cast
            <void(*)(u32&, u64)>
            (Game_t::Base_Address() + Offset_e::HASH_64);

        u32 result;
        hash_64(result, value);
        return result;
    }

}

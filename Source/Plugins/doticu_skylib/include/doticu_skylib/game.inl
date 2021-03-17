/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/game.h"
#include "doticu_skylib/memory.h"

namespace doticu_skylib {

    template <typename T>
    inline some<T*> Game_t::Allocate(size_t count)
    {
        SKYLIB_ASSERT(count > 0);

        maybe<Byte_t*> data = Memory_t::Self()->Allocate(sizeof(T) * count);
        SKYLIB_ASSERT(data);
        return reinterpret_cast<T*>(data());
    }

    template <typename T>
    inline some<T*> Game_t::Callocate(size_t count)
    {
        SKYLIB_ASSERT(count > 0);

        some<T*> data = Allocate<T>(count);
        memset(static_cast<void*>(data()), 0, sizeof(T) * count);
        return data;
    }

    template <typename T>
    inline some<T*> Game_t::Reallocate(some<T*> data, size_t new_count)
    {
        SKYLIB_ASSERT(new_count > 0);

        maybe<Byte_t*> new_data = Memory_t::Self()->Reallocate(reinterpret_cast<Byte_t*>(data()), sizeof(T) * new_count);
        SKYLIB_ASSERT(new_data);
        return reinterpret_cast<T*>(new_data());
    }

    template <typename T>
    inline void Game_t::Deallocate(some<T*> data)
    {
        SKYLIB_ASSERT_SOME(data);
        Memory_t::Self()->Deallocate(reinterpret_cast<Byte_t*>(data()));
    }

    template <typename From_t, typename To_t>
    inline maybe<To_t*> Game_t::Runtime_Cast(some<const From_t*> from)
    {
        static auto runtime_cast = reinterpret_cast
            <void *(*)(const void* from, u32 unk_01, Word_t from_rtti, Word_t to_rtti, u32 unk_02)>
            (Game_t::Base_Address() + Offset_e::RUNTIME_CAST);

        SKYLIB_ASSERT_SOME(from);

        Word_t from_rtti = Game_t::Base_Address() + From_t::Offset_e::RTTI;
        Word_t to_rtti = Game_t::Base_Address() + To_t::Offset_e::RTTI;
        return reinterpret_cast<To_t*>(runtime_cast(from(), 0, from_rtti, to_rtti, 0));
    }

    template <typename Data_t, typename Value_t>
    static Bool_t Game_t::Data_Has_Value(Data_t* data, Value_t value)
    {
        SKYLIB_ASSERT(data);

        Value_t* values = reinterpret_cast<Value_t*>(data);
        for (size_t idx = 0, end = sizeof(Data_t) / sizeof(Value_t); idx < end; idx += 1) {
            if (values[idx] == value) {
                return true;
            }
        }

        return false;
    }

    template <typename Data_t, typename Value_t>
    static Word_t Game_t::Offset_Of_Value(Data_t* data, Value_t value)
    {
        SKYLIB_ASSERT(data);

        Value_t* values = reinterpret_cast<Value_t*>(data);
        for (size_t idx = 0, end = sizeof(Data_t) / sizeof(Value_t); idx < end; idx += 1) {
            if (values[idx] == value) {
                return static_cast<Word_t>(idx) * sizeof(Value_t);
            }
        }

        return static_cast<Word_t>(~0);
    }

    template <typename Value_t>
    static void Game_t::Log_Value_Offsets(Value_t value, std::string indent)
    {
        Value_t* values = reinterpret_cast<Value_t*>(Base_Address());
        size_t value_count = Base_Address_Size() / sizeof(Value_t);

        SKYLIB_LOG(indent + "Game_t::Log_Value_Offsets");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "value_count: %zu, first_address: %p, last address: %p",
                   value_count, values, values + value_count);

        for (size_t idx = 0, end = value_count; idx < end; idx += 1) {
            if (values[idx] == value) {
                SKYLIB_LOG(indent + SKYLIB_TAB + "0x%8.8X",
                           reinterpret_cast<Word_t>(values + idx) - reinterpret_cast<Word_t>(values));
            }
        }

        SKYLIB_LOG(indent + "}");
    }

}

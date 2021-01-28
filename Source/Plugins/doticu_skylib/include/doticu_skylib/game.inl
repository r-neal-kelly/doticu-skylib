/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/game.h"
#include "doticu_skylib/game_heap.h"

namespace doticu_skylib {

    template <typename T>
    inline some<T*> Game_t::Allocate()
    {
        maybe<Byte_t*> data = Game_Heap_t::Self()->Allocate(sizeof(T));
        SKYLIB_ASSERT(data);
        return reinterpret_cast<T*>(data());
    }

    template <typename T>
    inline some<T*> Game_t::Callocate()
    {
        some<T*> data = Allocate<T>();
        memset(static_cast<void*>(data()), 0, sizeof(T));
        return data;
    }

    template <typename T>
    inline void Game_t::Deallocate(some<T*> data)
    {
        SKYLIB_ASSERT_SOME(data);
        Game_Heap_t::Self()->Deallocate(reinterpret_cast<Byte_t*>(data()));
    }

    template <typename From_t, typename To_t>
    inline maybe<To_t*> Game_t::Runtime_Cast(some<From_t*> from)
    {
        static auto runtime_cast = reinterpret_cast
            <void *(*)(void* from, u32 unk_01, Word_t from_rtti, Word_t to_rtti, u32 unk_02)>
            (Game_t::Base_Address() + Offset_e::RUNTIME_CAST);

        SKYLIB_ASSERT_SOME(from);

        Word_t from_rtti = Game_t::Base_Address() + From_t::Offset_e::RTTI;
        Word_t to_rtti = Game_t::Base_Address() + To_t::Offset_e::RTTI;
        return static_cast<To_t*>(runtime_cast(from(), 0, from_rtti, to_rtti, 0));
    }

}

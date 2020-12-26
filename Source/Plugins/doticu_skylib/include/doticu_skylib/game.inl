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
    inline void Game_t::Deallocate(some<T*> data)
    {
        SKYLIB_ASSERT_SOME(data);
        Game_Heap_t::Self()->Deallocate(reinterpret_cast<Byte_t*>(data()));
    }

}

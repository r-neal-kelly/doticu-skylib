/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/intrinsic.h"

#include "doticu_skylib/game.h"
#include "doticu_skylib/game_heap.h"

namespace doticu_skylib {

    some<Game_Heap_t*> Game_Heap_t::Self()
    {
        static auto self = reinterpret_cast
            <Game_Heap_t*>
            (Game_t::Base_Address() + Offset_e::SELF);

        SKYLIB_ASSERT(self);
        return self;
    }

    maybe<Byte_t*> Game_Heap_t::Allocate(size_t byte_count)
    {
        static auto allocate = reinterpret_cast
            <Byte_t*(*)(Game_Heap_t*, size_t byte_count, size_t alignment, Bool_t do_align)>
            (Game_t::Base_Address() + Offset_e::ALLOCATE);

        return allocate(this, byte_count, 0, false);
    }

    void Game_Heap_t::Deallocate(some<Byte_t*> data)
    {
        static auto deallocate = reinterpret_cast
            <void(*)(Game_Heap_t*, Byte_t* data, Bool_t do_align)>
            (Game_t::Base_Address() + Offset_e::DEALLOCATE);

        SKYLIB_ASSERT_SOME(data);
        deallocate(this, data(), false);
    }

}

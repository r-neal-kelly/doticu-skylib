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

    maybe<Byte_t*> Game_Heap_t::Allocate(size_t byte_count, u32 alignment, Bool_t do_align)
    {
        static auto allocate = reinterpret_cast
            <Byte_t*(*)(Game_Heap_t*, size_t, u32, Bool_t)>
            (Game_t::Base_Address() + Offset_e::ALLOCATE);

        return allocate(this, byte_count, alignment, do_align);
    }

    maybe<Byte_t*> Game_Heap_t::Reallocate(some<Byte_t*> data, size_t new_byte_count, u32 alignment, Bool_t do_align)
    {
        static auto reallocate = reinterpret_cast
            <Byte_t*(*)(Game_Heap_t*, Byte_t*, size_t, u32, Bool_t)>
            (Game_t::Base_Address() + Offset_e::REALLOCATE);

        SKYLIB_ASSERT_SOME(data);
        return reallocate(this, data(), new_byte_count, alignment, do_align);
    }

    void Game_Heap_t::Deallocate(some<Byte_t*> data, Bool_t is_aligned)
    {
        static auto deallocate = reinterpret_cast
            <void(*)(Game_Heap_t*, Byte_t*, Bool_t)>
            (Game_t::Base_Address() + Offset_e::DEALLOCATE);

        SKYLIB_ASSERT_SOME(data);
        deallocate(this, data(), is_aligned);
    }

}

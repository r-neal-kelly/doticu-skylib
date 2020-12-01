/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/collections.h"

#include "doticu_skylib/game.h"

namespace doticu_skylib {

    Bool_t Buffer_Allocator_t::Resize(u32 count)
    {
        auto resize = reinterpret_cast
            <Bool_t(*)(Buffer_Allocator_t*, u32)>
            (Game_t::Base_Address() + static_cast<Word_t>(Offset_e::RESIZE));
        return resize(this, count);
    }

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.h"
#include "doticu_skylib/scrap_array_allocator.h"

namespace doticu_skylib {

    Bool_t Scrap_Array_Allocator_t::Resize(u32 count)
    {
        auto resize = reinterpret_cast
            <Bool_t(*)(Scrap_Array_Allocator_t*, u32)>
            (Game_t::Base_Address() + static_cast<Word_t>(Offset_e::RESIZE));

        return resize(this, count);
    }

}

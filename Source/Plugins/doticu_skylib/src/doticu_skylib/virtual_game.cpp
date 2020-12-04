/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.h"

#include "doticu_skylib/virtual_game.h"

namespace doticu_skylib { namespace Virtual {

    Game_t* Game_t::Self()
    {
        static auto self = *reinterpret_cast
            <Game_t**>
            (doticu_skylib::Game_t::Base_Address() + Offset_e::SELF);
        SKYLIB_ASSERT(self);
        return self;
    }

}}

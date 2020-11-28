/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/utils.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/mod.h"
#include "doticu_skylib/player.h"

namespace doticu_skylib {

    Player_t* Player_t::Self()
    {
        static Player_t* self = static_cast<Player_t*>
            (Game_t::Form(Mod_t::Skyrim(), 0x000014));
        return self;
    }

}

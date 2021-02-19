/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/extra_data.inl"
#include "doticu_skylib/extra_talk_to_player.h"

namespace doticu_skylib {

    some<Extra_Talk_To_Player_t*> Extra_Talk_To_Player_t::Create(Bool_t can_talk_to_player)
    {
        some<Extra_Talk_To_Player_t*> x_talk_to_player = Extra_Data_t::Create<Extra_Talk_To_Player_t>();

        x_talk_to_player->can_talk_to_player = can_talk_to_player;

        return x_talk_to_player;
    }

    void Extra_Talk_To_Player_t::Destroy(some<Extra_Talk_To_Player_t*> x_talk_to_player)
    {
        SKYLIB_ASSERT_SOME(x_talk_to_player);

        Extra_Data_t::Destroy<Extra_Talk_To_Player_t>(x_talk_to_player);
    }

}

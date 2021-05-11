/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game_timer.h"

namespace doticu_skylib {

    void Game_Timer_t::Log(std::string indent) const
    {
        SKYLIB_LOG(indent + "Game_Timer_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "unk_00: %llu", unk_00);
        SKYLIB_LOG(indent + SKYLIB_TAB + "last_performance_count: %u", last_performance_count);
        SKYLIB_LOG(indent + SKYLIB_TAB + "clamp: %f", clamp);
        SKYLIB_LOG(indent + SKYLIB_TAB + "clamp_remainder: %f", clamp_remainder);
        SKYLIB_LOG(indent + SKYLIB_TAB + "delta: %f", delta);
        SKYLIB_LOG(indent + SKYLIB_TAB + "real_time_delta: %f", real_time_delta);
        SKYLIB_LOG(indent + SKYLIB_TAB + "unk_20: %u", unk_20);
        SKYLIB_LOG(indent + SKYLIB_TAB + "total_time: %u", total_time);
        SKYLIB_LOG(indent + SKYLIB_TAB + "unk_28: %f", unk_28);
        SKYLIB_LOG(indent + SKYLIB_TAB + "unk_2C: %u", unk_2C);
        SKYLIB_LOG(indent + SKYLIB_TAB + "unk_30: %u", unk_30);
        SKYLIB_LOG(indent + SKYLIB_TAB + "unk_34: %u", unk_34);
        SKYLIB_LOG(indent + SKYLIB_TAB + "unk_38: %u", unk_38);
        SKYLIB_LOG(indent + SKYLIB_TAB + "unk_39: %u", unk_39);
        SKYLIB_LOG(indent + SKYLIB_TAB + "unk_3A: %s", unk_3A ? "true" : "false");
        SKYLIB_LOG(indent + SKYLIB_TAB + "pad_3B: %u", pad_3B);
        SKYLIB_LOG(indent + SKYLIB_TAB + "pad_3C: %u", pad_3C);

        SKYLIB_LOG(indent + "}");
    }

}

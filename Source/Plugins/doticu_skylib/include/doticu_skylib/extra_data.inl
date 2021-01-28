/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/game.inl"

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    template <typename Extra_t>
    inline some<Extra_t*> Data_x::Create()
    {
        some<Extra_t*> x_data = Game_t::Allocate<Extra_t>();

        Game_t::Write_V_Table(x_data(), Extra_t::Offset_e::V_TABLE);
        x_data->next = none<Data_x*>();

        return x_data;
    }

    template <typename Extra_t>
    inline void Data_x::Destroy(some<Extra_t*> x_data)
    {
        SKYLIB_ASSERT_SOME(x_data);

        static_cast<some<Data_x*>>(x_data)->~Data_x();
        x_data->next = none<Data_x*>();

        Game_t::Deallocate<Extra_t>(x_data);
    }

}

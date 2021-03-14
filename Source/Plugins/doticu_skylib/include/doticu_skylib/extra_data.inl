/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/game.inl"

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    template <typename T>
    inline some<T*> Extra_Data_t::Create()
    {
        some<T*> x_data = Game_t::Allocate<T>();

        Game_t::Write_V_Table(x_data(), T::Offset_e::V_TABLE);
        x_data->next = none<Extra_Data_t*>();

        return x_data;
    }

    template <typename T>
    inline some<T*> Extra_Data_t::Create(const Extra_Data_t& other)
    {
        return T::Create(static_cast<const T&>(other));
    }

    template <typename T>
    inline void Extra_Data_t::Destroy(some<T*> x_data)
    {
        SKYLIB_ASSERT_SOME(x_data);

        x_data->~T();
        x_data->next = none<Extra_Data_t*>();

        Game_t::Deallocate<T>(x_data);
    }

}

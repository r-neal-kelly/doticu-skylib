/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/game.h"

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    template <typename Type_t>
    Type_t* Data_x::Create()
    {
        Type_t* xdata = static_cast<Type_t*>(Heap_Allocate(sizeof(Type_t)));
        memset(xdata, 0, sizeof(Type_t));
        Game_t::Write_V_Table(xdata, Type_t::Offset_e::V_TABLE);
        return xdata;
    }

}

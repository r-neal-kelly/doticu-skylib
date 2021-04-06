/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/package_value_list.h"

namespace doticu_skylib {

    void Package_Value_List_t::Log(std::string indent) const
    {
        SKYLIB_LOG(indent + "Package_Value_List_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "pad_08: %zu", this->pad_08);
        SKYLIB_LOG(indent + SKYLIB_TAB + "value: 0x%X", this->value);
        SKYLIB_LOG(indent + SKYLIB_TAB + "unk_18: 0x%p", this->unk_18);

        SKYLIB_LOG(indent + "}");
    }

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.inl"
#include "doticu_skylib/extra_soul_level.h"

namespace doticu_skylib {

    some<Extra_Soul_Level_t*> Extra_Soul_Level_t::Create()
    {
        some<Extra_Soul_Level_t*> x_soul_level = Extra_Data_t::Create<Extra_Soul_Level_t>();

        x_soul_level->soul_level = Soul_Level_e::EMPTY;
        x_soul_level->pad_11 = 0;
        x_soul_level->pad_12 = 0;
        x_soul_level->pad_14 = 0;

        return x_soul_level;
    }

    some<Extra_Soul_Level_t*> Extra_Soul_Level_t::Create(Soul_Level_e soul_level)
    {
        some<Extra_Soul_Level_t*> x_soul_level = Create();

        x_soul_level->Soul_Level(soul_level);

        return x_soul_level;
    }

    some<Extra_Soul_Level_t*> Extra_Soul_Level_t::Create(const Extra_Soul_Level_t& other)
    {
        some<Extra_Soul_Level_t*> x_soul_level = Extra_Data_t::Create<Extra_Soul_Level_t>();

        x_soul_level->soul_level = other.soul_level;
        x_soul_level->pad_11 = other.pad_11;
        x_soul_level->pad_12 = other.pad_12;
        x_soul_level->pad_14 = other.pad_14;

        return x_soul_level;
    }

    void Extra_Soul_Level_t::Destroy(some<Extra_Soul_Level_t*> x_soul_level)
    {
        SKYLIB_ASSERT_SOME(x_soul_level);

        Extra_Data_t::Destroy<Extra_Soul_Level_t>(x_soul_level);
    }

    Soul_Level_e Extra_Soul_Level_t::Soul_Level()
    {
        return this->soul_level;
    }

    void Extra_Soul_Level_t::Soul_Level(Soul_Level_e soul_level)
    {
        this->soul_level = soul_level;
    }

    void Extra_Soul_Level_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Extra_Soul_Level_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "soul_level: %s", this->soul_level.As_String()());

        SKYLIB_LOG(indent + "}");
    }

}

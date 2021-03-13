/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.inl"
#include "doticu_skylib/extra_temper_level.h"

namespace doticu_skylib {

    some<Extra_Temper_Level_t*> Extra_Temper_Level_t::Create()
    {
        some<Extra_Temper_Level_t*> x_temper_level = Extra_Data_t::Create<Extra_Temper_Level_t>();

        x_temper_level->temper_level = Temper_Level_e::STANDARD;
        x_temper_level->pad_14 = 0;

        return x_temper_level;
    }

    some<Extra_Temper_Level_t*> Extra_Temper_Level_t::Create(Temper_Level_t temper_level)
    {
        some<Extra_Temper_Level_t*> x_temper_level = Create();

        x_temper_level->Temper_Level(temper_level);

        return x_temper_level;
    }

    some<Extra_Temper_Level_t*> Extra_Temper_Level_t::Create(const Extra_Temper_Level_t& other)
    {
        some<Extra_Temper_Level_t*> x_temper_level = Extra_Data_t::Create<Extra_Temper_Level_t>();

        x_temper_level->temper_level = other.temper_level;
        x_temper_level->pad_14 = other.pad_14;

        return x_temper_level;
    }

    void Extra_Temper_Level_t::Destroy(some<Extra_Temper_Level_t*> x_temper_level)
    {
        SKYLIB_ASSERT_SOME(x_temper_level);

        Extra_Data_t::Destroy<Extra_Temper_Level_t>(x_temper_level);
    }

    Temper_Level_t Extra_Temper_Level_t::Temper_Level() const
    {
        return this->temper_level;
    }

    void Extra_Temper_Level_t::Temper_Level(Temper_Level_t temper_level)
    {
        this->temper_level = temper_level;
    }

    void Extra_Temper_Level_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Extra_Temper_Level_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "temper_level: %s", this->temper_level.As_String());

        SKYLIB_LOG(indent + "}");
    }

}

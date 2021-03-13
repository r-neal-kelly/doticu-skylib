/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.inl"
#include "doticu_skylib/extra_poison.h"
#include "doticu_skylib/potion.h"

namespace doticu_skylib {

    some<Extra_Poison_t*> Extra_Poison_t::Create()
    {
        some<Extra_Poison_t*> x_poison = Extra_Data_t::Create<Extra_Poison_t>();

        x_poison->poison = none<Potion_t*>();
        x_poison->count = 0;
        x_poison->pad_1C = 0;

        return x_poison;
    }

    some<Extra_Poison_t*> Extra_Poison_t::Create(maybe<Potion_t*> poison, u32 count)
    {
        some<Extra_Poison_t*> x_poison = Create();

        x_poison->poison = poison;
        x_poison->count = count;

        return x_poison;
    }

    some<Extra_Poison_t*> Extra_Poison_t::Create(const Extra_Poison_t& other)
    {
        some<Extra_Poison_t*> x_poison = Extra_Data_t::Create<Extra_Poison_t>();

        x_poison->poison = other.poison;
        x_poison->count = other.count;
        x_poison->pad_1C = other.pad_1C;

        return x_poison;
    }

    void Extra_Poison_t::Destroy(some<Extra_Poison_t*> x_poison)
    {
        SKYLIB_ASSERT_SOME(x_poison);

        Extra_Data_t::Destroy<Extra_Poison_t>(x_poison);
    }

    maybe<Potion_t*> Extra_Poison_t::Poison()
    {
        return this->poison;
    }

    void Extra_Poison_t::Poison(maybe<Potion_t*> poison)
    {
        this->poison = poison;
    }

    void Extra_Poison_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Extra_Poison_t::Log");
        SKYLIB_LOG(indent + "{");

        if (this->poison) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "poison:");
            this->poison->Log(indent + SKYLIB_TAB + SKYLIB_TAB);
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "poison: (none)");
        }
        SKYLIB_LOG(indent + SKYLIB_TAB + "count: %u", this->count);

        SKYLIB_LOG(indent + "}");
    }

}

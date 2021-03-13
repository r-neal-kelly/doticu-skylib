/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enchantment.h"
#include "doticu_skylib/extra_data.inl"
#include "doticu_skylib/extra_enchantment.h"

namespace doticu_skylib {

    some<Extra_Enchantment_t*> Extra_Enchantment_t::Create()
    {
        some<Extra_Enchantment_t*> x_enchantment = Extra_Data_t::Create<Extra_Enchantment_t>();

        x_enchantment->enchantment = none<Enchantment_t*>();
        x_enchantment->max_charge = 0;
        x_enchantment->do_remove_on_unequip = false;
        x_enchantment->pad_1B = 0;
        x_enchantment->pad_1C = 0;

        return x_enchantment;
    }

    some<Extra_Enchantment_t*> Extra_Enchantment_t::Create(maybe<Enchantment_t*> enchantment,
                                                           u16 max_charge,
                                                           Bool_t do_remove_on_unequip)
    {
        some<Extra_Enchantment_t*> x_enchantment = Create();

        x_enchantment->enchantment = enchantment;
        x_enchantment->max_charge = max_charge;
        x_enchantment->do_remove_on_unequip = do_remove_on_unequip;

        return x_enchantment;
    }

    some<Extra_Enchantment_t*> Extra_Enchantment_t::Create(const Extra_Enchantment_t& other)
    {
        some<Extra_Enchantment_t*> x_enchantment = Extra_Data_t::Create<Extra_Enchantment_t>();

        x_enchantment->enchantment = other.enchantment;
        x_enchantment->max_charge = other.max_charge;
        x_enchantment->do_remove_on_unequip = other.do_remove_on_unequip;
        x_enchantment->pad_1B = other.pad_1B;
        x_enchantment->pad_1C = other.pad_1C;

        return x_enchantment;
    }

    void Extra_Enchantment_t::Destroy(some<Extra_Enchantment_t*> x_enchantment)
    {
        SKYLIB_ASSERT_SOME(x_enchantment);

        Extra_Data_t::Destroy<Extra_Enchantment_t>(x_enchantment);
    }

    maybe<Enchantment_t*> Extra_Enchantment_t::Enchantment()
    {
        return this->enchantment;
    }

    void Extra_Enchantment_t::Enchantment(maybe<Enchantment_t*> enchantment)
    {
        this->enchantment = enchantment;
    }

    void Extra_Enchantment_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Extra_Enchantment_t::Log");
        SKYLIB_LOG(indent + "{");

        if (this->enchantment) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "enchantment:");
            this->enchantment->Log(indent + SKYLIB_TAB + SKYLIB_TAB);
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "enchantment: (none)");
        }
        SKYLIB_LOG(indent + SKYLIB_TAB + "max_charge: %u", this->max_charge);
        SKYLIB_LOG(indent + SKYLIB_TAB + "do_remove_on_unequip: %s", this->do_remove_on_unequip ? "true" : "false");

        SKYLIB_LOG(indent + "}");
    }

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/extra_charge.h"
#include "doticu_skylib/extra_data.inl"
#include "doticu_skylib/math.h"

namespace doticu_skylib {

    some<Extra_Charge_t*> Extra_Charge_t::Create()
    {
        some<Extra_Charge_t*> x_charge = Extra_Data_t::Create<Extra_Charge_t>();

        x_charge->charge = 0.0f;
        x_charge->pad_14 = 0;

        return x_charge;
    }

    some<Extra_Charge_t*> Extra_Charge_t::Create(Float_t charge)
    {
        some<Extra_Charge_t*> x_charge = Create();

        x_charge->Charge(charge);

        return x_charge;
    }

    some<Extra_Charge_t*> Extra_Charge_t::Create(const Extra_Charge_t& other)
    {
        some<Extra_Charge_t*> x_charge = Extra_Data_t::Create<Extra_Charge_t>();

        x_charge->charge = other.charge;
        x_charge->pad_14 = other.pad_14;

        return x_charge;
    }

    void Extra_Charge_t::Destroy(some<Extra_Charge_t*> x_charge)
    {
        SKYLIB_ASSERT_SOME(x_charge);

        Extra_Data_t::Destroy<Extra_Charge_t>(x_charge);
    }

    Float_t Extra_Charge_t::Charge()
    {
        if (this->charge < 0.0f) {
            this->charge = 0.0f;
        }
        return this->charge;
    }

    void Extra_Charge_t::Charge(Float_t charge)
    {
        this->charge = abs(charge);
    }

    void Extra_Charge_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Extra_Charge_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "charge: %.8f", Charge());

        SKYLIB_LOG(indent + "}");
    }

}

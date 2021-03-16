/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/extra_cannot_wear.h"
#include "doticu_skylib/extra_data.inl"

namespace doticu_skylib {

    some<Extra_Cannot_Wear_t*> Extra_Cannot_Wear_t::Create()
    {
        some<Extra_Cannot_Wear_t*> x_cannot_wear = Extra_Data_t::Create<Extra_Cannot_Wear_t>();
        return x_cannot_wear;
    }

    some<Extra_Cannot_Wear_t*> Extra_Cannot_Wear_t::Create(const Extra_Cannot_Wear_t& other)
    {
        return Create();
    }

    void Extra_Cannot_Wear_t::Destroy(some<Extra_Cannot_Wear_t*> x_cannot_wear)
    {
        SKYLIB_ASSERT_SOME(x_cannot_wear);

        Extra_Data_t::Destroy<Extra_Cannot_Wear_t>(x_cannot_wear);
    }

    void Extra_Cannot_Wear_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Extra_Cannot_Wear_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + "}");
    }

}

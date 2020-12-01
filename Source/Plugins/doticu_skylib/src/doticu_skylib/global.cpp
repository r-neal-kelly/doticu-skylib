/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/global.h"

namespace doticu_skylib {

    Bool_t Global_t::Bool()
    {
        return static_cast<u32>(value) != 0;
    }

    Float_t Global_t::Float()
    {
        return value;
    }

    u16 Global_t::Short()
    {
        return static_cast<u16>(value);
    }

    u32 Global_t::Long()
    {
        return static_cast<u32>(value);
    }

    void Global_t::Bool(Bool_t value)
    {
        this->value = value ? 1 : 0;
    }

    void Global_t::Float(Float_t value)
    {
        this->value = value;
    }

    void Global_t::Short(u16 value)
    {
        this->value = static_cast<Float_t>(value);
    }

    void Global_t::Long(u32 value)
    {
        this->value = static_cast<Float_t>(value);
    }

}

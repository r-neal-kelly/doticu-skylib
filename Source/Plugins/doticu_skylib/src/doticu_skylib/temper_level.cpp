/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/temper_level.h"

namespace doticu_skylib {

    Temper_Level_t::Temper_Level_t() :
        value(Temper_Level_e::To_Float(Temper_Level_e::STANDARD))
    {
    }

    Temper_Level_t::Temper_Level_t(value_type temper_level) :
        value(Temper_Level_e::From_Float(temper_level).As_Float())
    {
    }

    Temper_Level_t::Temper_Level_t(Temper_Level_e temper_level) :
        value(temper_level.As_Float())
    {
    }

    Temper_Level_t::Temper_Level_t(const Temper_Level_t& other) :
        value(other.As_Float())
    {
    }

    Temper_Level_t::Temper_Level_t(Temper_Level_t&& other) noexcept :
        value(other.As_Float())
    {
    }

    Temper_Level_t& Temper_Level_t::operator =(const Temper_Level_t& other)
    {
        if (this != std::addressof(other)) {
            this->value = other.As_Float();
        }
        return *this;
    }

    Temper_Level_t& Temper_Level_t::operator =(Temper_Level_t&& other) noexcept
    {
        if (this != std::addressof(other)) {
            this->value = other.As_Float();
        }
        return *this;
    }

    Temper_Level_t::~Temper_Level_t()
    {
    }

    Temper_Level_e Temper_Level_t::As_Enum() const
    {
        return Temper_Level_e::From_Float(this->value);
    }

    Float_t Temper_Level_t::As_Float() const
    {
        return As_Enum().As_Float();
    }

    some<const char*> Temper_Level_t::As_String() const
    {
        return As_Enum().As_String();
    }

    Float_t Temper_Level_t::Raw_Float() const
    {
        return this->value;
    }

}

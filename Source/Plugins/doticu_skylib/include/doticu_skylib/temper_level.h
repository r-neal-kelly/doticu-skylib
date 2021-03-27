/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_temper_level.h"
#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    using Raw_Temper_Level_t = Float_t;

    class Temper_Level_t
    {
    public:
        using value_type = Raw_Temper_Level_t;

    protected:
        value_type value;

    public:
        Temper_Level_t();
        Temper_Level_t(value_type temper_level);
        Temper_Level_t(Temper_Level_e temper_level);
        Temper_Level_t(const Temper_Level_t& other);
        Temper_Level_t(Temper_Level_t&& other) noexcept;
        Temper_Level_t& operator =(const Temper_Level_t& other);
        Temper_Level_t& operator =(Temper_Level_t&& other) noexcept;
        ~Temper_Level_t();

    public:
        Temper_Level_e      As_Enum() const;
        Float_t             As_Float() const;
        some<const char*>   As_String() const;
        Float_t             Raw_Float() const;
    };

}

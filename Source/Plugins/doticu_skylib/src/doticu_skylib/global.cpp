/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <iomanip>
#include <sstream>

#include "doticu_skylib/global.inl"

namespace doticu_skylib {

    Bool_t  Global_t::Bool()                { return this->value != 0.0f; }
    void    Global_t::Bool(Bool_t value)    { this->value = static_cast<Float_t>(value); }

    Int_t   Global_t::Int()                 { return static_cast<Int_t>(this->value); }
    void    Global_t::Int(Int_t value)      { this->value = static_cast<Float_t>(value); }

    Float_t Global_t::Float()               { return this->value; }
    void    Global_t::Float(Float_t value)  { this->value = value; }

    Int_t Global_t::Percent()
    {
        Int_t percent = this->As<Int_t>();
        if (percent < 0) {
            this->As<u16>(0);
            return 0;
        } else if (percent > 100) {
            this->As<u16>(100);
            return 100;
        } else {
            return percent;
        }
    }

    void Global_t::Percent(Int_t value)
    {
        if (value < 0) {
            this->As<u16>(0);
        } else if (value > 100) {
            this->As<u16>(100);
        } else {
            this->As<u16>(value);
        }
    }

    std::string Global_t::Float_String(size_t precision)
    {
        std::ostringstream oss;
        oss << std::setprecision(precision) << Float();
        return oss.str();
    }

}

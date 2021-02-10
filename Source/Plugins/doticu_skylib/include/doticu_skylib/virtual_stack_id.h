/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe_numeric.h"

namespace doticu_skylib { namespace Virtual {

    using Raw_Stack_ID_t = u32;

    class Stack_ID_t
    {
    public:
        using value_type = Raw_Stack_ID_t;
        
    public:
        static constexpr value_type NONE_VALUE = static_cast<value_type>(~0);

    protected:
        value_type value;

    public:
        Stack_ID_t();
        Stack_ID_t(value_type value);

    public:
        operator            value_type() const;
        explicit operator   Bool_t() const;
        Bool_t operator     !() const;
    };

}}

namespace doticu_skylib {

    template <>
    inline Bool_t Is_Equal(const none<Virtual::Stack_ID_t>& a, const Virtual::Stack_ID_t& b)
    {
        return !b;
    }

    template <>
    class none<Virtual::Stack_ID_t> : public none_numeric<Virtual::Stack_ID_t>
    {
    public:
        none() : none_numeric(Virtual::Stack_ID_t::NONE_VALUE) {}
    };

    template <>
    class maybe<Virtual::Stack_ID_t> : public maybe_numeric<Virtual::Stack_ID_t>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<Virtual::Stack_ID_t> : public some_numeric<Virtual::Stack_ID_t>
    {
    public:
        using some_numeric::some_numeric;
    };

}

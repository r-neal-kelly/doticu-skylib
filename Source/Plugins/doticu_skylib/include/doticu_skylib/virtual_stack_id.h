/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/math.h"
#include "doticu_skylib/numeric.h"

namespace doticu_skylib { namespace Virtual {

    using Raw_Stack_ID_t = u32;

    class Stack_ID_t_data :
        public Numeric_Data_t<Raw_Stack_ID_t>
    {
    public:
        static constexpr value_type _NONE_  = static_cast<value_type>(~0);

    public:
        static Bool_t Is_Valid(value_type value)
        {
            return value != _NONE_;
        }
    };

    class Stack_ID_t :
        public Numeric_t<Stack_ID_t_data>
    {
    public:
        using Numeric_t::Numeric_t;
    };

}}

namespace doticu_skylib {

    template <>
    class none<Virtual::Stack_ID_t> :
        public none_numeric<Virtual::Stack_ID_t>
    {
    public:
        using none_numeric::none_numeric;
    };

    template <>
    class maybe<Virtual::Stack_ID_t> :
        public maybe_numeric<Virtual::Stack_ID_t>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<Virtual::Stack_ID_t> :
        public some_numeric<Virtual::Stack_ID_t>
    {
    public:
        using some_numeric::some_numeric;
    };

}

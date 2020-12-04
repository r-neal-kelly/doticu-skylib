/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Complex_Branch_e : public Enum_t<u8>
    {
    public:
        static constexpr size_t MAX = 2;
        enum : u8
        {
            PLAYER  = 0,
            COMMAND = 1,
        };
        using Enum_t::Enum_t;
    };

    class Simple_Branch_e : public Enum_t<u8>
    {
    public:
        static constexpr size_t MAX = 6;
        enum : u8
        {
            SCENE       = 2,
            COMBAT      = 3,
            FAVORS      = 4,
            DETECTION   = 5,
            SERVICE     = 6,
            MISC        = 7,
        };
        using Enum_t::Enum_t;
    };

    class Branch_Type_e :
        public Complex_Branch_e,
        public Simple_Branch_e
    {
    public:
        static constexpr size_t MAX = 8;
        using Complex_Branch_e::Complex_Branch_e;
    };

}

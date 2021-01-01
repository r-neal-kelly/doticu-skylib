/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Logic_Gate_e : public Enum_t<Word_t>
    {
    public:
        enum : value_type
        {
            NONE = static_cast<value_type>(-1),

            NOT = 0,

            OR,
            AND,
            XOR,
            NOR,
            NAND,
            XNOR,

            _END_,
        };

        static constexpr const char* NONE_STRING = "NONE";
        static constexpr const char* NOT_STRING = "!";
        static constexpr const char* OR_STRING = "|";
        static constexpr const char* AND_STRING = "&";
        static constexpr const char* XOR_STRING = "^";
        static constexpr const char* NOR_STRING = "!|";
        static constexpr const char* NAND_STRING = "!&";
        static constexpr const char* XNOR_STRING = "!^";

    public:
        using Enum_t::Enum_t;

        static some<const char*>    To_String(Logic_Gate_e logic_gate);
        static Logic_Gate_e         From_String(maybe<const char*> logic_gate);
    };

}

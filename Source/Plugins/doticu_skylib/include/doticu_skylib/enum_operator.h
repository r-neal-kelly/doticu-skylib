/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Operator_e : public Enum_t<Word_t>
    {
    public:
        enum : value_type
        {
            NONE = static_cast<value_type>(-1),

            EQUAL_TO,
            LESS_THAN,
            GREATER_THAN,

            _END_,
        };

        static constexpr const char* NONE_STRING = "";
        static constexpr const char* EQUAL_TO_STRING = "==";
        static constexpr const char* LESS_THAN_STRING = "<";
        static constexpr const char* GREATER_THAN_STRING = ">";

    public:
        using Enum_t::Enum_t;

        static some<const char*>    To_String(Operator_e operator_e);
        static Operator_e           From_String(maybe<const char*> operator_cstr);
    };

}

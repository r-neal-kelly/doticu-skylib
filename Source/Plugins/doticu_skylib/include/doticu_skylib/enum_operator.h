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

            EQUAL_TO = 0,
            NOT_EQUAL_TO,
            LESS_THAN,
            GREATER_THAN,
            LESS_THAN_OR_EQUAL_TO,
            GREATER_THAN_OR_EQUAL_TO,

            LOGICAL_NOT,
            LOGICAL_AND,
            LOGICAL_OR,

            BITWISE_NOT,
            BITWISE_AND,
            BITWISE_OR,
            BITWISE_XOR,
            BITWISE_LEFT_SHIFT,
            BITWISE_RIGHT_SHIFT,

            REFERENCE,
            DEREFERENCE,

            ELLIPSIS,

            _END_,
        };

        static constexpr const char* NONE_STRING = "";

        static constexpr const char* EQUAL_TO_STRING = "==";
        static constexpr const char* NOT_EQUAL_TO_STRING = "!=";
        static constexpr const char* LESS_THAN_STRING = "<";
        static constexpr const char* GREATER_THAN_STRING = ">";
        static constexpr const char* LESS_THAN_OR_EQUAL_TO_STRING = "<=";
        static constexpr const char* GREATER_THAN_OR_EQUAL_TO_STRING = ">=";

        static constexpr const char* LOGICAL_NOT_STRING = "!";
        static constexpr const char* LOGICAL_AND_STRING = "&&";
        static constexpr const char* LOGICAL_OR_STRING = "||";

        static constexpr const char* BITWISE_NOT_STRING = "~";
        static constexpr const char* BITWISE_AND_STRING = "&";
        static constexpr const char* BITWISE_OR_STRING = "|";
        static constexpr const char* BITWISE_XOR_STRING = "^";
        static constexpr const char* BITWISE_LEFT_SHIFT_STRING = "<<";
        static constexpr const char* BITWISE_RIGHT_SHIFT_STRING = ">>";

        static constexpr const char* REFERENCE_STRING = ".";
        static constexpr const char* DEREFERENCE_STRING = "->";

        static constexpr const char* ELLIPSIS_STRING = "...";

    public:
        using Enum_t::Enum_t;

        static some<const char*>    To_String(Operator_e operator_e);
        static Operator_e           From_String(maybe<const char*> operator_cstr);
    };

}

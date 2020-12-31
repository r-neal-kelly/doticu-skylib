/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cstring.h"

#include "doticu_skylib/enum_operator.h"

namespace doticu_skylib {

    some<const char*> Operator_e::To_String(Operator_e operator_e)
    {
        if (operator_e == Operator_e::EQUAL_TO) {
            return EQUAL_TO_STRING;
        } else if (operator_e == Operator_e::LESS_THAN) {
            return LESS_THAN_STRING;
        } else if (operator_e == Operator_e::GREATER_THAN) {
            return GREATER_THAN_STRING;
        } else {
            return NONE_STRING;
        }
    }

    Operator_e Operator_e::From_String(maybe<const char*> operator_cstr)
    {
        if (operator_cstr) {
            const char* str = CString_t::Seek_After(operator_cstr(), ' ', 24);
            if (CString_t::Starts_With(EQUAL_TO_STRING, str, true)) {
                return Operator_e::EQUAL_TO;
            } else if (CString_t::Starts_With(LESS_THAN_STRING, str, true)) {
                return Operator_e::LESS_THAN;
            } else if (CString_t::Starts_With(GREATER_THAN_STRING, str, true)) {
                return Operator_e::GREATER_THAN;
            } else {
                return Operator_e::NONE;
            }
        } else {
            return Operator_e::NONE;
        }
    }

}

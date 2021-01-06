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
        } else if (operator_e == Operator_e::NOT_EQUAL_TO) {
            return NOT_EQUAL_TO_STRING;
        } else if (operator_e == Operator_e::LESS_THAN) {
            return LESS_THAN_STRING;
        } else if (operator_e == Operator_e::GREATER_THAN) {
            return GREATER_THAN_STRING;
        } else if (operator_e == Operator_e::LESS_THAN_OR_EQUAL_TO) {
            return LESS_THAN_OR_EQUAL_TO_STRING;
        } else if (operator_e == Operator_e::GREATER_THAN_OR_EQUAL_TO) {
            return GREATER_THAN_OR_EQUAL_TO_STRING;

        } else if (operator_e == Operator_e::LOGICAL_NOT) {
            return LOGICAL_NOT_STRING;
        } else if (operator_e == Operator_e::LOGICAL_AND) {
            return LOGICAL_AND_STRING;
        } else if (operator_e == Operator_e::LOGICAL_OR) {
            return LOGICAL_OR_STRING;

        } else if (operator_e == Operator_e::BITWISE_NOT) {
            return BITWISE_NOT_STRING;
        } else if (operator_e == Operator_e::BITWISE_AND) {
            return BITWISE_AND_STRING;
        } else if (operator_e == Operator_e::BITWISE_OR) {
            return BITWISE_OR_STRING;
        } else if (operator_e == Operator_e::BITWISE_XOR) {
            return BITWISE_XOR_STRING;
        } else if (operator_e == Operator_e::BITWISE_LEFT_SHIFT) {
            return BITWISE_LEFT_SHIFT_STRING;
        } else if (operator_e == Operator_e::BITWISE_RIGHT_SHIFT) {
            return BITWISE_RIGHT_SHIFT_STRING;

        } else if (operator_e == Operator_e::REFERENCE) {
            return REFERENCE_STRING;
        } else if (operator_e == Operator_e::DEREFERENCE) {
            return DEREFERENCE_STRING;

        } else if (operator_e == Operator_e::ELLIPSIS) {
            return ELLIPSIS_STRING;

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
            } else if (CString_t::Starts_With(NOT_EQUAL_TO_STRING, str, true)) {
                return Operator_e::NOT_EQUAL_TO;
            } else if (CString_t::Starts_With(LESS_THAN_STRING, str, true)) {
                return Operator_e::LESS_THAN;
            } else if (CString_t::Starts_With(GREATER_THAN_STRING, str, true)) {
                return Operator_e::GREATER_THAN;
            } else if (CString_t::Starts_With(LESS_THAN_OR_EQUAL_TO_STRING, str, true)) {
                return Operator_e::LESS_THAN_OR_EQUAL_TO;
            } else if (CString_t::Starts_With(GREATER_THAN_OR_EQUAL_TO_STRING, str, true)) {
                return Operator_e::GREATER_THAN_OR_EQUAL_TO;

            } else if (CString_t::Starts_With(LOGICAL_NOT_STRING, str, true)) {
                return Operator_e::LOGICAL_NOT;
            } else if (CString_t::Starts_With(LOGICAL_AND_STRING, str, true)) {
                return Operator_e::LOGICAL_AND;
            } else if (CString_t::Starts_With(LOGICAL_OR_STRING, str, true)) {
                return Operator_e::LOGICAL_OR;

            } else if (CString_t::Starts_With(BITWISE_NOT_STRING, str, true)) {
                return Operator_e::BITWISE_NOT;
            } else if (CString_t::Starts_With(BITWISE_AND_STRING, str, true)) {
                return Operator_e::BITWISE_AND;
            } else if (CString_t::Starts_With(BITWISE_OR_STRING, str, true)) {
                return Operator_e::BITWISE_OR;
            } else if (CString_t::Starts_With(BITWISE_XOR_STRING, str, true)) {
                return Operator_e::BITWISE_XOR;
            } else if (CString_t::Starts_With(BITWISE_LEFT_SHIFT_STRING, str, true)) {
                return Operator_e::BITWISE_LEFT_SHIFT;
            } else if (CString_t::Starts_With(BITWISE_RIGHT_SHIFT_STRING, str, true)) {
                return Operator_e::BITWISE_RIGHT_SHIFT;

            } else if (CString_t::Starts_With(REFERENCE_STRING, str, true)) {
                return Operator_e::REFERENCE;
            } else if (CString_t::Starts_With(DEREFERENCE_STRING, str, true)) {
                return Operator_e::DEREFERENCE;

            } else if (CString_t::Starts_With(ELLIPSIS_STRING, str, true)) {
                return Operator_e::ELLIPSIS;

            } else {
                return Operator_e::NONE;
            }
        } else {
            return Operator_e::NONE;
        }
    }

}

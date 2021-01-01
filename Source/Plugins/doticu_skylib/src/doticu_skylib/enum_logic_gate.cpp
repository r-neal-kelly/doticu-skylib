/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cstring.h"

#include "doticu_skylib/enum_logic_gate.h"

namespace doticu_skylib {

    some<const char*> Logic_Gate_e::To_String(Logic_Gate_e logic_gate)
    {
        if (logic_gate == Logic_Gate_e::NOT) {
            return NOT_STRING;
        } else if (logic_gate == Logic_Gate_e::OR) {
            return OR_STRING;
        } else if (logic_gate == Logic_Gate_e::AND) {
            return AND_STRING;
        } else if (logic_gate == Logic_Gate_e::XOR) {
            return XOR_STRING;
        } else if (logic_gate == Logic_Gate_e::NOR) {
            return NOR_STRING;
        } else if (logic_gate == Logic_Gate_e::NAND) {
            return NAND_STRING;
        } else if (logic_gate == Logic_Gate_e::XNOR) {
            return XNOR_STRING;
        } else {
            return NONE_STRING;
        }
    }

    Logic_Gate_e Logic_Gate_e::From_String(maybe<const char*> logic_gate)
    {
        if (logic_gate) {
            const char* str = CString_t::Seek_After(logic_gate(), ' ', 24);
            if (CString_t::Starts_With(NOT_STRING, str, true)) {
                return Logic_Gate_e::NOT;
            } else if (CString_t::Starts_With(OR_STRING, str, true)) {
                return Logic_Gate_e::OR;
            } else if (CString_t::Starts_With(AND_STRING, str, true)) {
                return Logic_Gate_e::AND;
            } else if (CString_t::Starts_With(XOR_STRING, str, true)) {
                return Logic_Gate_e::XOR;
            } else if (CString_t::Starts_With(NOR_STRING, str, true)) {
                return Logic_Gate_e::NOR;
            } else if (CString_t::Starts_With(NAND_STRING, str, true)) {
                return Logic_Gate_e::NAND;
            } else if (CString_t::Starts_With(XNOR_STRING, str, true)) {
                return Logic_Gate_e::XNOR;
            } else {
                return Logic_Gate_e::NONE;
            }
        } else {
            return Logic_Gate_e::NONE;
        }
    }

}

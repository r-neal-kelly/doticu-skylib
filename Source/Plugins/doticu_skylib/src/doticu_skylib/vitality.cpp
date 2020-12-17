/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cstring.h"

#include "doticu_skylib/vitality.h"

namespace doticu_skylib {

    some<const char*> Vitality_e::To_String(Vitality_e vitality)
    {
        if (vitality == Vitality_e::MORTAL) {
            return MORTAL_STRING;
        } else if (vitality == Vitality_e::PROTECTED) {
            return PROTECTED_STRING;
        } else if (vitality == Vitality_e::ESSENTIAL) {
            return ESSENTIAL_STRING;
        } else if (vitality == Vitality_e::INVULNERABLE) {
            return INVULNERABLE_STRING;
        } else {
            return NONE_STRING;
        }
    }

    Vitality_e Vitality_e::From_String(some<const char*> vitality)
    {
        SKYLIB_ASSERT_SOME(vitality);

        char* input = const_cast<char*>(vitality());
        while (*input == ' ') {
            input += 1;
        }

        if (CString_t::Starts_With(MORTAL_STRING, input, true)) {
            return Vitality_e::MORTAL;
        } else if (CString_t::Starts_With(PROTECTED_STRING, input, true)) {
            return Vitality_e::PROTECTED;
        } else if (CString_t::Starts_With(ESSENTIAL_STRING, input, true)) {
            return Vitality_e::ESSENTIAL;
        } else if (CString_t::Starts_With(INVULNERABLE_STRING, input, true)) {
            return Vitality_e::INVULNERABLE;
        } else {
            return Vitality_e::NONE;
        }
    }

}

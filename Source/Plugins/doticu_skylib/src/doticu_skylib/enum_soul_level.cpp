/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cstring.h"

#include "doticu_skylib/enum_soul_level.h"

namespace doticu_skylib {

    some<const char*> Soul_Level_e::To_String(Soul_Level_e soul_level_e)
    {
        if (soul_level_e == Soul_Level_e::PETTY) {
            return PETTY_STRING;
        } else if (soul_level_e == Soul_Level_e::LESSER) {
            return LESSER_STRING;
        } else if (soul_level_e == Soul_Level_e::COMMON) {
            return COMMON_STRING;
        } else if (soul_level_e == Soul_Level_e::GREATER) {
            return GREATER_STRING;
        } else if (soul_level_e == Soul_Level_e::GRAND) {
            return GRAND_STRING;

        } else {
            return NONE_STRING;
        }
    }

    Soul_Level_e Soul_Level_e::From_String(maybe<const char*> soul_level_cstr)
    {
        if (soul_level_cstr) {
            if (CString_t::Starts_With(PETTY_STRING, soul_level_cstr(), true)) {
                return Soul_Level_e::PETTY;
            } else if (CString_t::Starts_With(LESSER_STRING, soul_level_cstr(), true)) {
                return Soul_Level_e::LESSER;
            } else if (CString_t::Starts_With(COMMON_STRING, soul_level_cstr(), true)) {
                return Soul_Level_e::COMMON;
            } else if (CString_t::Starts_With(GREATER_STRING, soul_level_cstr(), true)) {
                return Soul_Level_e::GREATER;
            } else if (CString_t::Starts_With(GRAND_STRING, soul_level_cstr(), true)) {
                return Soul_Level_e::GRAND;

            } else {
                return Soul_Level_e::NONE;
            }
        } else {
            return Soul_Level_e::NONE;
        }
    }

}

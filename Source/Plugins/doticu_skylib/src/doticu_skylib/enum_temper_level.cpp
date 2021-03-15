/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/cstring.h"
#include "doticu_skylib/enum_temper_level.h"

namespace doticu_skylib {

    some<const Float_t*> Temper_Level_e::Floats()
    {
        static const Float_t floats[_TOTAL_] =
        {
            1.0f, // STANDARD
            1.1f, // FINE
            1.2f, // SUPERIOR
            1.3f, // EXQUISITE
            1.4f, // FLAWLESS
            1.5f, // EPIC
            1.6f, // LEGENDARY
        };

        return floats;
    }

    Float_t Temper_Level_e::To_Float(Temper_Level_e temper_level)
    {
        if (temper_level) {
            return Floats()[temper_level];
        } else {
            return Floats()[Temper_Level_e::STANDARD];
        }
    }

    Temper_Level_e Temper_Level_e::From_Float(Float_t temper_level)
    {
        some<const Float_t*> floats = Floats();
        for (size_t begin = 0, idx = _TOTAL_; idx-- > begin;) {
            if (temper_level >= floats[idx]) {
                return static_cast<Temper_Level_e::value_type>(idx);
            }
        }
        return Temper_Level_e::STANDARD;
    }

    some<const char* const*> Temper_Level_e::Strings()
    {
        static const char* const strings[_TOTAL_] =
        {
            SKYLIB_ENUM_TO_STRING(STANDARD),
            SKYLIB_ENUM_TO_STRING(FINE),
            SKYLIB_ENUM_TO_STRING(SUPERIOR),
            SKYLIB_ENUM_TO_STRING(EXQUISITE),
            SKYLIB_ENUM_TO_STRING(FLAWLESS),
            SKYLIB_ENUM_TO_STRING(EPIC),
            SKYLIB_ENUM_TO_STRING(LEGENDARY),
        };

        return strings;
    }

    some<const char*> Temper_Level_e::To_String(Temper_Level_e temper_level)
    {
        if (temper_level) {
            return Strings()[temper_level];
        } else {
            return "NONE";
        }
    }

    Temper_Level_e Temper_Level_e::From_String(maybe<const char*> temper_level)
    {
        if (temper_level) {
            some<const char* const*> strings = Strings();
            for (size_t idx = 0, end = _TOTAL_; idx < end; idx += 1) {
                some<const char*> string = strings[idx];
                if (CString_t::Is_Same(string(), temper_level(), true)) {
                    return static_cast<Temper_Level_e::value_type>(idx);
                }
            }
            return _NONE_;
        } else {
            return _NONE_;
        }
    }

    Float_t Temper_Level_e::As_Float()
    {
        return To_Float(*this);
    }

    some<const char*> Temper_Level_e::As_String()
    {
        return To_String(*this);
    }

    Temper_Level_e::operator Bool_t() const
    {
        return this->value < _TOTAL_;
    }

}

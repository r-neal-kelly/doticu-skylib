/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/virtual_class.h"

namespace doticu_skylib {

    some<const char* const*> Script_Type_e::Strings()
    {
        static const char* const strings[_TOTAL_ - Raw_Form_Type_e::_TOTAL_] =
        {
            SKYLIB_ENUM_TO_STRING(0x8A),
            SKYLIB_ENUM_TO_STRING(ALIAS_BASE),
            SKYLIB_ENUM_TO_STRING(ALIAS_REFERENCE),
            SKYLIB_ENUM_TO_STRING(ALIAS_LOCATION),
            SKYLIB_ENUM_TO_STRING(ACTIVE_MAGIC_EFFECT),
        };

        return strings;
    }

    some<const char*> Script_Type_e::To_String(Script_Type_e script_type)
    {
        if (script_type < Raw_Form_Type_e::_TOTAL_) {
            return Raw_Form_Type_e::To_String(script_type);
        } else if (script_type < _TOTAL_) {
            return Strings()[script_type - Raw_Form_Type_e::_TOTAL_];
        } else {
            return "NONE";
        }
    }

    Script_Type_e Script_Type_e::From_String(maybe<const char*> script_type)
    {
        if (script_type) {
            Raw_Form_Type_t raw_form_type = Raw_Form_Type_e::From_String(script_type);
            if (raw_form_type != Raw_Form_Type_e::_NONE_) {
                return raw_form_type;
            } else {
                some<const char* const*> strings = Strings();
                for (size_t idx = 0, end = _TOTAL_ - Raw_Form_Type_e::_TOTAL_; idx < end; idx += 1) {
                    some<const char*> string = strings[idx];
                    if (CString_t::Is_Same(string(), script_type(), true)) {
                        return static_cast<value_type>(idx + Raw_Form_Type_e::_TOTAL_);
                    }
                }
                return _NONE_;
            }
        } else {
            return _NONE_;
        }
    }

    maybe<Virtual::Class_t*> Script_Type_e::Class()
    {
        return Virtual::Class_t::Find_Or_Load(*this, true);
    }

}

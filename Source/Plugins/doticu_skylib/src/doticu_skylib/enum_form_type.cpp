/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cstring.h"
#include "doticu_skylib/enum_form_type.h"

namespace doticu_skylib {

    some<const char* const*> Raw_Form_Type_e::Strings()
    {
        static const char* const strings[_TOTAL_] =
        {
            SKYLIB_ENUM_TO_STRING(FORM),
            SKYLIB_ENUM_TO_STRING(0x01),
            SKYLIB_ENUM_TO_STRING(0x02),
            SKYLIB_ENUM_TO_STRING(0x03),
            SKYLIB_ENUM_TO_STRING(KEYWORD),
            SKYLIB_ENUM_TO_STRING(LOCATION_REFERENCE_TYPE),
            SKYLIB_ENUM_TO_STRING(0x06),
            SKYLIB_ENUM_TO_STRING(0x07),
            SKYLIB_ENUM_TO_STRING(MENU_ICON),
            SKYLIB_ENUM_TO_STRING(GLOBAL),
            SKYLIB_ENUM_TO_STRING(0x0A),
            SKYLIB_ENUM_TO_STRING(FACTION),
            SKYLIB_ENUM_TO_STRING(0x0C),
            SKYLIB_ENUM_TO_STRING(0x0D),
            SKYLIB_ENUM_TO_STRING(RACE),
            SKYLIB_ENUM_TO_STRING(0x0F),
            SKYLIB_ENUM_TO_STRING(0x10),
            SKYLIB_ENUM_TO_STRING(0x11),
            SKYLIB_ENUM_TO_STRING(MAGIC_EFFECT),
            SKYLIB_ENUM_TO_STRING(SCRIPT),
            SKYLIB_ENUM_TO_STRING(0x14),
            SKYLIB_ENUM_TO_STRING(ENCHANTMENT),
            SKYLIB_ENUM_TO_STRING(SPELL),
            SKYLIB_ENUM_TO_STRING(SCROLL),
            SKYLIB_ENUM_TO_STRING(ACTIVATOR),
            SKYLIB_ENUM_TO_STRING(0x19),
            SKYLIB_ENUM_TO_STRING(ARMOR),
            SKYLIB_ENUM_TO_STRING(BOOK),
            SKYLIB_ENUM_TO_STRING(CONTAINER),
            SKYLIB_ENUM_TO_STRING(0x1D),
            SKYLIB_ENUM_TO_STRING(INGREDIENT),
            SKYLIB_ENUM_TO_STRING(0x1F),
            SKYLIB_ENUM_TO_STRING(MISC),
            SKYLIB_ENUM_TO_STRING(0x21),
            SKYLIB_ENUM_TO_STRING(STATIC),
            SKYLIB_ENUM_TO_STRING(0x23),
            SKYLIB_ENUM_TO_STRING(0x24),
            SKYLIB_ENUM_TO_STRING(0x25),
            SKYLIB_ENUM_TO_STRING(0x26),
            SKYLIB_ENUM_TO_STRING(FLORA),
            SKYLIB_ENUM_TO_STRING(FURNITURE),
            SKYLIB_ENUM_TO_STRING(WEAPON),
            SKYLIB_ENUM_TO_STRING(AMMO),
            SKYLIB_ENUM_TO_STRING(ACTOR_BASE),
            SKYLIB_ENUM_TO_STRING(LEVELED_ACTOR_BASE),
            SKYLIB_ENUM_TO_STRING(KEY),
            SKYLIB_ENUM_TO_STRING(POTION),
            SKYLIB_ENUM_TO_STRING(0x2F),
            SKYLIB_ENUM_TO_STRING(0x30),
            SKYLIB_ENUM_TO_STRING(0x31),
            SKYLIB_ENUM_TO_STRING(PROJECTILE),
            SKYLIB_ENUM_TO_STRING(0x33),
            SKYLIB_ENUM_TO_STRING(SOUL_GEM),
            SKYLIB_ENUM_TO_STRING(LEVELED_ITEM),
            SKYLIB_ENUM_TO_STRING(0x36),
            SKYLIB_ENUM_TO_STRING(0x37),
            SKYLIB_ENUM_TO_STRING(0x38),
            SKYLIB_ENUM_TO_STRING(0x39),
            SKYLIB_ENUM_TO_STRING(0x3A),
            SKYLIB_ENUM_TO_STRING(0x3B),
            SKYLIB_ENUM_TO_STRING(CELL),
            SKYLIB_ENUM_TO_STRING(REFERENCE),
            SKYLIB_ENUM_TO_STRING(ACTOR),
            SKYLIB_ENUM_TO_STRING(0x3F),
            SKYLIB_ENUM_TO_STRING(0x40),
            SKYLIB_ENUM_TO_STRING(0x41),
            SKYLIB_ENUM_TO_STRING(0x42),
            SKYLIB_ENUM_TO_STRING(0x43),
            SKYLIB_ENUM_TO_STRING(0x44),
            SKYLIB_ENUM_TO_STRING(0x45),
            SKYLIB_ENUM_TO_STRING(0x46),
            SKYLIB_ENUM_TO_STRING(WORLDSPACE),
            SKYLIB_ENUM_TO_STRING(0x48),
            SKYLIB_ENUM_TO_STRING(0x49),
            SKYLIB_ENUM_TO_STRING(0x4A),
            SKYLIB_ENUM_TO_STRING(DIALOGUE_TOPIC),
            SKYLIB_ENUM_TO_STRING(DIALOGUE_INFO),
            SKYLIB_ENUM_TO_STRING(QUEST),
            SKYLIB_ENUM_TO_STRING(0x4E),
            SKYLIB_ENUM_TO_STRING(PACKAGE),
            SKYLIB_ENUM_TO_STRING(COMBAT_STYLE),
            SKYLIB_ENUM_TO_STRING(0x51),
            SKYLIB_ENUM_TO_STRING(0x52),
            SKYLIB_ENUM_TO_STRING(0x53),
            SKYLIB_ENUM_TO_STRING(0x54),
            SKYLIB_ENUM_TO_STRING(EFFECT_SHADER),
            SKYLIB_ENUM_TO_STRING(0x56),
            SKYLIB_ENUM_TO_STRING(0x57),
            SKYLIB_ENUM_TO_STRING(0x58),
            SKYLIB_ENUM_TO_STRING(0x59),
            SKYLIB_ENUM_TO_STRING(0x5A),
            SKYLIB_ENUM_TO_STRING(FORM_LIST),
            SKYLIB_ENUM_TO_STRING(PERK),
            SKYLIB_ENUM_TO_STRING(0x5D),
            SKYLIB_ENUM_TO_STRING(0x5E),
            SKYLIB_ENUM_TO_STRING(0x5F),
            SKYLIB_ENUM_TO_STRING(0x60),
            SKYLIB_ENUM_TO_STRING(0x61),
            SKYLIB_ENUM_TO_STRING(0x62),
            SKYLIB_ENUM_TO_STRING(0x63),
            SKYLIB_ENUM_TO_STRING(0x64),
            SKYLIB_ENUM_TO_STRING(0x65),
            SKYLIB_ENUM_TO_STRING(0x66),
            SKYLIB_ENUM_TO_STRING(ENCOUNTER_ZONE),
            SKYLIB_ENUM_TO_STRING(LOCATION),
            SKYLIB_ENUM_TO_STRING(MESSAGE),
            SKYLIB_ENUM_TO_STRING(0x6A),
            SKYLIB_ENUM_TO_STRING(0x6B),
            SKYLIB_ENUM_TO_STRING(0x6C),
            SKYLIB_ENUM_TO_STRING(0x6D),
            SKYLIB_ENUM_TO_STRING(0x6E),
            SKYLIB_ENUM_TO_STRING(0x6F),
            SKYLIB_ENUM_TO_STRING(0x70),
            SKYLIB_ENUM_TO_STRING(0x71),
            SKYLIB_ENUM_TO_STRING(0x72),
            SKYLIB_ENUM_TO_STRING(DIALOGUE_BRANCH),
            SKYLIB_ENUM_TO_STRING(0x74),
            SKYLIB_ENUM_TO_STRING(0x75),
            SKYLIB_ENUM_TO_STRING(0x76),
            SKYLIB_ENUM_TO_STRING(0x77),
            SKYLIB_ENUM_TO_STRING(0x78),
            SKYLIB_ENUM_TO_STRING(0x79),
            SKYLIB_ENUM_TO_STRING(0x7A),
            SKYLIB_ENUM_TO_STRING(0x7B),
            SKYLIB_ENUM_TO_STRING(OUTFIT),
            SKYLIB_ENUM_TO_STRING(0x7D),
            SKYLIB_ENUM_TO_STRING(0x7E),
            SKYLIB_ENUM_TO_STRING(0x7F),
            SKYLIB_ENUM_TO_STRING(0x80),
            SKYLIB_ENUM_TO_STRING(0x81),
            SKYLIB_ENUM_TO_STRING(0x82),
            SKYLIB_ENUM_TO_STRING(0x83),
            SKYLIB_ENUM_TO_STRING(0x84),
            SKYLIB_ENUM_TO_STRING(COLOR),
            SKYLIB_ENUM_TO_STRING(0x86),
            SKYLIB_ENUM_TO_STRING(0x87),
            SKYLIB_ENUM_TO_STRING(0x88),
            SKYLIB_ENUM_TO_STRING(0x89),
        };

        return strings;
    }

    some<const char*> Raw_Form_Type_e::To_String(Raw_Form_Type_t raw_form_type)
    {
        if (raw_form_type < _TOTAL_) {
            return Strings()[raw_form_type];
        } else {
            return "NONE";
        }
    }

    Raw_Form_Type_t Raw_Form_Type_e::From_String(maybe<const char*> raw_form_type)
    {
        if (raw_form_type) {
            some<const char* const*> strings = Strings();
            for (size_t idx = 0, end = _TOTAL_; idx < end; idx += 1) {
                some<const char*> string = strings[idx];
                if (CString_t::Is_Same(string(), raw_form_type(), true)) {
                    return static_cast<Raw_Form_Type_t>(idx);
                }
            }
            return _NONE_;
        } else {
            return _NONE_;
        }
    }

    some<const char*> Form_Type_e::As_String() const
    {
        return To_String(*this);
    }

}

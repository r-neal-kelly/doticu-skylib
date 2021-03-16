/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cstring.h"
#include "doticu_skylib/enum_extra_type.h"

namespace doticu_skylib {

    some<const char* const*> Extra_Type_e::Strings()
    {
        static const char* const strings[_TOTAL_] =
        {
            "NONE",
            SKYLIB_ENUM_TO_STRING(0x01),
            SKYLIB_ENUM_TO_STRING(0x02),
            SKYLIB_ENUM_TO_STRING(0x03),
            SKYLIB_ENUM_TO_STRING(0x04),
            SKYLIB_ENUM_TO_STRING(0x05),
            SKYLIB_ENUM_TO_STRING(0x06),
            SKYLIB_ENUM_TO_STRING(0x07),
            SKYLIB_ENUM_TO_STRING(0x08),
            SKYLIB_ENUM_TO_STRING(0x09),
            SKYLIB_ENUM_TO_STRING(0x0A),
            SKYLIB_ENUM_TO_STRING(0x0B),
            SKYLIB_ENUM_TO_STRING(0x0C),
            SKYLIB_ENUM_TO_STRING(0x0D),
            SKYLIB_ENUM_TO_STRING(0x0E),
            SKYLIB_ENUM_TO_STRING(0x0F),
            SKYLIB_ENUM_TO_STRING(0x10),
            SKYLIB_ENUM_TO_STRING(0x11),
            SKYLIB_ENUM_TO_STRING(0x12),
            SKYLIB_ENUM_TO_STRING(0x13),
            SKYLIB_ENUM_TO_STRING(0x14),
            SKYLIB_ENUM_TO_STRING(CONTAINER_CHANGES),
            SKYLIB_ENUM_TO_STRING(WORN),
            SKYLIB_ENUM_TO_STRING(WORN_LEFT),
            SKYLIB_ENUM_TO_STRING(0x18),
            SKYLIB_ENUM_TO_STRING(0x19),
            SKYLIB_ENUM_TO_STRING(0x1A),
            SKYLIB_ENUM_TO_STRING(0x1B),
            SKYLIB_ENUM_TO_STRING(REFERENCE_HANDLE),
            SKYLIB_ENUM_TO_STRING(FOLLOWERS),
            SKYLIB_ENUM_TO_STRING(0x1E),
            SKYLIB_ENUM_TO_STRING(GHOST),
            SKYLIB_ENUM_TO_STRING(0x20),
            SKYLIB_ENUM_TO_STRING(OWNER),
            SKYLIB_ENUM_TO_STRING(0x22),
            SKYLIB_ENUM_TO_STRING(0x23),
            SKYLIB_ENUM_TO_STRING(COUNT),
            SKYLIB_ENUM_TO_STRING(TEMPER_LEVEL),
            SKYLIB_ENUM_TO_STRING(0x26),
            SKYLIB_ENUM_TO_STRING(0x27),
            SKYLIB_ENUM_TO_STRING(CHARGE),
            SKYLIB_ENUM_TO_STRING(0x29),
            SKYLIB_ENUM_TO_STRING(0x2A),
            SKYLIB_ENUM_TO_STRING(0x2B),
            SKYLIB_ENUM_TO_STRING(0x2C),
            SKYLIB_ENUM_TO_STRING(0x2D),
            SKYLIB_ENUM_TO_STRING(LEVELED_ITEM),
            SKYLIB_ENUM_TO_STRING(0x2F),
            SKYLIB_ENUM_TO_STRING(0x30),
            SKYLIB_ENUM_TO_STRING(0x31),
            SKYLIB_ENUM_TO_STRING(0x32),
            SKYLIB_ENUM_TO_STRING(0x33),
            SKYLIB_ENUM_TO_STRING(0x34),
            SKYLIB_ENUM_TO_STRING(0x35),
            SKYLIB_ENUM_TO_STRING(0x36),
            SKYLIB_ENUM_TO_STRING(0x37),
            SKYLIB_ENUM_TO_STRING(0x38),
            SKYLIB_ENUM_TO_STRING(0x39),
            SKYLIB_ENUM_TO_STRING(0x3A),
            SKYLIB_ENUM_TO_STRING(0x3B),
            SKYLIB_ENUM_TO_STRING(0x3C),
            SKYLIB_ENUM_TO_STRING(CANNOT_WEAR),
            SKYLIB_ENUM_TO_STRING(POISON),
            SKYLIB_ENUM_TO_STRING(0x3F),
            SKYLIB_ENUM_TO_STRING(0x40),
            SKYLIB_ENUM_TO_STRING(0x41),
            SKYLIB_ENUM_TO_STRING(0x42),
            SKYLIB_ENUM_TO_STRING(0x43),
            SKYLIB_ENUM_TO_STRING(0x44),
            SKYLIB_ENUM_TO_STRING(0x45),
            SKYLIB_ENUM_TO_STRING(0x46),
            SKYLIB_ENUM_TO_STRING(0x47),
            SKYLIB_ENUM_TO_STRING(0x48),
            SKYLIB_ENUM_TO_STRING(HOTKEY),
            SKYLIB_ENUM_TO_STRING(0x4A),
            SKYLIB_ENUM_TO_STRING(0x4B),
            SKYLIB_ENUM_TO_STRING(0x4C),
            SKYLIB_ENUM_TO_STRING(0x4D),
            SKYLIB_ENUM_TO_STRING(0x4E),
            SKYLIB_ENUM_TO_STRING(0x4F),
            SKYLIB_ENUM_TO_STRING(0x50),
            SKYLIB_ENUM_TO_STRING(0x51),
            SKYLIB_ENUM_TO_STRING(0x52),
            SKYLIB_ENUM_TO_STRING(0x53),
            SKYLIB_ENUM_TO_STRING(TALK_TO_PLAYER),
            SKYLIB_ENUM_TO_STRING(0x55),
            SKYLIB_ENUM_TO_STRING(0x56),
            SKYLIB_ENUM_TO_STRING(0x57),
            SKYLIB_ENUM_TO_STRING(0x58),
            SKYLIB_ENUM_TO_STRING(0x59),
            SKYLIB_ENUM_TO_STRING(0x5A),
            SKYLIB_ENUM_TO_STRING(FACTIONS),
            SKYLIB_ENUM_TO_STRING(0x5C),
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
            SKYLIB_ENUM_TO_STRING(0x67),
            SKYLIB_ENUM_TO_STRING(0x68),
            SKYLIB_ENUM_TO_STRING(0x69),
            SKYLIB_ENUM_TO_STRING(0x6A),
            SKYLIB_ENUM_TO_STRING(0x6B),
            SKYLIB_ENUM_TO_STRING(0x6C),
            SKYLIB_ENUM_TO_STRING(0x6D),
            SKYLIB_ENUM_TO_STRING(COLLISION_LAYER),
            SKYLIB_ENUM_TO_STRING(0x6F),
            SKYLIB_ENUM_TO_STRING(ENCOUNTER_ZONE),
            SKYLIB_ENUM_TO_STRING(0x71),
            SKYLIB_ENUM_TO_STRING(0x72),
            SKYLIB_ENUM_TO_STRING(0x73),
            SKYLIB_ENUM_TO_STRING(0x74),
            SKYLIB_ENUM_TO_STRING(0x75),
            SKYLIB_ENUM_TO_STRING(0x76),
            SKYLIB_ENUM_TO_STRING(0x77),
            SKYLIB_ENUM_TO_STRING(0x78),
            SKYLIB_ENUM_TO_STRING(0x79),
            SKYLIB_ENUM_TO_STRING(0x7A),
            SKYLIB_ENUM_TO_STRING(0x7B),
            SKYLIB_ENUM_TO_STRING(0x7C),
            SKYLIB_ENUM_TO_STRING(0x7D),
            SKYLIB_ENUM_TO_STRING(0x7E),
            SKYLIB_ENUM_TO_STRING(0x7F),
            SKYLIB_ENUM_TO_STRING(0x80),
            SKYLIB_ENUM_TO_STRING(0x81),
            SKYLIB_ENUM_TO_STRING(0x82),
            SKYLIB_ENUM_TO_STRING(0x83),
            SKYLIB_ENUM_TO_STRING(0x84),
            SKYLIB_ENUM_TO_STRING(0x85),
            SKYLIB_ENUM_TO_STRING(0x86),
            SKYLIB_ENUM_TO_STRING(0x87),
            SKYLIB_ENUM_TO_STRING(ALIASES),
            SKYLIB_ENUM_TO_STRING(LOCATION),
            SKYLIB_ENUM_TO_STRING(0x8A),
            SKYLIB_ENUM_TO_STRING(0x8B),
            SKYLIB_ENUM_TO_STRING(0x8C),
            SKYLIB_ENUM_TO_STRING(0x8D),
            SKYLIB_ENUM_TO_STRING(OUTFIT),
            SKYLIB_ENUM_TO_STRING(0x8F),
            SKYLIB_ENUM_TO_STRING(0x90),
            SKYLIB_ENUM_TO_STRING(0x91),
            SKYLIB_ENUM_TO_STRING(0x92),
            SKYLIB_ENUM_TO_STRING(0x93),
            SKYLIB_ENUM_TO_STRING(0x94),
            SKYLIB_ENUM_TO_STRING(FROM_ALIAS),
            SKYLIB_ENUM_TO_STRING(SHOULD_WEAR),
            SKYLIB_ENUM_TO_STRING(0x97),
            SKYLIB_ENUM_TO_STRING(0x98),
            SKYLIB_ENUM_TO_STRING(TEXT_DISPLAY),
            SKYLIB_ENUM_TO_STRING(0x9A),
            SKYLIB_ENUM_TO_STRING(ENCHANTMENT),
            SKYLIB_ENUM_TO_STRING(SOUL_LEVEL),
            SKYLIB_ENUM_TO_STRING(0x9D),
            SKYLIB_ENUM_TO_STRING(0x9E),
            SKYLIB_ENUM_TO_STRING(UNIQUE_ID),
            SKYLIB_ENUM_TO_STRING(FLAGS),
            SKYLIB_ENUM_TO_STRING(0xA1),
            SKYLIB_ENUM_TO_STRING(0xA2),
            SKYLIB_ENUM_TO_STRING(0xA3),
            SKYLIB_ENUM_TO_STRING(0xA4),
            SKYLIB_ENUM_TO_STRING(0xA5),
            SKYLIB_ENUM_TO_STRING(0xA6),
            SKYLIB_ENUM_TO_STRING(0xA7),
            SKYLIB_ENUM_TO_STRING(0xA8),
            SKYLIB_ENUM_TO_STRING(REFERENCE_INTERACTION),
            SKYLIB_ENUM_TO_STRING(0xAA),
            SKYLIB_ENUM_TO_STRING(0xAB),
            SKYLIB_ENUM_TO_STRING(0xAC),
            SKYLIB_ENUM_TO_STRING(0xAD),
            SKYLIB_ENUM_TO_STRING(0xAE),
            SKYLIB_ENUM_TO_STRING(0xAF),
            SKYLIB_ENUM_TO_STRING(0xB0),
            SKYLIB_ENUM_TO_STRING(0xB1),
            SKYLIB_ENUM_TO_STRING(0xB2),
            SKYLIB_ENUM_TO_STRING(0xB3),
            SKYLIB_ENUM_TO_STRING(0xB4),
            SKYLIB_ENUM_TO_STRING(0xB5),
            SKYLIB_ENUM_TO_STRING(0xB6),
            SKYLIB_ENUM_TO_STRING(0xB7),
            SKYLIB_ENUM_TO_STRING(0xB8),
            SKYLIB_ENUM_TO_STRING(0xB9),
            SKYLIB_ENUM_TO_STRING(0xBA),
            SKYLIB_ENUM_TO_STRING(0xBB),
            SKYLIB_ENUM_TO_STRING(0xBC),
            SKYLIB_ENUM_TO_STRING(0xBD),
            SKYLIB_ENUM_TO_STRING(0xBE),
            SKYLIB_ENUM_TO_STRING(0xBF),
        };

        return strings;
    }

    some<const char*> Extra_Type_e::To_String(Extra_Type_e extra_type)
    {
        if (extra_type < _TOTAL_) {
            return Strings()[extra_type];
        } else {
            return Strings()[0];
        }
    }

    Extra_Type_e Extra_Type_e::From_String(maybe<const char*> extra_type)
    {
        if (extra_type) {
            some<const char* const*> strings = Strings();
            for (size_t idx = 0, end = _TOTAL_; idx < end; idx += 1) {
                some<const char*> string = strings[idx];
                if (CString_t::Is_Same(string(), extra_type(), true)) {
                    return static_cast<Extra_Type_e::value_type>(idx);
                }
            }
            return _NONE_;
        } else {
            return _NONE_;
        }
    }

    some<const char*> Extra_Type_e::As_String()
    {
        return To_String(*this);
    }

}

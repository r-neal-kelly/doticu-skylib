/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Extra_Type_e :
        public Enum_t<u8>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_                  = 0x00,

            // 0x01 0x01525CD8
            // 0X02
            // 0x03 0x0152CD60
            // 0x04 0x0152CCC0
            // 0x05 0x01525D18
            // 0x06 0x01525CF8
            // 0x07 0x0152CCE0
            // 0x08 0x0152CD20
            // 0x09 0x01566028
            // 0x0A 0x0152CDA0
            // 0x0B 0x0152F360
            // 0x0C
            // 0x0D 0x0152F240
            // 0x0E 0x0152BF40
            // 0x0F
            // 0x10 0x0152F180
            // 0x11
            // 0x12 0x0156C830
            // 0x13
            // 0x14 0x0152C200
            CONTAINER_CHANGES       = 0x15,
            WORN                    = 0x16,
            WORN_LEFT               = 0x17,
            // 0x18 0x0152C140
            // 0x19 0x0152F320
            // 0x1A
            // 0x1B 0x0152F380
            REFERENCE_HANDLE        = 0x1C,
            FOLLOWERS               = 0x1D,
            // 0x1E 0x0152C440
            GHOST                   = 0x1F,
            // 0x20
            OWNER                   = 0x21, // XOWN
            // 0x22
            // 0x23
            COUNT                   = 0x24,
            TEMPER_LEVEL            = 0x25,
            // 0x26
            // 0x27
            CHARGE                  = 0x28, // XCHG
            // 0x29 0x0152F1E0
            // 0x2A 0x0152BEA0
            // 0x2B 0x0152BF00
            // 0x2C 0x0152F220
            // 0x2D 0x0152F200
            LEVELED_ITEM            = 0x2E,
            // 0x2F
            // 0x30 0x0152CAA0
            // 0x31 0x0163AD50
            // 0x32 0x0152CDE0
            // 0x33
            // 0x34 0x0152F340
            // 0x35
            // 0x36 0x0152C240
            // 0x37 0x0152C260
            // 0x38
            // 0x39
            // 0x3A
            // 0x3B
            // 0x3C 0x0152C5C0
            CANNOT_WEAR             = 0x3D, // 
            POISON                  = 0x3E,
            // 0x3F
            // 0x40 0x0152C4A0
            // 0x41 0x0152C5A0
            // 0x42 0x0152CD80
            // 0x43
            // 0x44
            // 0x45 0x0152C600
            // 0x46
            // 0x47
            // 0x48 0x0152C640
            HOTKEY                  = 0x49, // 0x0152C120
            // 0x4A
            // 0x4B
            // 0x4C
            // 0x4D
            // 0x4E 0x0152C680
            // 0x4F
            // 0x50 0x0152C340
            // 0x51 0x0152C360
            // 0x52 0x0152C380
            // 0x53 0x0152C3A0
            TALK_TO_PLAYER          = 0x54,
            // 0x55 0x0152C760
            // 0x56 0x0152CD40
            // 0x57 0x0152C7A0
            // 0x58 0x0152C7C0
            // 0x59 0x0152C7E0
            // 0x5A
            FACTIONS                = 0x5B, // XRNK
            // 0x5C 0x0152F1A0
            // 0x5D 0x0152C820
            // 0x5E
            // 0x5F 0x0152FB40
            // 0x60 0x0152C500
            // 0x61 0x0152C3C0
            // 0x62 0x0152C3E0
            // 0x63 0x0152C4E0
            // 0x64
            // 0x65
            // 0x66
            // 0x67 0x0152C880
            // 0x68 0x0152BEE0
            // 0x69
            // 0x6A
            // 0x6B 0x0152C8A0
            // 0x6C 0x0152C920
            // 0x6D 0x0152F400
            COLLISION_LAYER         = 0x6E, // XTRI
            // 0x6F
            ENCOUNTER_ZONE          = 0x70,
            // 0x71 0x0152F4C0
            // 0x72 0x0152C8C0
            // 0x73 0x0152C8E0
            // 0x74
            // 0x75
            // 0x76
            // 0x77 0x0152C900
            // 0x78 0x0152C960
            // 0x79 0x0152C6A0
            // 0x7A
            // 0x7B 0x0152CB40
            // 0x7C 0x0152C980
            // 0x7D 0x0152CD00
            // 0x7E 0x0156C850
            // 0x7F
            // 0x80
            // 0x81
            // 0x82
            // 0x83
            // 0x84
            // 0x85 0x0152C2E0
            // 0x86
            // 0x87 0x0152F4E0
            ALIASES                 = 0x88,
            LOCATION                = 0x89,
            // 0x8A
            // 0x8B 0x0152C300
            // 0x8C 0x0152C9C0
            // 0x8D
            OUTFIT                  = 0x8E,
            // 0x8F
            // 0x90 0x0152C320
            // 0x91 0x0152CA00
            // 0x92 0x0152CA20
            // 0x93 0x0152CA40
            // 0x94
            FROM_ALIAS              = 0x95, // 
            SHOULD_WEAR             = 0x96, // 0x?
            // 0x97 0x0152CA80
            // 0x98 0x0152CB00
            TEXT_DISPLAY            = 0x99,
            // 0x9A 0x0152CB20
            ENCHANTMENT             = 0x9B,
            SOUL_LEVEL              = 0x9C,
            // 0x9D 0x0152CB60
            // 0x9E
            UNIQUE_ID               = 0x9F,
            FLAGS                   = 0xA0,
            // 0xA1 0x0152CBE0
            // 0xA2 0x0152CC00
            // 0xA3 0x0152F280
            // 0xA4 0x0152CB80
            // 0xA5 0x0152C9E0
            // 0xA6 0x0152CC20
            // 0xA7 0x0152F520
            // 0xA8 0x0152BF20
            REFERENCE_INTERACTION   = 0xA9,
            // 0xAA 0x0152CC40
            // 0xAB
            // 0xAC 0x0152C280
            // 0xAD 0x0152C2A0
            // 0xAE
            // 0xAF 0x0152CC80
            // 0xB0 0x0152C100
            // 0xB1
            // 0xB2
            // 0xB3
            // 0xB4 0x0156B378
            // 0xB5
            // 0xB6
            // 0xB7
            // 0xB8
            // 0xB9
            // 0xBA
            // 0xBB
            // 0xBC
            // 0xBD
            // 0xBE
            // 0xBF

            _TOTAL_                 = 0xC0,
        };

    public:
        static some<const char* const*> Strings();
        static some<const char*>        To_String(Extra_Type_e extra_type);
        static Extra_Type_e             From_String(maybe<const char*> extra_type);

    public:
        using Enum_t::Enum_t;

    public:
        some<const char*> As_String();
    };

}

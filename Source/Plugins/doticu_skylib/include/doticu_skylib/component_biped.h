/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Biped_Slots_e : public Enum_t<u32>
    {
    public:
        enum : u32
        {
            HEAD                = 1lu << 0,
            HAIR                = 1lu << 1,
            BODY                = 1lu << 2,
            HANDS               = 1lu << 3,
            FOREARMS            = 1lu << 4,
            AMULET              = 1lu << 5,
            RING                = 1lu << 6,
            FEET                = 1lu << 7,
            CALVES              = 1lu << 8,
            SHIELD              = 1lu << 9,
            TAIL                = 1lu << 10,
            LONG_HAIR           = 1lu << 11,
            CIRCLET             = 1lu << 12,
            EARS                = 1lu << 13,
            DECAPTIATED_HEAD    = 1lu << 20,
            DECAPITATED_NECK    = 1lu << 21,
            FX                  = 1lu << 31,
        };
        using Enum_t::Enum_t;
    };

    class Armor_Type_e : public Enum_t<u32>
    {
    public:
        enum : u32
        {
            LIGHT_ARMOR = 0,
            HEAVY_ARMOR = 1,
            CLOTHING = 2,
        };
        using Enum_t::Enum_t;
    };

    class Biped_c : public Form_Data_c // BGSBipedObjectForm
    {
    public:
        virtual ~Biped_c(); // 0

        Biped_Slots_e   biped_slots;
        Armor_Type_e    biped_armor_type;
    };
    STATIC_ASSERT(sizeof(Biped_c) == 0x10);

}

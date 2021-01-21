/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Actor_Value_e : public Enum_t<u32>
    {
    public:
        enum : value_type
        {
            AGGRESSION = 0,
            CONFIDENCE,
            ENERGY,
            MORALITY,
            MOOD,
            ASSISTANCE,
            ONE_HANDED,
            TWO_HANDED,
            MARKSMAN,
            BLOCK,
            SMITHING,
            HEAVY_ARMOR,
            LIGHT_ARMOR,
            PICKPOCKET,
            LOCKPICKING,
            SNEAK,
            ALCHEMY,
            SPEECHCRAFT,
            ALTERATION,
            CONJURATION,
            DESTRUCTION,
            ILLUSION,
            RESTORATION,
            ENCHANTING,
            HEALTH,
            MAGICKA,
            STAMINA,
            HEAL_RATE,
            MAGICKA_RATE,
            STAMINA_RATE,
            SPEED_MULT,
            INVENTORY_WEIGHT,
            CARRY_WEIGHT,
            CRITICAL_CHANCE,
            MELEE_DAMAGE,
            UNARMED_DAMAGE,
            MASS,
            VOICE_POINTS,
            VOICE_RATE,
            DAMAGE_RESIST,
            POISON_RESIST,
            RESIST_FIRE,
            RESIST_SHOCK,
            RESIST_FROST,
            RESIST_MAGIC,
            RESIST_DISEASE,
            UNKNOWN_46,
            UNKNOWN_47,
            UNKNOWN_48,
            UNKNOWN_49,
            UNKNOWN_50,
            UNKNOWN_51,
            UNKNOWN_52,
            PARALYSIS,
            INVISIBILITY,
            NIGHT_EYE,
            DETECT_LIFE_RANGE,
            WATER_BREATHING,
            WATER_WALKING,
            UNKNOWN_59,
            FAME,
            INFAMY,
            JUMPING_BONUS,
            WARD_POWER,
            RIGHT_ITEM_CHARGE,
            ARMOR_PERKS,
            SHIELD_PERKS,
            WARD_DEFLECTION,
            VARIABLE_01,
            VARIABLE_02,
            VARIABLE_03,
            VARIABLE_04,
            VARIABLE_05,
            VARIABLE_06,
            VARIABLE_07,
            VARIABLE_08,
            VARIABLE_09,
            VARIABLE_10,
            // ...
            WAITING_FOR_PLAYER = 95,
            // ...
            INVALID = 164
        };
        using Enum_t::Enum_t;
    };

}

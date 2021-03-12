/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    using Raw_Actor_Value_Type_t = u32;

    class Actor_Value_Type_e :
        public Enum_t<Raw_Actor_Value_Type_t>
    {
    public:
        enum enum_type : value_type
        {
            _NONE_                          = static_cast<value_type>(-1),

            AGGRESSION                      = static_cast<value_type>(0x00),
            CONFIDENCE                      = static_cast<value_type>(0x01),
            ENERGY                          = static_cast<value_type>(0x02),
            MORALITY                        = static_cast<value_type>(0x03),
            MOOD                            = static_cast<value_type>(0x04),
            ASSISTANCE                      = static_cast<value_type>(0x05),
            ONE_HANDED                      = static_cast<value_type>(0x06),
            TWO_HANDED                      = static_cast<value_type>(0x07),
            MARKSMAN                        = static_cast<value_type>(0x08),
            BLOCK                           = static_cast<value_type>(0x09),
            SMITHING                        = static_cast<value_type>(0x0A),
            HEAVY_ARMOR                     = static_cast<value_type>(0x0B),
            LIGHT_ARMOR                     = static_cast<value_type>(0x0C),
            PICKPOCKET                      = static_cast<value_type>(0x0D),
            LOCKPICKING                     = static_cast<value_type>(0x0E),
            SNEAK                           = static_cast<value_type>(0x0F),
            ALCHEMY                         = static_cast<value_type>(0x10),
            SPEECHCRAFT                     = static_cast<value_type>(0x11),
            ALTERATION                      = static_cast<value_type>(0x12),
            CONJURATION                     = static_cast<value_type>(0x13),
            DESTRUCTION                     = static_cast<value_type>(0x14),
            ILLUSION                        = static_cast<value_type>(0x15),
            RESTORATION                     = static_cast<value_type>(0x16),
            ENCHANTING                      = static_cast<value_type>(0x17),
            HEALTH                          = static_cast<value_type>(0x18),
            MAGICKA                         = static_cast<value_type>(0x19),
            STAMINA                         = static_cast<value_type>(0x1A),
            HEAL_RATE                       = static_cast<value_type>(0x1B),
            MAGICKA_RATE                    = static_cast<value_type>(0x1C),
            STAMINA_RATE                    = static_cast<value_type>(0x1D),
            SPEED_MULT                      = static_cast<value_type>(0x1E),
            INVENTORY_WEIGHT                = static_cast<value_type>(0x1F),
            CARRY_WEIGHT                    = static_cast<value_type>(0x20),
            CRITICAL_CHANCE                 = static_cast<value_type>(0x21),
            MELEE_DAMAGE                    = static_cast<value_type>(0x22),
            UNARMED_DAMAGE                  = static_cast<value_type>(0x23),
            MASS                            = static_cast<value_type>(0x24),
            VOICE_POINTS                    = static_cast<value_type>(0x25),
            VOICE_RATE                      = static_cast<value_type>(0x26),
            DAMAGE_RESIST                   = static_cast<value_type>(0x27),
            POISON_RESIST                   = static_cast<value_type>(0x28),
            RESIST_FIRE                     = static_cast<value_type>(0x29),
            RESIST_SHOCK                    = static_cast<value_type>(0x2A),
            RESIST_FROST                    = static_cast<value_type>(0x2B),
            RESIST_MAGIC                    = static_cast<value_type>(0x2C),
            RESIST_DISEASE                  = static_cast<value_type>(0x2D),
            UNK_2E                          = static_cast<value_type>(0x2E),
            UNK_2F                          = static_cast<value_type>(0x2F),
            UNK_30                          = static_cast<value_type>(0x30),
            UNK_31                          = static_cast<value_type>(0x31),
            UNK_32                          = static_cast<value_type>(0x32),
            UNK_33                          = static_cast<value_type>(0x33),
            UNK_34                          = static_cast<value_type>(0x34),
            PARALYSIS                       = static_cast<value_type>(0x35),
            INVISIBILITY                    = static_cast<value_type>(0x36),
            NIGHT_EYE                       = static_cast<value_type>(0x37),
            DETECT_LIFE_RANGE               = static_cast<value_type>(0x38),
            WATER_BREATHING                 = static_cast<value_type>(0x39),
            WATER_WALKING                   = static_cast<value_type>(0x3A),
            UNK_3B                          = static_cast<value_type>(0x3B),
            FAME                            = static_cast<value_type>(0x3C),
            INFAMY                          = static_cast<value_type>(0x3D),
            JUMPING_BONUS                   = static_cast<value_type>(0x3E),
            WARD_POWER                      = static_cast<value_type>(0x3F),
            RIGHT_ITEM_CHARGE               = static_cast<value_type>(0x40),
            ARMOR_PERKS                     = static_cast<value_type>(0x41),
            SHIELD_PERKS                    = static_cast<value_type>(0x42),
            WARD_DEFLECTION                 = static_cast<value_type>(0x43),
            VARIABLE_01                     = static_cast<value_type>(0x44),
            VARIABLE_02                     = static_cast<value_type>(0x45),
            VARIABLE_03                     = static_cast<value_type>(0x46),
            VARIABLE_04                     = static_cast<value_type>(0x47),
            VARIABLE_05                     = static_cast<value_type>(0x48),
            VARIABLE_06                     = static_cast<value_type>(0x49),
            VARIABLE_07                     = static_cast<value_type>(0x4A),
            VARIABLE_08                     = static_cast<value_type>(0x4B),
            VARIABLE_09                     = static_cast<value_type>(0x4C),
            VARIABLE_10                     = static_cast<value_type>(0x4D),
            BOW_SPEED_BONUS                 = static_cast<value_type>(0x4E),
            FAVOR_ACTIVE                    = static_cast<value_type>(0x4F),
            FAVORS_PER_DAY                  = static_cast<value_type>(0x50),
            FAVORS_PER_DAY_TIMER            = static_cast<value_type>(0x51),
            LEFT_ITEM_CHARGE                = static_cast<value_type>(0x52),
            ABSORB_CHANCE                   = static_cast<value_type>(0x53),
            BLINDNESS                       = static_cast<value_type>(0x54),
            WEAPON_SPEED_MULT               = static_cast<value_type>(0x55),
            SHOUT_RECOVERY_MULT             = static_cast<value_type>(0x56),
            BOW_STAGGER_BONUS               = static_cast<value_type>(0x57),
            TELEKINESIS                     = static_cast<value_type>(0x58),
            FAVOR_POINTS_BONUS              = static_cast<value_type>(0x59),
            LAST_BRIBED_INTIMIDATED         = static_cast<value_type>(0x5A),
            LAST_FLATTERED                  = static_cast<value_type>(0x5B),
            MOVEMENT_NOISE_MULT             = static_cast<value_type>(0x5C),
            BYPASS_VENDOR_STOLEN_CHECK      = static_cast<value_type>(0x5D),
            BYPASS_VENDOR_KEYWORD_CHECK     = static_cast<value_type>(0x5E),
            WAITING_FOR_PLAYER              = static_cast<value_type>(0x5F),
            ONE_HANDED_MODIFIER             = static_cast<value_type>(0x60),
            TWO_HANDED_MODIFIER             = static_cast<value_type>(0x61),
            MARKSMAN_MODIFIER               = static_cast<value_type>(0x62),
            BLOCK_MODIFIER                  = static_cast<value_type>(0x63),
            SMITHING_MODIFIER               = static_cast<value_type>(0x64),
            HEAVY_ARMOR_MODIFIER            = static_cast<value_type>(0x65),
            LIGHT_ARMOR_MODIFIER            = static_cast<value_type>(0x66),
            PICKPOCKET_MODIFIER             = static_cast<value_type>(0x67),
            LOCKPICKING_MODIFIER            = static_cast<value_type>(0x68),
            SNEAK_MODIFIER                  = static_cast<value_type>(0x69),
            ALCHEMY_MODIFIER                = static_cast<value_type>(0x6A),
            SPEECHCRAFT_MODIFIER            = static_cast<value_type>(0x6B),
            ALTERATION_MODIFIER             = static_cast<value_type>(0x6C),
            CONJURATION_MODIFIER            = static_cast<value_type>(0x6D),
            DESTRUCTION_MODIFIER            = static_cast<value_type>(0x6E),
            ILLUSION_MODIFIER               = static_cast<value_type>(0x6F),
            RESTORATION_MODIFIER            = static_cast<value_type>(0x70),
            ENCHANTING_MODIFIER             = static_cast<value_type>(0x71),
            ONE_HANDED_SKILL_ADVANCE        = static_cast<value_type>(0x72),
            TWO_HANDED_SKILL_ADVANCE        = static_cast<value_type>(0x73),
            MARKSMAN_SKILL_ADVANCE          = static_cast<value_type>(0x74),
            BLOCK_SKILL_ADVANCE             = static_cast<value_type>(0x75),
            SMITHING_SKILL_ADVANCE          = static_cast<value_type>(0x76),
            HEAVY_ARMOR_SKILL_ADVANCE       = static_cast<value_type>(0x77),
            LIGHT_ARMOR_SKILL_ADVANCE       = static_cast<value_type>(0x78),
            PICKPOCKET_SKILL_ADVANCE        = static_cast<value_type>(0x79),
            LOCKPICKING_SKILL_ADVANCE       = static_cast<value_type>(0x7A),
            SNEAK_SKILL_ADVANCE             = static_cast<value_type>(0x7B),
            ALCHEMY_SKILL_ADVANCE           = static_cast<value_type>(0x7C),
            SPEECHCRAFT_SKILL_ADVANCE       = static_cast<value_type>(0x7D),
            ALTERATION_SKILL_ADVANCE        = static_cast<value_type>(0x7E),
            CONJURATION_SKILL_ADVANCE       = static_cast<value_type>(0x7F),
            DESTRUCTION_SKILL_ADVANCE       = static_cast<value_type>(0x80),
            ILLUSION_SKILL_ADVANCE          = static_cast<value_type>(0x81),
            RESTORATION_SKILL_ADVANCE       = static_cast<value_type>(0x82),
            ENCHANTING_SKILL_ADVANCE        = static_cast<value_type>(0x83),
            LEFT_WEAPON_SPEED_MULTIPLY      = static_cast<value_type>(0x84),
            DRAGON_SOULS                    = static_cast<value_type>(0x85),
            COMBAT_HEALTH_REGEN_MULTIPLY    = static_cast<value_type>(0x86),
            ONE_HANDED_POWER_MODIFIER       = static_cast<value_type>(0x87),
            TWO_HANDED_POWER_MODIFIER       = static_cast<value_type>(0x88),
            MARKSMAN_POWER_MODIFIER         = static_cast<value_type>(0x89),
            BLOCK_POWER_MODIFIER            = static_cast<value_type>(0x8A),
            SMITHING_POWER_MODIFIER         = static_cast<value_type>(0x8B),
            HEAVY_ARMOR_POWER_MODIFIER      = static_cast<value_type>(0x8C),
            LIGHT_ARMOR_POWER_MODIFIER      = static_cast<value_type>(0x8D),
            PICKPOCKET_POWER_MODIFIER       = static_cast<value_type>(0x8E),
            LOCKPICKING_POWER_MODIFIER      = static_cast<value_type>(0x8F),
            SNEAK_POWER_MODIFIER            = static_cast<value_type>(0x90),
            ALCHEMY_POWER_MODIFIER          = static_cast<value_type>(0x91),
            SPEECHCRAFT_POWER_MODIFIER      = static_cast<value_type>(0x92),
            ALTERATION_POWER_MODIFIER       = static_cast<value_type>(0x93),
            CONJURATION_POWER_MODIFIER      = static_cast<value_type>(0x94),
            DESTRUCTION_POWER_MODIFIER      = static_cast<value_type>(0x95),
            ILLUSION_POWER_MODIFIER         = static_cast<value_type>(0x96),
            RESTORATION_POWER_MODIFIER      = static_cast<value_type>(0x97),
            ENCHANTING_POWER_MODIFIER       = static_cast<value_type>(0x98),
            DRAGON_REND                     = static_cast<value_type>(0x99),
            ATTACK_DAMAGE_MULT              = static_cast<value_type>(0x9A),
            HEAL_RATE_MULT                  = static_cast<value_type>(0x9B),
            MAGICKA_RATE_MULT               = static_cast<value_type>(0x9C),
            STAMINA_RATE_MULT               = static_cast<value_type>(0x9D),
            WEREWOLF_PERKS                  = static_cast<value_type>(0x9E),
            VAMPIRE_PERKS                   = static_cast<value_type>(0x9F),
            GRAB_ACTOR_OFFSET               = static_cast<value_type>(0xA0),
            GRABBED                         = static_cast<value_type>(0xA1),
            UNK_A2                          = static_cast<value_type>(0xA2),
            REFLECT_DAMAGE                  = static_cast<value_type>(0xA3),

            _TOTAL_                         = static_cast<value_type>(0xA4),
        };

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                FROM_ABSTRACT_NAME = 0x003E1450, // 26570 (probably will move to ActorValueList type, as named in SKSE, when we implement it)
            };
            using Enum_t::Enum_t;
        };

    public:
        using Enum_t::Enum_t;

    public:
        static some<const char* const*> Strings();
        static some<const char*>        To_String(Actor_Value_Type_e actor_value_type);
        static Actor_Value_Type_e       From_String(maybe<const char*> actor_value_type);
        static Actor_Value_Type_e       From_Abstract_Name(maybe<const char*> abstract_name);
    };

}

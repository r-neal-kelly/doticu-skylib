/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Actor_Base_Template_Flags_e :
        public Enum_t<u16>
    {
    public:
        enum enum_type : value_type
        {
            TRAITS              = static_cast<value_type>(1 << 0), // (sex, race, skin, height, weight, far away skin and distance, voice type, weapon list, alignment, disposition base, death item, opposite gender animations, sounds, animations)
            STATS               = static_cast<value_type>(1 << 1), // (level, pc level mult, calc min, calc max, auto calc stats, health data, magicka data, stamina data, skills, speed, bleedout override, class)
            FACTIONS            = static_cast<value_type>(1 << 2), // (factions and ranks, assigned crime faction)
            SPELLS_AND_PERKS    = static_cast<value_type>(1 << 3), // (spell list and perk list)
            AI_DATA             = static_cast<value_type>(1 << 4), // (aggression, mood, confidence, assistance, morality, energy, aggro radius behavior, warn, warn/attack, attack, combat style, gift filter)
            AI_PACKAGES         = static_cast<value_type>(1 << 5), // (ai package list)
            UNK_06              = static_cast<value_type>(1 << 6), // (RELATIONSHIPS? can't be set in editor)
            BASE_DATA           = static_cast<value_type>(1 << 7), // (is essential, is summonable, encumbrance flag, respawns, simple actor, doesn't affect stealth meter)
            INVENTORY           = static_cast<value_type>(1 << 8), // (default outfit, sleep oufit, base container)
            SCRIPTS             = static_cast<value_type>(1 << 9), // (I think additionally, rather than overriding)
            DEFAULT_AI_PACKAGES = static_cast<value_type>(1 << 10), // (default list, spectator override list, observe dead override list, guard override list, combat override list)
            ATTACK_DATA         = static_cast<value_type>(1 << 11), // (behavior graph data and overrides)
            KEYWORDS            = static_cast<value_type>(1 << 12), // (keywords)
        };

    public:
        using Enum_t::Enum_t;

    public:
        void Log(std::string indent = "");
    };

}

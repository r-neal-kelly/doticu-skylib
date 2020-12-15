/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/enum.h"
#include "doticu_skylib/string.h"

#include "doticu_skylib/component_form_data.h"

#include "doticu_skylib/faction_and_rank.h"

class TESLevItem;
class BGSVoiceType;

namespace doticu_skylib {

    class Form_t;

    class Actor_Base_Flags_e : public Enum_t<u32>
    {
    public:
        enum : u32
        {
            IS_FEMALE                       = 1lu << 0,
            IS_ESSENTIAL                    = 1lu << 1,
            IS_CHARGEN_FACE_PRESET          = 1lu << 2,
            DOES_RESPAWN                    = 1lu << 3,
            DOES_AUTO_CALCUATE_STATS        = 1lu << 4,
            IS_UNIQUE                       = 1lu << 5,
            DOESNT_AFFECT_STEALTH_METER     = 1lu << 6,
            HAS_PC_LEVEL_MULTIPLIER         = 1lu << 7,
            DOES_USE_TEMPLATE               = 1lu << 8,
            IS_PROTECTED                    = 1lu << 11,
            IS_SUMMONABLE                   = 1lu << 14,
            DOESNT_BLEED                    = 1lu << 16,
            HAS_BLEEDOUT_OVERRIDE           = 1lu << 18,
            HAS_OPPOSITE_GENDER_ANIMATIONS  = 1lu << 19,
            IS_SIMPLE_ACTOR                 = 1lu << 20,
            HAS_LOOPED_SCRIPT               = 1lu << 21,
            HAS_LOOPED_AUDIO                = 1lu << 28,
            IS_GHOST                        = 1lu << 29,
            IS_INVULNERABLE                 = 1lu << 31,
        };
        using Enum_t::Enum_t;
    };

    class Actor_Base_Template_Flags_e : public Enum_t<u16>
    {
    public:
        enum : u16
        {
            TRAITS              = 1lu << 0,
            STATS               = 1lu << 1,
            FACTIONS            = 1lu << 2,
            SPELLS              = 1lu << 3,
            AI_DATA             = 1lu << 4,
            AI_PACKAGES         = 1lu << 5,
            UNUSED              = 1lu << 6,
            BASE_DATA           = 1lu << 7,
            INVENTORY           = 1lu << 8,
            SCRIPT              = 1lu << 9,
            AI_DEFAULT_PACKAGES = 1lu << 10,
            ATTACK_DATA         = 1lu << 11,
            KEYWORDS            = 1lu << 12,
        };
        using Enum_t::Enum_t;
    };

    class Actor_Base_Data_c : public Form_Data_c
    {
    public:
        virtual ~Actor_Base_Data_c(); // 0

        Actor_Base_Flags_e          actor_base_flags;           // 08
        s16                         magicka_offset;             // 0C
        s16                         stamina_offset;             // 0E
        u16                         level;                      // 10
        u16                         min_level_calc;             // 12
        u16                         max_level_calc;             // 14
        u16                         speed_multiplier;           // 16
        u16                         base_disposition;           // 18
        Actor_Base_Template_Flags_e actor_base_template_flags;  // 1A
        s16                         health_offset;              // 1C
        s16                         bleedout_override;          // 1E
        TESLevItem*                 death_item;                 // 20
        BGSVoiceType*               voice_type;                 // 28
        Form_t*                     base_template_form;         // 30
        Form_t**                    template_forms;             // 38
        Array_t<Faction_And_Rank_t> factions_and_ranks;         // 40

        Bool_t Is_Male();
        Bool_t Is_Female();
        Bool_t Is_Unique();
        Bool_t Is_Generic();
    };
    STATIC_ASSERT(sizeof(Actor_Base_Data_c) == 0x58);

}

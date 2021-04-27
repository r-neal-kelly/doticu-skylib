/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_destructible.h"
#include "doticu_skylib/component_equip_slot.h"
#include "doticu_skylib/component_grab_sounds.h"
#include "doticu_skylib/component_icon.h"
#include "doticu_skylib/component_message_icon.h"
#include "doticu_skylib/component_model_alternates.h"
#include "doticu_skylib/component_weight.h"
#include "doticu_skylib/enum_potion_flags.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/magic_base.h"

namespace doticu_skylib {

    class Sound_Descriptor_t; // BGSSoundDescriptorForm
    class Spell_t;

    class Potion_t :                // AlchemyItem
        public Magic_Base_t,        // 000
        public Model_Alternates_c,  // 090
        public Icon_c,              // 0C8
        public Message_Icon_c,      // 0D8
        public Weight_c,            // 0F0
        public Equip_Slot_c,        // 100
        public Destructible_c,      // 110
        public Grab_Sounds_c        // 120
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::POTION,
        };

        static constexpr const char* SCRIPT_NAME = "Potion";

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E10E70, // 513850
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Potion_t(); // 0

    public:
        s32                         cost_override;      // 138 (gold value?)
        Potion_Flags_e              potion_flags;       // 13C
        maybe<Spell_t*>             addiction_spell;    // 140
        Float_t                     addiction_chance;   // 148
        u32                         pad_14C;            // 14C
        maybe<Sound_Descriptor_t*>  consumption_sound;  // 150
        Icon_c                      unk_icon;           // 158

    public:
        Bool_t  Is_Potion() const;
        Bool_t  Is_Poison() const;
        Bool_t  Is_Food() const;
        Bool_t  Is_Prepared_Food() const;
        Bool_t  Is_Raw_Food() const;

    public:
        void    Log(std::string indent = "") const;
    };
    STATIC_ASSERT(sizeof(Potion_t) == 0x168);

}

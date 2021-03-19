/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/bound_object.h"
#include "doticu_skylib/component_biped_model.h"
#include "doticu_skylib/component_biped_object.h"
#include "doticu_skylib/component_block_bash.h"
#include "doticu_skylib/component_description.h"
#include "doticu_skylib/component_destructible.h"
#include "doticu_skylib/component_enchantable.h"
#include "doticu_skylib/component_equip_slot.h"
#include "doticu_skylib/component_grab_sounds.h"
#include "doticu_skylib/component_keywords.h"
#include "doticu_skylib/component_name.h"
#include "doticu_skylib/component_race.h"
#include "doticu_skylib/component_value.h"
#include "doticu_skylib/component_weight.h"
#include "doticu_skylib/dynamic_array.h"
#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Armor_t :             // TESObjectARMO
        public Bound_Object_t,  // 000
        public Name_c,          // 030
        public Race_c,          // 040
        public Enchantable_c,   // 050
        public Value_c,         // 068
        public Weight_c,        // 078
        public Destructible_c,  // 088
        public Grab_Sounds_c,   // 098
        public Biped_Model_c,   // 0B0
        public Equip_Slot_c,    // 1A0
        public Biped_Object_c,  // 1B0
        public Block_Bash_c,    // 1C0
        public Keywords_c,      // 1D8
        public Description_c    // 1F0
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::ARMOR,
        };

        static constexpr const char* SCRIPT_NAME = "Armor";

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E153C0, // 513936
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Armor_t(); // 00

    public:
        u32             armor_rating;       // 200
        u32             pad_204;            // 204
        Array_t<void*>  armor_addons;       // 208
        maybe<Armor_t*> armor_templates;    // 220

    public:
        Bool_t  Is_Likely_Armor() const;
        Bool_t  Is_Surely_Armor() const;
        Bool_t  Is_Light_Armor() const;
        Bool_t  Is_Heavy_Armor() const;
        Bool_t  Is_Helmet() const;
        Bool_t  Is_Cuirass() const;
        Bool_t  Is_Gauntlets() const;
        Bool_t  Is_Boots() const;
        Bool_t  Is_Shield() const;
        
        Bool_t  Is_Likely_Clothing() const;
        Bool_t  Is_Surely_Clothing() const;
        Bool_t  Is_Lower_Class_Clothing() const;
        Bool_t  Is_Likely_Middle_Class_Clothing() const;
        Bool_t  Is_Surely_Middle_Class_Clothing() const;
        Bool_t  Is_Upper_Class_Clothing() const;
        Bool_t  Is_Hat() const;
        Bool_t  Is_Shirt() const;
        Bool_t  Is_Gloves() const;
        Bool_t  Is_Shoes() const;

        Bool_t  Is_Likely_Jewelry() const;
        Bool_t  Is_Surely_Jewelry() const;
        Bool_t  Is_Likely_Cheap_Jewelry() const;
        Bool_t  Is_Surely_Cheap_Jewelry() const;
        Bool_t  Is_Expensive_Jewelry() const;
        Bool_t  Is_Circlet() const;
        Bool_t  Is_Necklace() const;
        Bool_t  Is_Ring() const;

        Bool_t  Is_For_Head() const;
        Bool_t  Is_For_Forehead() const;
        Bool_t  Is_For_Neck() const;
        Bool_t  Is_For_Body() const;
        Bool_t  Is_For_Forearm() const;
        Bool_t  Is_For_Hands() const;
        Bool_t  Is_For_Finger() const;
        Bool_t  Is_For_Feet() const;

        Bool_t  Is_Aetherium_Material() const;
        Bool_t  Is_Blades_Material() const;
        Bool_t  Is_Bonemold_Heavy_Material() const;
        Bool_t  Is_Bonemold_Light_Material() const;
        Bool_t  Is_Chitin_Heavy_Material() const;
        Bool_t  Is_Chitin_Light_Material() const;
        Bool_t  Is_Daedric_Material() const;
        Bool_t  Is_Dark_Brotherhood_Material() const;
        Bool_t  Is_Dawnguard_Material() const;
        Bool_t  Is_Dragonplate_Material() const;
        Bool_t  Is_Dragonscale_Material() const;
        Bool_t  Is_Dwarven_Material() const;
        Bool_t  Is_Ebony_Material() const;
        Bool_t  Is_Elven_Material() const;
        Bool_t  Is_Elven_Gilded_Material() const;
        Bool_t  Is_Falmer_Material() const;
        Bool_t  Is_Falmer_Hardened_Material() const;
        Bool_t  Is_Falmer_Heavy_Material() const;
        Bool_t  Is_Falmer_Heavy_Original_Material() const;
        Bool_t  Is_Forsworn_Material() const;
        Bool_t  Is_Forsworn_MS02_Material() const;
        Bool_t  Is_Glass_Material() const;
        Bool_t  Is_Hide_Material() const;
        Bool_t  Is_Hunter_Material() const;
        Bool_t  Is_Imperial_Heavy_Material() const;
        Bool_t  Is_Imperial_Light_Material() const;
        Bool_t  Is_Imperial_Studded_Material() const;
        Bool_t  Is_Iron_Material() const;
        Bool_t  Is_Iron_Banded_Material() const;
        Bool_t  Is_Leather_Material() const;
        Bool_t  Is_Morag_Tong_Material() const;
        Bool_t  Is_Nightingale_Material() const;
        Bool_t  Is_Nordic_Heavy_Material() const;
        Bool_t  Is_Nordic_Light_Material() const;
        Bool_t  Is_Orcish_Material() const;
        Bool_t  Is_Penitus_Material() const;
        Bool_t  Is_Scaled_Material() const;
        Bool_t  Is_Stalhrim_Heavy_Material() const;
        Bool_t  Is_Stalhrim_Light_Material() const;
        Bool_t  Is_Steel_Material() const;
        Bool_t  Is_Steel_Plate_Material() const;
        Bool_t  Is_Stormcloak_Material() const;
        Bool_t  Is_Stormcloak_Bear_Material() const;
        Bool_t  Is_Studded_Material() const;
        Bool_t  Is_Thieves_Guild_Material() const;
        Bool_t  Is_Thieves_Guild_Leader_Material() const;
        Bool_t  Is_Vampire_Material() const;

        Bool_t  Is_Daedric_Artifact() const;

    public:
        void Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Armor_t) == 0x228);

}

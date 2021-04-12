/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Keyword_t;

}

namespace doticu_skylib { namespace Const { namespace Keyword {

    some<Keyword_t*> Armor_Material_Blades();
    some<Keyword_t*> Armor_Material_Bonemold_Heavy();
    some<Keyword_t*> Armor_Material_Bonemold_Light();
    some<Keyword_t*> Armor_Material_Chitin_Heavy();
    some<Keyword_t*> Armor_Material_Chitin_Light();
    some<Keyword_t*> Armor_Material_Daedric();
    some<Keyword_t*> Armor_Material_Dark_Brotherhood();
    some<Keyword_t*> Armor_Material_Dawnguard();
    some<Keyword_t*> Armor_Material_Dragonplate();
    some<Keyword_t*> Armor_Material_Dragonscale();
    some<Keyword_t*> Armor_Material_Dwarven();
    some<Keyword_t*> Armor_Material_Ebony();
    some<Keyword_t*> Armor_Material_Elven();
    some<Keyword_t*> Armor_Material_Elven_Gilded();
    some<Keyword_t*> Armor_Material_Falmer();
    some<Keyword_t*> Armor_Material_Falmer_Hardened();
    some<Keyword_t*> Armor_Material_Falmer_Heavy();
    some<Keyword_t*> Armor_Material_Falmer_Heavy_Original();
    some<Keyword_t*> Armor_Material_Forsworn();
    some<Keyword_t*> Armor_Material_Forsworn_MS02();
    some<Keyword_t*> Armor_Material_Glass();
    some<Keyword_t*> Armor_Material_Hide();
    some<Keyword_t*> Armor_Material_Hunter();
    some<Keyword_t*> Armor_Material_Imperial_Heavy();
    some<Keyword_t*> Armor_Material_Imperial_Light();
    some<Keyword_t*> Armor_Material_Imperial_Studded();
    some<Keyword_t*> Armor_Material_Iron();
    some<Keyword_t*> Armor_Material_Iron_Banded();
    some<Keyword_t*> Armor_Material_Leather();
    some<Keyword_t*> Armor_Material_Morag_Tong();
    some<Keyword_t*> Armor_Material_Nightingale();
    some<Keyword_t*> Armor_Material_Nordic_Heavy();
    some<Keyword_t*> Armor_Material_Nordic_Light();
    some<Keyword_t*> Armor_Material_Orcish();
    some<Keyword_t*> Armor_Material_Penitus();
    some<Keyword_t*> Armor_Material_Scaled();
    some<Keyword_t*> Armor_Material_Stalhrim_Heavy();
    some<Keyword_t*> Armor_Material_Stalhrim_Light();
    some<Keyword_t*> Armor_Material_Steel();
    some<Keyword_t*> Armor_Material_Steel_Plate();
    some<Keyword_t*> Armor_Material_Stormcloak();
    some<Keyword_t*> Armor_Material_Stormcloak_Bear();
    some<Keyword_t*> Armor_Material_Studded();
    some<Keyword_t*> Armor_Material_Thieves_Guild();
    some<Keyword_t*> Armor_Material_Thieves_Guild_Leader();
    some<Keyword_t*> Armor_Material_Vampire();
    some<Keyword_t*> Armor_Type_Boots();
    some<Keyword_t*> Armor_Type_Clothing();
    some<Keyword_t*> Armor_Type_Cuirass();
    some<Keyword_t*> Armor_Type_Gauntlets();
    some<Keyword_t*> Armor_Type_Heavy();
    some<Keyword_t*> Armor_Type_Helmet();
    some<Keyword_t*> Armor_Type_Jewelry();
    some<Keyword_t*> Armor_Type_Light();
    some<Keyword_t*> Armor_Type_Shield();

    some<Keyword_t*> Clothing_Type_Body();
    some<Keyword_t*> Clothing_Type_Circlet();
    some<Keyword_t*> Clothing_Type_Feet();
    some<Keyword_t*> Clothing_Type_Hands();
    some<Keyword_t*> Clothing_Type_Head();
    some<Keyword_t*> Clothing_Type_Necklace();
    some<Keyword_t*> Clothing_Type_Poor();
    some<Keyword_t*> Clothing_Type_Rich();
    some<Keyword_t*> Clothing_Type_Ring();
    some<Keyword_t*> Crafting_Material_Aetherium();

    some<Keyword_t*> Daedric_Artifact();

    some<Keyword_t*> Jewelry_Type_Expensive();

    some<Keyword_t*> Location_Set_Cave();
    some<Keyword_t*> Location_Set_Cave_Ice();
    some<Keyword_t*> Location_Set_Dwarven_Ruin();
    some<Keyword_t*> Location_Set_Military_Camp();
    some<Keyword_t*> Location_Set_Military_Fort();
    some<Keyword_t*> Location_Set_Nordic_Ruin();
    some<Keyword_t*> Location_Set_Outdoor();
    some<Keyword_t*> Location_Type_Animal_Den();
    some<Keyword_t*> Location_Type_Ash_Spawn_Lair();
    some<Keyword_t*> Location_Type_Bandit_Camp();
    some<Keyword_t*> Location_Type_Barracks();
    some<Keyword_t*> Location_Type_Castle();
    some<Keyword_t*> Location_Type_Cemetery();
    some<Keyword_t*> Location_Type_City();
    some<Keyword_t*> Location_Type_Clearable();
    some<Keyword_t*> Location_Type_Dragon_Lair();
    some<Keyword_t*> Location_Type_Dragon_Priest_Lair();
    some<Keyword_t*> Location_Type_Draugr_Crypt();
    some<Keyword_t*> Location_Type_Dungeon();
    some<Keyword_t*> Location_Type_Dwarven_Automaton_Ruin();
    some<Keyword_t*> Location_Type_Dwelling();
    some<Keyword_t*> Location_Type_Falmer_Hive();
    some<Keyword_t*> Location_Type_Farm();
    some<Keyword_t*> Location_Type_Forsworn_Camp();
    some<Keyword_t*> Location_Type_Giant_Camp();
    some<Keyword_t*> Location_Type_Guild();
    some<Keyword_t*> Location_Type_Habitation();
    some<Keyword_t*> Location_Type_Habitation_With_Inn();
    some<Keyword_t*> Location_Type_Hagraven_Nest();
    some<Keyword_t*> Location_Type_Hold();
    some<Keyword_t*> Location_Type_Hold_Capital();
    some<Keyword_t*> Location_Type_Hold_Major();
    some<Keyword_t*> Location_Type_Hold_Minor();
    some<Keyword_t*> Location_Type_Homestead();
    some<Keyword_t*> Location_Type_Homestead_With_Shrine();
    some<Keyword_t*> Location_Type_House();
    some<Keyword_t*> Location_Type_Inn();
    some<Keyword_t*> Location_Type_Jail();
    some<Keyword_t*> Location_Type_Lumber_Mill();
    some<Keyword_t*> Location_Type_Military_Camp();
    some<Keyword_t*> Location_Type_Military_Fort();
    some<Keyword_t*> Location_Type_Mine();
    some<Keyword_t*> Location_Type_Nature_Pillar();
    some<Keyword_t*> Location_Type_Orc_Stronghold();
    some<Keyword_t*> Location_Type_Player_House();
    some<Keyword_t*> Location_Type_Riekling_Camp();
    some<Keyword_t*> Location_Type_Settlement();
    some<Keyword_t*> Location_Type_Ship();
    some<Keyword_t*> Location_Type_Shipwreck();
    some<Keyword_t*> Location_Type_Spriggan_Grove();
    some<Keyword_t*> Location_Type_Stewards_Dwelling();
    some<Keyword_t*> Location_Type_Store();
    some<Keyword_t*> Location_Type_Temple();
    some<Keyword_t*> Location_Type_Town();
    some<Keyword_t*> Location_Type_Vampire_Lair();
    some<Keyword_t*> Location_Type_Warlock_Lair();
    some<Keyword_t*> Location_Type_Werebear_Lair();
    some<Keyword_t*> Location_Type_Werewolf_Lair();

    some<Keyword_t*> Magic_Damage_Fire();
    some<Keyword_t*> Magic_Damage_Frost();
    some<Keyword_t*> Magic_Damage_Shock();
    some<Keyword_t*> Magic_Vampire_Drain();

    some<Keyword_t*> Vampire();
    some<Keyword_t*> Vendor_Item_Animal_Hide();
    some<Keyword_t*> Vendor_Item_Animal_Part();
    some<Keyword_t*> Vendor_Item_Armor();
    some<Keyword_t*> Vendor_Item_Arrow();
    some<Keyword_t*> Vendor_Item_Book();
    some<Keyword_t*> Vendor_Item_Clothing();
    some<Keyword_t*> Vendor_Item_Clutter();
    some<Keyword_t*> Vendor_Item_Daedric_Artifact();
    some<Keyword_t*> Vendor_Item_Firewood();
    some<Keyword_t*> Vendor_Item_Food();
    some<Keyword_t*> Vendor_Item_Food_Raw();
    some<Keyword_t*> Vendor_Item_Gem();
    some<Keyword_t*> Vendor_Item_Ingredient();
    some<Keyword_t*> Vendor_Item_Jewelry();
    some<Keyword_t*> Vendor_Item_Key();
    some<Keyword_t*> Vendor_Item_Ore_Or_Ingot();
    some<Keyword_t*> Vendor_Item_Poison();
    some<Keyword_t*> Vendor_Item_Potion();
    some<Keyword_t*> Vendor_Item_Recipe();
    some<Keyword_t*> Vendor_Item_Scroll();
    some<Keyword_t*> Vendor_Item_Soul_Gem();
    some<Keyword_t*> Vendor_Item_Spell_Tome();
    some<Keyword_t*> Vendor_Item_Staff();
    some<Keyword_t*> Vendor_Item_Tool();
    some<Keyword_t*> Vendor_Item_Weapon();

    some<Keyword_t*> Weapon_Material_Daedric();
    some<Keyword_t*> Weapon_Material_Dragonbone();
    some<Keyword_t*> Weapon_Material_Draugr();
    some<Keyword_t*> Weapon_Material_Draugr_Honed();
    some<Keyword_t*> Weapon_Material_Dwarven();
    some<Keyword_t*> Weapon_Material_Ebony();
    some<Keyword_t*> Weapon_Material_Elven();
    some<Keyword_t*> Weapon_Material_Falmer();
    some<Keyword_t*> Weapon_Material_Falmer_Honed();
    some<Keyword_t*> Weapon_Material_Glass();
    some<Keyword_t*> Weapon_Material_Imperial();
    some<Keyword_t*> Weapon_Material_Iron();
    some<Keyword_t*> Weapon_Material_Nordic();
    some<Keyword_t*> Weapon_Material_Orcish();
    some<Keyword_t*> Weapon_Material_Silver();
    some<Keyword_t*> Weapon_Material_Stalhrim();
    some<Keyword_t*> Weapon_Material_Steel();
    some<Keyword_t*> Weapon_Material_Wood();
    some<Keyword_t*> Weapon_Type_Battleaxe();
    some<Keyword_t*> Weapon_Type_Bow();
    some<Keyword_t*> Weapon_Type_Dagger();
    some<Keyword_t*> Weapon_Type_Greatsword();
    some<Keyword_t*> Weapon_Type_Mace();
    some<Keyword_t*> Weapon_Type_Staff();
    some<Keyword_t*> Weapon_Type_Sword();
    some<Keyword_t*> Weapon_Type_Waraxe();
    some<Keyword_t*> Weapon_Type_Warhammer();

}}}

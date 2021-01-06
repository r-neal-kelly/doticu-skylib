/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/cstring.h"
#include "doticu_skylib/enum.h"
#include "doticu_skylib/interface.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/math.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/string.h"
#include "doticu_skylib/version.h"

#include "doticu_skylib/form_id.h"

namespace doticu_skylib {

    class Actor_Value_e;
    class Actor_Value_Modifier_e;
    class Form_Type_e;
    class Logic_Gate_e;
    class Operator_e;
    class Rarity_e;
    class Relation_e;
    class Script_Type_e;
    class Sex_e;
    class Vitality_e;

    class Active_Magic_Effects_c;
    class Actor_Base_Data_c;
    class AI_c;
    class Attack_c;
    class Biped_Model_c;
    class Biped_Object_c;
    class Container_c;
    class Description_c;
    class Destructible_c;
    class Form_Data_c;
    class Harvest_c;
    class Keywords_c;
    class Leveled_c;
    class Model_c;
    class Model_Alternates_c;
    class Name_c;
    class Openable_c;
    class Package_Override_c;
    class Perks_c;
    class Race_c;
    class Skin_c;

    class Active_Magic_Effect_t;
    class Actor_t;
    class Actor_Base_t;
    class Actor_State_t;
    class Actor_Values_t;
    class Alias_Base_t;
    class Alias_Reference_t;
    class Animated_Object_t;
    class Armor_t;
    class Bound_Object_t;
    class Cell_t;
    class Consts_t;
    class Effect_Shader_t;
    class Faction_t;
    class Faction_And_Rank_t;
    class Form_t;
    class Form_Factory_i;
    class Form_List_t;
    class Game_t;
    class Game_Heap_t;
    class Global_t;
    class Keyword_t;
    class Leveled_Actor_Base_t;
    class Location_t;
    class Magic_Target_t;
    class Misc_t;
    class Mod_t;
    class Object_t;
    class OS_t;
    class Player_t;
    class Quest_t;
    class Race_t;
    class Reference_t;
    class Script_t;
    class Translations_t;
    class UI_t;
    class Worldspace_t;

    class Aliases_x;
    class Data_x;
    class Factions_And_Ranks_x;
    class List_x;
    class Location_x;

}

/*namespace doticu_skylib {

    typedef TESObjectMISC   Misc_t;
    typedef TESObjectSTAT   Static_t;
    typedef TESObjectWEAP   Weapon_t;
    typedef TESObjectARMO   Armor_t;

    typedef BGSOutfit       Outfit_t;

}*/

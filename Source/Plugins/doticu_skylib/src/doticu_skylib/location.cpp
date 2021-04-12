/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/const_keywords.h"
#include "doticu_skylib/location.h"

namespace doticu_skylib {

    Bool_t Location_t::Is_Likely_Civilized() const
    {
        if (Has_Keyword(Const::Keyword::Location_Type_Dwelling()) ||
            Has_Keyword(Const::Keyword::Location_Type_Habitation()) ||
            Has_Keyword(Const::Keyword::Location_Type_Habitation_With_Inn())) {
            return true;
        } else if (Has_Keyword(Const::Keyword::Location_Type_Dungeon())) {
            return false;
        } else if (Has_Keyword(Const::Keyword::Location_Type_Settlement()) ||
                   Has_Keyword(Const::Keyword::Location_Type_City()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Town()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Orc_Stronghold()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Guild()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Inn()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Farm()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Mine()) ||
                   Has_Keyword(Const::Keyword::Location_Type_House()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Store()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Lumber_Mill()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Player_House()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Homestead()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Homestead_With_Shrine()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Castle()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Barracks()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Cemetery()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Temple()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Jail()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Stewards_Dwelling())) {
            return true;
        } else {
            return false;
        }
    }

    Bool_t Location_t::Is_Likely_Dangerous() const
    {
        if (Is_Likely_Civilized()) {
            return false;
        } else if (Has_Keyword(Const::Keyword::Location_Type_Dungeon()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Clearable()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Animal_Den()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Ash_Spawn_Lair()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Bandit_Camp()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Dragon_Lair()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Dragon_Priest_Lair()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Draugr_Crypt()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Dwarven_Automaton_Ruin()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Falmer_Hive()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Forsworn_Camp()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Giant_Camp()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Hagraven_Nest()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Military_Camp()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Military_Fort()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Riekling_Camp()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Ship()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Shipwreck()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Spriggan_Grove()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Vampire_Lair()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Warlock_Lair()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Werebear_Lair()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Werewolf_Lair()) ||
                   Has_Keyword(Const::Keyword::Location_Set_Cave()) ||
                   Has_Keyword(Const::Keyword::Location_Set_Cave_Ice()) ||
                   Has_Keyword(Const::Keyword::Location_Set_Dwarven_Ruin()) ||
                   Has_Keyword(Const::Keyword::Location_Set_Military_Camp()) ||
                   Has_Keyword(Const::Keyword::Location_Set_Military_Fort()) ||
                   Has_Keyword(Const::Keyword::Location_Set_Nordic_Ruin())) {
            return true;
        } else {
            return false;
        }
    }

    Bool_t Location_t::Is_Likely_Regional() const
    {
        if (Is_Likely_Civilized() || Is_Likely_Dangerous()) {
            return false;
        } else if (Has_Keyword(Const::Keyword::Location_Type_Hold()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Hold_Capital()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Hold_Major()) ||
                   Has_Keyword(Const::Keyword::Location_Type_Hold_Minor())) {
            return true;
        } else {
            return false;
        }
    }

    String_t Location_t::Any_Name()
    {
        const char* name = Name();
        if (!name || !name[0]) {
            name = Get_Editor_ID();
            if (!name || !name[0]) {
                return Form_ID_String();
            } else {
                return name;
            }
        } else {
            return name;
        }
    }

}

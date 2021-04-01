/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/armor.h"
#include "doticu_skylib/const_keywords.h"

namespace doticu_skylib {

    Bool_t Armor_t::Is_Likely_Armor() const
    {
        return Is_Light_Armor() || Is_Heavy_Armor() || Is_Shield();
    }

    Bool_t Armor_t::Is_Surely_Armor() const
    {
        return Is_Likely_Armor() || Is_Helmet() || Is_Cuirass() || Is_Gauntlets() || Is_Boots();
    }

    Bool_t Armor_t::Is_Light_Armor() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Type_Light());
    }

    Bool_t Armor_t::Is_Heavy_Armor() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Type_Heavy());
    }

    Bool_t Armor_t::Is_Helmet() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Type_Helmet());
    }

    Bool_t Armor_t::Is_Cuirass() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Type_Cuirass());
    }

    Bool_t Armor_t::Is_Gauntlets() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Type_Gauntlets());
    }

    Bool_t Armor_t::Is_Boots() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Type_Boots());
    }

    Bool_t Armor_t::Is_Shield() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Type_Shield());
    }

    Bool_t Armor_t::Is_Likely_Clothing() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Type_Clothing());
    }

    Bool_t Armor_t::Is_Surely_Clothing() const
    {
        return Is_Likely_Clothing() || Is_Hat() || Is_Shirt() || Is_Gloves() || Is_Shoes();
    }

    Bool_t Armor_t::Is_Lower_Class_Clothing() const
    {
        return Component_Has_Keyword(Const::Keyword::Clothing_Type_Poor());
    }

    Bool_t Armor_t::Is_Likely_Middle_Class_Clothing() const
    {
        return Is_Likely_Clothing() && !Is_Lower_Class_Clothing() && !Is_Upper_Class_Clothing();
    }

    Bool_t Armor_t::Is_Surely_Middle_Class_Clothing() const
    {
        return Is_Surely_Clothing() && !Is_Lower_Class_Clothing() && !Is_Upper_Class_Clothing();
    }

    Bool_t Armor_t::Is_Upper_Class_Clothing() const
    {
        return Component_Has_Keyword(Const::Keyword::Clothing_Type_Rich());
    }

    Bool_t Armor_t::Is_Hat() const
    {
        return Component_Has_Keyword(Const::Keyword::Clothing_Type_Head());
    }

    Bool_t Armor_t::Is_Shirt() const
    {
        return Component_Has_Keyword(Const::Keyword::Clothing_Type_Body());
    }

    Bool_t Armor_t::Is_Gloves() const
    {
        return Component_Has_Keyword(Const::Keyword::Clothing_Type_Hands());
    }

    Bool_t Armor_t::Is_Shoes() const
    {
        return Component_Has_Keyword(Const::Keyword::Clothing_Type_Feet());
    }

    Bool_t Armor_t::Is_Likely_Jewelry() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Type_Jewelry());
    }

    Bool_t Armor_t::Is_Surely_Jewelry() const
    {
        return Is_Likely_Jewelry() || Is_Circlet() || Is_Necklace() || Is_Ring();
    }

    Bool_t Armor_t::Is_Likely_Cheap_Jewelry() const
    {
        return Is_Likely_Jewelry() && !Is_Expensive_Jewelry();
    }

    Bool_t Armor_t::Is_Surely_Cheap_Jewelry() const
    {
        return Is_Surely_Jewelry() && !Is_Expensive_Jewelry();
    }

    Bool_t Armor_t::Is_Expensive_Jewelry() const
    {
        return Component_Has_Keyword(Const::Keyword::Jewelry_Type_Expensive());
    }

    Bool_t Armor_t::Is_Circlet() const
    {
        return Component_Has_Keyword(Const::Keyword::Clothing_Type_Circlet());
    }

    Bool_t Armor_t::Is_Necklace() const
    {
        return Component_Has_Keyword(Const::Keyword::Clothing_Type_Necklace());
    }

    Bool_t Armor_t::Is_Ring() const
    {
        return Component_Has_Keyword(Const::Keyword::Clothing_Type_Ring());
    }

    Bool_t Armor_t::Is_For_Head() const
    {
        return Is_Helmet() || Is_Hat();
    }

    Bool_t Armor_t::Is_For_Forehead() const
    {
        return Is_Circlet();
    }

    Bool_t Armor_t::Is_For_Neck() const
    {
        return Is_Necklace();
    }

    Bool_t Armor_t::Is_For_Body() const
    {
        return Is_Cuirass() || Is_Shirt();
    }

    Bool_t Armor_t::Is_For_Forearm() const
    {
        return Is_Shield();
    }

    Bool_t Armor_t::Is_For_Hands() const
    {
        return Is_Gauntlets() || Is_Gloves();
    }

    Bool_t Armor_t::Is_For_Finger() const
    {
        return Is_Ring();
    }

    Bool_t Armor_t::Is_For_Feet() const
    {
        return Is_Boots() || Is_Shoes();
    }

    Bool_t Armor_t::Is_Aetherium_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Crafting_Material_Aetherium());
    }

    Bool_t Armor_t::Is_Blades_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Blades());
    }

    Bool_t Armor_t::Is_Bonemold_Heavy_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Bonemold_Heavy());
    }

    Bool_t Armor_t::Is_Bonemold_Light_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Bonemold_Light());
    }

    Bool_t Armor_t::Is_Chitin_Heavy_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Chitin_Heavy());
    }

    Bool_t Armor_t::Is_Chitin_Light_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Chitin_Light());
    }

    Bool_t Armor_t::Is_Daedric_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Daedric());
    }

    Bool_t Armor_t::Is_Dark_Brotherhood_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Dark_Brotherhood());
    }

    Bool_t Armor_t::Is_Dawnguard_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Dawnguard());
    }

    Bool_t Armor_t::Is_Dragonplate_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Dragonplate());
    }

    Bool_t Armor_t::Is_Dragonscale_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Dragonscale());
    }

    Bool_t Armor_t::Is_Dwarven_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Dwarven());
    }

    Bool_t Armor_t::Is_Ebony_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Ebony());
    }

    Bool_t Armor_t::Is_Elven_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Elven());
    }

    Bool_t Armor_t::Is_Elven_Gilded_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Elven_Gilded());
    }

    Bool_t Armor_t::Is_Falmer_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Falmer());
    }

    Bool_t Armor_t::Is_Falmer_Hardened_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Falmer_Hardened());
    }

    Bool_t Armor_t::Is_Falmer_Heavy_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Falmer_Heavy());
    }

    Bool_t Armor_t::Is_Falmer_Heavy_Original_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Falmer_Heavy_Original());
    }

    Bool_t Armor_t::Is_Forsworn_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Forsworn());
    }

    Bool_t Armor_t::Is_Forsworn_MS02_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Forsworn_MS02());
    }

    Bool_t Armor_t::Is_Glass_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Glass());
    }

    Bool_t Armor_t::Is_Hide_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Hide());
    }

    Bool_t Armor_t::Is_Hunter_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Hunter());
    }

    Bool_t Armor_t::Is_Imperial_Heavy_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Imperial_Heavy());
    }

    Bool_t Armor_t::Is_Imperial_Light_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Imperial_Light());
    }

    Bool_t Armor_t::Is_Imperial_Studded_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Imperial_Studded());
    }

    Bool_t Armor_t::Is_Iron_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Iron());
    }

    Bool_t Armor_t::Is_Iron_Banded_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Iron_Banded());
    }

    Bool_t Armor_t::Is_Leather_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Leather());
    }

    Bool_t Armor_t::Is_Morag_Tong_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Morag_Tong());
    }

    Bool_t Armor_t::Is_Nightingale_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Nightingale());
    }

    Bool_t Armor_t::Is_Nordic_Heavy_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Nordic_Heavy());
    }

    Bool_t Armor_t::Is_Nordic_Light_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Nordic_Light());
    }

    Bool_t Armor_t::Is_Orcish_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Orcish());
    }

    Bool_t Armor_t::Is_Penitus_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Penitus());
    }

    Bool_t Armor_t::Is_Scaled_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Scaled());
    }

    Bool_t Armor_t::Is_Stalhrim_Heavy_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Stalhrim_Heavy());
    }

    Bool_t Armor_t::Is_Stalhrim_Light_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Stalhrim_Light());
    }

    Bool_t Armor_t::Is_Steel_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Steel());
    }

    Bool_t Armor_t::Is_Steel_Plate_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Steel_Plate());
    }

    Bool_t Armor_t::Is_Stormcloak_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Stormcloak());
    }

    Bool_t Armor_t::Is_Stormcloak_Bear_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Stormcloak_Bear());
    }

    Bool_t Armor_t::Is_Studded_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Studded());
    }

    Bool_t Armor_t::Is_Thieves_Guild_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Thieves_Guild());
    }

    Bool_t Armor_t::Is_Thieves_Guild_Leader_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Thieves_Guild_Leader());
    }

    Bool_t Armor_t::Is_Vampire_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Armor_Material_Vampire());
    }

    Bool_t Armor_t::Is_Daedric_Artifact() const
    {
        return
            Component_Has_Keyword(Const::Keyword::Daedric_Artifact()) ||
            Component_Has_Keyword(Const::Keyword::Vendor_Item_Daedric_Artifact());
    }

    void Armor_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Armor_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "component_name: %s", Component_Name());

        if (Is_Likely_Armor() != Is_Surely_Armor()) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "likely_armor and surely_armor mismatch");
        }

        if (Is_Likely_Clothing() != Is_Surely_Clothing()) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "likely_clothing and surely_clothing mismatch");
        }

        if (Is_Likely_Jewelry() != Is_Surely_Jewelry()) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "likely_jewelry and surely_jewelry mismatch");
        }

        SKYLIB_LOG(indent + SKYLIB_TAB + "keywords:");
        Keywords_c::Log_Component_Keywords(indent + SKYLIB_TAB + SKYLIB_TAB);

        SKYLIB_LOG(indent + "}");
    }

}

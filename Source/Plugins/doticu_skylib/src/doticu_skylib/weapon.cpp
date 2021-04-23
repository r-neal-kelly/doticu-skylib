/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/const_keywords.h"
#include "doticu_skylib/keyword.h"
#include "doticu_skylib/weapon.h"

namespace doticu_skylib {

    Bool_t Weapon_t::Is_Enchanted() const
    {
        return !!this->enchantment;
    }

    Bool_t Weapon_t::Is_Sword() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Type_Sword());
    }

    Bool_t Weapon_t::Is_Greatsword() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Type_Greatsword());
    }

    Bool_t Weapon_t::Is_Waraxe() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Type_Waraxe());
    }

    Bool_t Weapon_t::Is_Battleaxe() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Type_Battleaxe());
    }

    Bool_t Weapon_t::Is_Mace() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Type_Mace());
    }

    Bool_t Weapon_t::Is_Warhammer() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Type_Warhammer());
    }

    Bool_t Weapon_t::Is_Dagger() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Type_Dagger());
    }

    Bool_t Weapon_t::Is_Staff() const
    {
        return
            Component_Has_Keyword(Const::Keyword::Weapon_Type_Staff()) ||
            Component_Has_Keyword(Const::Keyword::Vendor_Item_Staff());
    }

    Bool_t Weapon_t::Is_Bow() const
    {
        return
            Component_Has_Keyword(Const::Keyword::Weapon_Type_Bow()) &&
            this->weapon_animation_type == Weapon_Animation_Type_e::BOW;
    }

    Bool_t Weapon_t::Is_Crossbow() const
    {
        return
            Component_Has_Keyword(Const::Keyword::Weapon_Type_Bow()) &&
            this->weapon_animation_type == Weapon_Animation_Type_e::CROSSBOW;
    }

    Bool_t Weapon_t::Is_Bow_Or_Crossbow() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Type_Bow());
    }

    Bool_t Weapon_t::Is_Wood_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Wood());
    }

    Bool_t Weapon_t::Is_Iron_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Iron());
    }

    Bool_t Weapon_t::Is_Steel_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Steel());
    }

    Bool_t Weapon_t::Is_Silver_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Silver());
    }

    Bool_t Weapon_t::Is_Imperial_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Imperial());
    }

    Bool_t Weapon_t::Is_Nordic_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Nordic());
    }

    Bool_t Weapon_t::Is_Draugr_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Draugr());
    }

    Bool_t Weapon_t::Is_Draugr_Honed_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Draugr_Honed());
    }

    Bool_t Weapon_t::Is_Falmer_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Falmer());
    }

    Bool_t Weapon_t::Is_Falmer_Honed_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Falmer_Honed());
    }

    Bool_t Weapon_t::Is_Dwarven_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Dwarven());
    }

    Bool_t Weapon_t::Is_Orcish_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Orcish());
    }

    Bool_t Weapon_t::Is_Elven_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Elven());
    }

    Bool_t Weapon_t::Is_Glass_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Glass());
    }

    Bool_t Weapon_t::Is_Ebony_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Ebony());
    }

    Bool_t Weapon_t::Is_Daedric_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Daedric());
    }

    Bool_t Weapon_t::Is_Dragonbone_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Dragonbone());
    }

    Bool_t Weapon_t::Is_Stalhrim_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Stalhrim());
    }

    Bool_t Weapon_t::Is_Aetherium_Material() const
    {
        return Component_Has_Keyword(Const::Keyword::Crafting_Material_Aetherium());
    }

    Bool_t Weapon_t::Is_Daedric_Artifact() const
    {
        return
            Component_Has_Keyword(Const::Keyword::Daedric_Artifact()) ||
            Component_Has_Keyword(Const::Keyword::Vendor_Item_Daedric_Artifact());
    }

    void Weapon_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Weapon_t::Log");
        SKYLIB_LOG(indent + "{");

        Keywords_c::Log_Component_Keywords(indent + SKYLIB_TAB);

        SKYLIB_LOG(indent + "}");
    }

}

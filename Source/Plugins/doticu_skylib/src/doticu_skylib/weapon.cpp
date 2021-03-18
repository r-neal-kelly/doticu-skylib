/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/const_keyword.h"
#include "doticu_skylib/keyword.h"
#include "doticu_skylib/weapon.h"

namespace doticu_skylib {

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

    Bool_t Weapon_t::Is_Wood() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Wood());
    }

    Bool_t Weapon_t::Is_Iron() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Iron());
    }

    Bool_t Weapon_t::Is_Steel() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Steel());
    }

    Bool_t Weapon_t::Is_Silver() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Silver());
    }

    Bool_t Weapon_t::Is_Imperial() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Imperial());
    }

    Bool_t Weapon_t::Is_Nordic() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Nordic());
    }

    Bool_t Weapon_t::Is_Draugr() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Draugr());
    }

    Bool_t Weapon_t::Is_Draugr_Honed() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Draugr_Honed());
    }

    Bool_t Weapon_t::Is_Falmer() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Falmer());
    }

    Bool_t Weapon_t::Is_Falmer_Honed() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Falmer_Honed());
    }

    Bool_t Weapon_t::Is_Dwarven() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Dwarven());
    }

    Bool_t Weapon_t::Is_Orcish() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Orcish());
    }

    Bool_t Weapon_t::Is_Elven() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Elven());
    }

    Bool_t Weapon_t::Is_Glass() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Glass());
    }

    Bool_t Weapon_t::Is_Ebony() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Ebony());
    }

    Bool_t Weapon_t::Is_Daedric() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Daedric());
    }

    Bool_t Weapon_t::Is_Dragonbone() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Dragonbone());
    }

    Bool_t Weapon_t::Is_Stalhrim() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Stalhrim());
    }

    Bool_t Weapon_t::Is_Aetherium() const
    {
        return Component_Has_Keyword(Const::Keyword::Weapon_Material_Aetherium());
    }

    Bool_t Weapon_t::Is_Daedric_Artifact() const
    {
        return
            Component_Has_Keyword(Const::Keyword::Daedric_Artifact()) ||
            Component_Has_Keyword(Const::Keyword::Vendor_Item_Daedric_Artifact());
    }

}

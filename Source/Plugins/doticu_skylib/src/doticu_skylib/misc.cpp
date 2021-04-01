/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/const_keywords.h"
#include "doticu_skylib/misc.h"

namespace doticu_skylib {

    Bool_t Misc_t::Is_Animal_Hide() const
    {
        return Component_Has_Keyword(Const::Keyword::Vendor_Item_Animal_Hide());
    }

    Bool_t Misc_t::Is_Animal_Part() const
    {
        return Component_Has_Keyword(Const::Keyword::Vendor_Item_Animal_Part());
    }

    Bool_t Misc_t::Is_Child_Clothing() const
    {
        return Component_Has_Keyword(Const::Keyword::Vendor_Item_Clothing());
    }

    Bool_t Misc_t::Is_Firewood() const
    {
        return Component_Has_Keyword(Const::Keyword::Vendor_Item_Firewood());
    }

    Bool_t Misc_t::Is_Gem() const
    {
        return Component_Has_Keyword(Const::Keyword::Vendor_Item_Gem());
    }

    Bool_t Misc_t::Is_Ore_Or_Ingot() const
    {
        return Component_Has_Keyword(Const::Keyword::Vendor_Item_Ore_Or_Ingot());
    }

    Bool_t Misc_t::Is_Tool() const
    {
        return Component_Has_Keyword(Const::Keyword::Vendor_Item_Tool());
    }

    Bool_t Misc_t::Is_Daedric_Artifact() const
    {
        return
            Component_Has_Keyword(Const::Keyword::Daedric_Artifact()) ||
            Component_Has_Keyword(Const::Keyword::Vendor_Item_Daedric_Artifact());
    }

    void Misc_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Misc_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "component_name: %s", Component_Name());
        SKYLIB_LOG(indent + SKYLIB_TAB + "form_id: %s", this->form_id.As_String());

        SKYLIB_LOG(indent + SKYLIB_TAB + "keywords:");
        Keywords_c::Log_Component_Keywords(indent + SKYLIB_TAB + SKYLIB_TAB);

        SKYLIB_LOG(indent + "}");
    }

}

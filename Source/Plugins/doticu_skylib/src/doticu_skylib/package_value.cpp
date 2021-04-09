/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.inl"
#include "doticu_skylib/package_value.h"
#include "doticu_skylib/package_value_bool.h"
#include "doticu_skylib/package_value_float.h"
#include "doticu_skylib/package_value_int.h"
#include "doticu_skylib/package_value_list.h"
#include "doticu_skylib/package_value_location.h"
#include "doticu_skylib/package_value_reference.h"
#include "doticu_skylib/package_value_target.h"
#include "doticu_skylib/package_value_topic.h"

namespace doticu_skylib {

    Package_Value_Type_e Package_Value_t::Type() const
    {
        if (Is_Bool())              return Package_Value_Type_e::BOOL;
        else if (Is_Float())        return Package_Value_Type_e::FLOAT;
        else if (Is_Int())          return Package_Value_Type_e::INT;
        else if (Is_List())         return Package_Value_Type_e::LIST;
        else if (Is_Location())     return Package_Value_Type_e::LOCATION;
        else if (Is_Reference())    return Package_Value_Type_e::REFERENCE;
        else if (Is_Target())       return Package_Value_Type_e::TARGET;
        else if (Is_Topic())        return Package_Value_Type_e::TOPIC;
        else                        return Package_Value_Type_e::_NONE_;
    }

    Bool_t Package_Value_t::Is_Bool() const
    {
        return As_Bool() != none<Package_Value_Bool_t*>();
    }

    Bool_t Package_Value_t::Is_Float() const
    {
        return As_Float() != none<Package_Value_Float_t*>();
    }

    Bool_t Package_Value_t::Is_Int() const
    {
        return As_Int() != none<Package_Value_Int_t*>();
    }

    Bool_t Package_Value_t::Is_List() const
    {
        return As_List() != none<Package_Value_List_t*>();
    }

    Bool_t Package_Value_t::Is_Location() const
    {
        return As_Location() != none<Package_Value_Location_t*>();
    }

    Bool_t Package_Value_t::Is_Reference() const
    {
        return As_Reference() != none<Package_Value_Reference_t*>();
    }

    Bool_t Package_Value_t::Is_Target() const
    {
        return As_Target() != none<Package_Value_Target_t*>();
    }

    Bool_t Package_Value_t::Is_Topic() const
    {
        return As_Topic() != none<Package_Value_Topic_t*>();
    }

    maybe<Package_Value_Bool_t*> Package_Value_t::As_Bool() const
    {
        return Game_t::Runtime_Cast<Package_Value_t, Package_Value_Bool_t>(this);
    }

    maybe<Package_Value_Float_t*> Package_Value_t::As_Float() const
    {
        return Game_t::Runtime_Cast<Package_Value_t, Package_Value_Float_t>(this);
    }

    maybe<Package_Value_Int_t*> Package_Value_t::As_Int() const
    {
        return Game_t::Runtime_Cast<Package_Value_t, Package_Value_Int_t>(this);
    }

    maybe<Package_Value_List_t*> Package_Value_t::As_List() const
    {
        return Game_t::Runtime_Cast<Package_Value_t, Package_Value_List_t>(this);
    }

    maybe<Package_Value_Location_t*> Package_Value_t::As_Location() const
    {
        return Game_t::Runtime_Cast<Package_Value_t, Package_Value_Location_t>(this);
    }

    maybe<Package_Value_Reference_t*> Package_Value_t::As_Reference() const
    {
        return Game_t::Runtime_Cast<Package_Value_t, Package_Value_Reference_t>(this);
    }

    maybe<Package_Value_Target_t*> Package_Value_t::As_Target() const
    {
        return Game_t::Runtime_Cast<Package_Value_t, Package_Value_Target_t>(this);
    }

    maybe<Package_Value_Topic_t*> Package_Value_t::As_Topic() const
    {
        return Game_t::Runtime_Cast<Package_Value_t, Package_Value_Topic_t>(this);
    }

    void Package_Value_t::Log(std::string indent) const
    {
        if (Is_Bool())              As_Bool()->Log(indent);
        else if (Is_Float())        As_Float()->Log(indent);
        else if (Is_Int())          As_Int()->Log(indent);
        else if (Is_List())         As_List()->Log(indent);
        else if (Is_Location())     As_Location()->Log(indent);
        else if (Is_Reference())    As_Reference()->Log(indent);
        else if (Is_Target())       As_Target()->Log(indent);
        else if (Is_Topic())        As_Topic()->Log(indent);
        else {
            SKYLIB_LOG(indent + "Package_Value_t::Log");
            SKYLIB_LOG(indent + "{");

            SKYLIB_LOG(indent + SKYLIB_TAB + "unknown type");
            SKYLIB_LOG(indent + SKYLIB_TAB + "v_table: 0x%p", Game_t::V_Table_Offset(this));

            SKYLIB_LOG(indent + "}");
        }
    }

}

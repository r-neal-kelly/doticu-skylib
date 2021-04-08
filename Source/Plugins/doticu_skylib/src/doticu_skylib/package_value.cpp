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
        Word_t v_table_offset = Game_t::V_Table_Offset(this);
        if (v_table_offset == Package_Value_Bool_t::Offset_e::V_TABLE)              return Package_Value_Type_e::BOOL;
        else if (v_table_offset == Package_Value_Float_t::Offset_e::V_TABLE)        return Package_Value_Type_e::FLOAT;
        else if (v_table_offset == Package_Value_Int_t::Offset_e::V_TABLE)          return Package_Value_Type_e::INT;
        else if (v_table_offset == Package_Value_List_t::Offset_e::V_TABLE)         return Package_Value_Type_e::LIST;
        else if (v_table_offset == Package_Value_Location_t::Offset_e::V_TABLE)     return Package_Value_Type_e::LOCATION;
        else if (v_table_offset == Package_Value_Reference_t::Offset_e::V_TABLE)    return Package_Value_Type_e::REFERENCE;
        else if (v_table_offset == Package_Value_Target_t::Offset_e::V_TABLE)       return Package_Value_Type_e::TARGET;
        else if (v_table_offset == Package_Value_Topic_t::Offset_e::V_TABLE)        return Package_Value_Type_e::TOPIC;
        else                                                                        return Package_Value_Type_e::_NONE_;
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
        if (Is_Bool())              static_cast<const Package_Value_Bool_t*>(this)->Log(indent);
        else if (Is_Float())        static_cast<const Package_Value_Float_t*>(this)->Log(indent);
        else if (Is_Int())          static_cast<const Package_Value_Int_t*>(this)->Log(indent);
        else if (Is_List())         static_cast<const Package_Value_List_t*>(this)->Log(indent);
        else if (Is_Location())     static_cast<const Package_Value_Location_t*>(this)->Log(indent);
        else if (Is_Reference())    static_cast<const Package_Value_Reference_t*>(this)->Log(indent);
        else if (Is_Target())       static_cast<const Package_Value_Target_t*>(this)->Log(indent);
        else if (Is_Topic())        static_cast<const Package_Value_Topic_t*>(this)->Log(indent);
        else {
            SKYLIB_LOG(indent + "Package_Value_t::Log");
            SKYLIB_LOG(indent + "{");

            SKYLIB_LOG(indent + SKYLIB_TAB + "unknown type");
            SKYLIB_LOG(indent + SKYLIB_TAB + "v_table: 0x%p", Game_t::V_Table_Offset(this));

            SKYLIB_LOG(indent + "}");
        }
    }

}

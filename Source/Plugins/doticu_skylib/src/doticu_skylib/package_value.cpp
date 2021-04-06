/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.h"
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

    void Package_Value_t::Log(std::string indent) const
    {
        if (Type() == Package_Value_Type_e::BOOL)           static_cast<const Package_Value_Bool_t*>(this)->Log(indent);
        else if (Type() == Package_Value_Type_e::FLOAT)     static_cast<const Package_Value_Float_t*>(this)->Log(indent);
        else if (Type() == Package_Value_Type_e::INT)       static_cast<const Package_Value_Int_t*>(this)->Log(indent);
        else if (Type() == Package_Value_Type_e::LIST)      static_cast<const Package_Value_List_t*>(this)->Log(indent);
        else if (Type() == Package_Value_Type_e::LOCATION)  static_cast<const Package_Value_Location_t*>(this)->Log(indent);
        else if (Type() == Package_Value_Type_e::REFERENCE) static_cast<const Package_Value_Reference_t*>(this)->Log(indent);
        else if (Type() == Package_Value_Type_e::TARGET)    static_cast<const Package_Value_Target_t*>(this)->Log(indent);
        else if (Type() == Package_Value_Type_e::TOPIC)     static_cast<const Package_Value_Topic_t*>(this)->Log(indent);
        else {
            SKYLIB_LOG(indent + "Package_Value_t::Log");
            SKYLIB_LOG(indent + "{");

            SKYLIB_LOG(indent + SKYLIB_TAB + "unknown type");
            SKYLIB_LOG(indent + SKYLIB_TAB + "v_table: 0x%p", Game_t::V_Table_Offset(this));

            SKYLIB_LOG(indent + "}");
        }
    }

}

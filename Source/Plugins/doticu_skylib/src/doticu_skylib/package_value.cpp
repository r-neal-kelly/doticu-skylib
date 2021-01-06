/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.h"
#include "doticu_skylib/package_bool_value.h"
#include "doticu_skylib/package_float_value.h"
#include "doticu_skylib/package_int_value.h"
#include "doticu_skylib/package_location_value.h"
#include "doticu_skylib/package_reference_value.h"
#include "doticu_skylib/package_topic_value.h"

namespace doticu_skylib {

    Package_Value_e Package_Value_t::Type() const
    {
        Word_t v_table_offset = Game_t::V_Table_Offset(this);
        if (v_table_offset == Package_Bool_Value_t::Offset_e::V_TABLE) {
            return Package_Value_e::BOOL;
        } else if (v_table_offset == Package_Int_Value_t::Offset_e::V_TABLE) {
            return Package_Value_e::INT;
        } else if (v_table_offset == Package_Float_Value_t::Offset_e::V_TABLE) {
            return Package_Value_e::FLOAT;
        } else if (v_table_offset == Package_Location_Value_t::Offset_e::V_TABLE) {
            return Package_Value_e::LOCATION;
        } else if (v_table_offset == Package_Reference_Value_t::Offset_e::V_TABLE) {
            return Package_Value_e::REFERENCE;
        } else if (v_table_offset == Package_Topic_Value_t::Offset_e::V_TABLE) {
            return Package_Value_e::TOPIC;
        } else {
            return Package_Value_e::NONE;
        }
    }

}

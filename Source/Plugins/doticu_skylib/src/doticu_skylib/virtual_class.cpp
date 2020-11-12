/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/utils.h"
#include "doticu_skylib/virtual_class.h"
#include "doticu_skylib/virtual_machine.h"

namespace doticu_skylib { namespace Virtual {

    Class_t* Class_t::Fetch(String_t class_name, Bool_t do_auto_decrement)
    {
        Machine_t* const machine = Machine_t::Self();
        if (machine) {
            Class_t* info_out = nullptr;
            machine->Load_Class_Info(&class_name, &info_out);
            if (do_auto_decrement && info_out->ref_count > 1) {
                info_out->Free();
            }
            return info_out;
        } else {
            return nullptr;
        }
    }

    Class_t* Class_t::Fetch(Form_Type_t form_type, Bool_t do_auto_decrement)
    {
        Machine_t* const machine = Machine_t::Self();
        if (machine) {
            Class_t* info_out = nullptr;
            machine->Load_Class_Info2(form_type, &info_out);
            if (do_auto_decrement && info_out->ref_count > 1) {
                info_out->Free();
            }
            return info_out;
        } else {
            return nullptr;
        }
    }

    size_t Class_t::Count_Setting_Infos()
    {
        Word_t flags = static_cast<Word_t>(flags_20);
        Word_t six_bits = static_cast<Word_t>(0x3F);
        return (flags >> 2) & six_bits;
    }

    size_t Class_t::Count_Variable_Infos()
    {
        Word_t flags = static_cast<Word_t>(flags_20);
        Word_t ten_bits = static_cast<Word_t>(0x3FF);
        return (flags >> 8) & ten_bits;
    }

    size_t Class_t::Count_Default_Infos()
    {
        Word_t flags = static_cast<Word_t>(flags_24);
        Word_t ten_bits = static_cast<Word_t>(0x3FF);
        return flags & ten_bits;
    }

    size_t Class_t::Count_Property_Infos()
    {
        Word_t flags = static_cast<Word_t>(flags_24);
        Word_t ten_bits = static_cast<Word_t>(0x3FF);
        return (flags >> 10) & ten_bits;
    }

    Setting_Info_t* Class_t::Setting_Infos()
    {
        return reinterpret_cast<Setting_Info_t*>(data);
    }

    Variable_Info_t* Class_t::Variable_Infos()
    {
        return reinterpret_cast<Variable_Info_t*>(Setting_Infos() + Count_Setting_Infos());
    }

    Default_Info_t* Class_t::Default_Infos()
    {
        return reinterpret_cast<Default_Info_t*>(Variable_Infos() + Count_Variable_Infos());
    }

    Property_Info_t* Class_t::Property_Infos()
    {
        return reinterpret_cast<Property_Info_t*>(Default_Infos() + Count_Default_Infos());
    }

    Index_t Class_t::Variable_Index(String_t variable_name)
    {
        Variable_Info_t* variables = Variable_Infos();
        for (Index_t idx = 0, size = Count_Variable_Infos(); idx < size; idx += 1) {
            if (CString_t::Is_Same(variables[idx].name, variable_name, true)) {
                return idx;
            }
        }
        return -1;
    }

    Index_t Class_t::Property_Index(String_t property_name)
    {
        Property_Info_t* properties = Property_Infos();
        for (Index_t idx = 0, size = Count_Property_Infos(); idx < size; idx += 1) {
            if (CString_t::Is_Same(properties[idx].name, property_name, true)) {
                return properties[idx].auto_var_idx;
            }
        }
        return -1;
    }

    Property_Info_t* Class_t::Property_Info(String_t property_name)
    {
        Property_Info_t* properties = Property_Infos();
        for (Index_t idx = 0, size = Count_Property_Infos(); idx < size; idx += 1) {
            if (CString_t::Is_Same(properties[idx].name, property_name, true)) {
                return &properties[idx];
            }
        }
        return nullptr;
    }

    void Class_t::Hold()
    {
        reinterpret_cast<VMClassInfo*>(this)->AddRef();
    }

    void Class_t::Free()
    {
        reinterpret_cast<VMClassInfo*>(this)->Release();
    }

}}

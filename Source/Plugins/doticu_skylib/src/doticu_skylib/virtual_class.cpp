/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cstring.h"

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

    Class_t* Class_t::Fetch(Form_Type_e form_type, Bool_t do_auto_decrement)
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

    void Class_t::Log_Variable_Infos()
    {
        _MESSAGE("Logging Variables: %s", name);
        Variable_Info_t* variables = Variable_Infos();
        for (u64 idx = 0, size = Count_Variable_Infos(); idx < size; idx += 1) {
            Variable_Info_t& variable = variables[idx];
            _MESSAGE("name: %s", variable.name);
            _MESSAGE("    type: %u", variable.type);
            _MESSAGE("        name: %s\n", variable.type.To_String());
        }
    }

    void Class_t::Log_Property_Infos()
    {
        _MESSAGE("Logging Properties: %s", name);
        Property_Info_t* properties = Property_Infos();
        for (u64 idx = 0, size = Count_Property_Infos(); idx < size; idx += 1) {
            Property_Info_t& property = properties[idx];
            _MESSAGE("name: %s", property.name);
            _MESSAGE("    parent_name: %s", property.parent_name);
            _MESSAGE("    property_name: %s", property.property_name);
            _MESSAGE("    type: %s", property.type.To_String());
            _MESSAGE("    flags_20: %u", property.flags_20);
            _MESSAGE("    pad_24: %p", property.unk_24);
            _MESSAGE("    getter: %p", property.getter);
            _MESSAGE("    setter: %p", property.setter);
            _MESSAGE("    auto_var_idx: %p", property.auto_var_idx);
            _MESSAGE("    flags_3C: %u", property.flags_3C);
            _MESSAGE("    unk_40: %p\n", property.unk_40);
        }
    }

}}

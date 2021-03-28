/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cstring.h"

#include "doticu_skylib/game.h"
#include "doticu_skylib/game.inl"

#include "doticu_skylib/virtual_class.h"
#include "doticu_skylib/virtual_machine.h"

namespace doticu_skylib { namespace Virtual {

    maybe<Class_t*> Class_t::Find_Or_Load(String_t class_name, Bool_t do_decrement_on_find)
    {
        Class_t* vclass = nullptr;
        if (Machine_t::Self()->Do_Find_Or_Load_Class_1(class_name, vclass) && vclass) {
            if (do_decrement_on_find && vclass->Reference_Count() > 1) {
                vclass->Decrement_Reference();
            }
            return vclass;
        } else {
            return nullptr;
        }
    }

    maybe<Class_t*> Class_t::Find_Or_Load(Script_Type_e script_type, Bool_t do_decrement_on_find)
    {
        Class_t* vclass = nullptr;
        if (Machine_t::Self()->Do_Find_Or_Load_Class_2(script_type.Raw(), vclass) && vclass) {
            if (do_decrement_on_find && vclass->Reference_Count() > 1) {
                vclass->Decrement_Reference();
            }
            return vclass;
        } else {
            return nullptr;
        }
    }

    void Class_t::Destroy()
    {
        static auto destroy = reinterpret_cast
            <void(*)(Class_t*)>
            (Game_t::Base_Address() + static_cast<Word_t>(Offset_e::DESTROY));

        destroy(this);
    }

    u32 Class_t::Reference_Count()
    {
        return Atomic_Count_t::Atomic_Count();
    }

    u32 Class_t::Increment_Reference()
    {
        return Atomic_Count_t::Increment_Atomic();
    }

    u32 Class_t::Decrement_Reference()
    {
        u32 count = Atomic_Count_t::Decrement_Atomic();
        if (count < 1) {
            Destroy();
            Game_t::Deallocate<Class_t>(this);
        }
        return count;
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

    maybe<size_t> Class_t::Variable_Index(String_t variable_name)
    {
        Variable_Info_t* variables = Variable_Infos();
        for (size_t idx = 0, size = Count_Variable_Infos(); idx < size; idx += 1) {
            if (CString_t::Is_Same(variables[idx].name, variable_name, true)) {
                return idx;
            }
        }
        return none<size_t>();
    }

    maybe<size_t> Class_t::Property_Index(String_t property_name)
    {
        Property_Info_t* properties = Property_Infos();
        for (size_t idx = 0, size = Count_Property_Infos(); idx < size; idx += 1) {
            if (CString_t::Is_Same(properties[idx].name, property_name, true)) {
                return properties[idx].auto_var_idx;
            }
        }
        return none<size_t>();
    }

    Property_Info_t* Class_t::Property_Info(String_t property_name)
    {
        Property_Info_t* properties = Property_Infos();
        for (size_t idx = 0, size = Count_Property_Infos(); idx < size; idx += 1) {
            if (CString_t::Is_Same(properties[idx].name, property_name, true)) {
                return &properties[idx];
            }
        }
        return nullptr;
    }

    maybe<Script_Type_e> Class_t::Script_Type()
    {
        // user defined types do not have script types.

        Raw_Script_Type_t script_type;
        if (Machine_t::Self()->Get_Class_Script_Type(name, script_type)) {
            return Script_Type_e(script_type);
        } else {
            return none<Script_Type_e>();
        }
    }

    void Class_t::Log_Variable_Infos()
    {
        SKYLIB_LOG("Logging Variables: %s", name);
        Variable_Info_t* variables = Variable_Infos();
        for (size_t idx = 0, size = Count_Variable_Infos(); idx < size; idx += 1) {
            Variable_Info_t& variable = variables[idx];
            SKYLIB_LOG("name: %s", variable.name);
            SKYLIB_LOG("    type: %u", variable.type);
            SKYLIB_LOG("        name: %s\n", variable.type.To_String());
        }
    }

    void Class_t::Log_Property_Infos()
    {
        SKYLIB_LOG("Logging Properties: %s", name);
        Property_Info_t* properties = Property_Infos();
        for (size_t idx = 0, size = Count_Property_Infos(); idx < size; idx += 1) {
            Property_Info_t& property = properties[idx];
            SKYLIB_LOG("name: %s", property.name);
            SKYLIB_LOG("    parent_name: %s", property.parent_name);
            SKYLIB_LOG("    property_name: %s", property.property_name);
            SKYLIB_LOG("    type: %s", property.type.To_String());
            SKYLIB_LOG("    flags_20: %u", property.flags_20);
            SKYLIB_LOG("    pad_24: %p", property.unk_24);
            SKYLIB_LOG("    getter: %p", property.getter);
            SKYLIB_LOG("    setter: %p", property.setter);
            SKYLIB_LOG("    auto_var_idx: %p", property.auto_var_idx);
            SKYLIB_LOG("    flags_3C: %u", property.flags_3C);
            SKYLIB_LOG("    unk_40: %p\n", property.unk_40);
        }
    }

}}

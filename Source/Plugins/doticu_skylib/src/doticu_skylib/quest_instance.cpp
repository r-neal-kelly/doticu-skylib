/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <iomanip>
#include <sstream>

#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/game.h"
#include "doticu_skylib/global.h"
#include "doticu_skylib/quest_instance.h"

namespace doticu_skylib {

    maybe<Form_t*> Quest_Instance_Alias_t::Data_Form()
    {
        return Game_t::Form(this->data_form_id);
    }

    Global_Type_e Quest_Instance_Global_t::Type()
    {
        if (this->global) {
            return this->global->type;
        } else {
            return Global_Type_e::_NONE_;
        }
    }

    Bool_t Quest_Instance_Global_t::Is_Float()
    {
        return Type() == Global_Type_e::FLOAT;
    }

    Bool_t Quest_Instance_Global_t::Is_Short()
    {
        return Type() == Global_Type_e::SHORT;
    }

    Bool_t Quest_Instance_Global_t::Is_Long()
    {
        return Type() == Global_Type_e::LONG;
    }

    Float_t Quest_Instance_Global_t::Float()
    {
        return this->value;
    }

    s16 Quest_Instance_Global_t::Short()
    {
        return static_cast<s16>(this->value);
    }

    s32 Quest_Instance_Global_t::Long()
    {
        return static_cast<s32>(this->value);
    }

    std::string Quest_Instance_Global_t::Float_String()
    {
        std::ostringstream oss;
        oss << std::setprecision(2) << this->value;
        return oss.str();
    }

    std::string Quest_Instance_Global_t::Short_String()
    {
        return std::to_string(static_cast<s16>(this->value));
    }

    std::string Quest_Instance_Global_t::Long_String()
    {
        return std::to_string(static_cast<s32>(this->value));
    }

    maybe<Quest_Instance_Alias_t*> Quest_Instance_t::Alias(some<Alias_ID_t> alias_id)
    {
        for (size_t idx = 0, end = this->aliases.Count(); idx < end; idx += 1) {
            if (aliases[idx].alias_id == alias_id) {
                return &aliases[idx];
            }
        }
        return none<Quest_Instance_Alias_t*>();
    }

    maybe<Quest_Instance_Global_t*> Quest_Instance_t::Global(some<const char*> global_editor_id)
    {
        for (size_t idx = 0, end = this->globals.Count(); idx < end; idx += 1) {
            if (globals[idx].global && globals[idx].global->editor_id == global_editor_id()) {
                return &globals[idx];
            }
        }
        return none<Quest_Instance_Global_t*>();
    }

}

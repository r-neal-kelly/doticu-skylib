/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/magic_base.h"
#include "doticu_skylib/magic_effect.h"
#include "doticu_skylib/magic_effect_instance.h"

namespace doticu_skylib {

    Vector_t<some<Magic_Effect_t*>> Magic_Base_t::Magic_Effects()
    {
        Vector_t<some<Magic_Effect_t*>> results;
        Magic_Effects(results);
        return results;
    }

    void Magic_Base_t::Magic_Effects(Vector_t<some<Magic_Effect_t*>>& results)
    {
        for (size_t idx = 0, end = this->magic_effect_instances.Count(); idx < end; idx += 1) {
            maybe<Magic_Effect_Instance_t*> magic_effect_instance = this->magic_effect_instances[idx];
            if (magic_effect_instance && magic_effect_instance->base) {
                results.push_back(magic_effect_instance->base());
            }
        }
    }

    Bool_t Magic_Base_t::Can_Damage_Health()
    {
        for (size_t idx = 0, end = this->magic_effect_instances.Count(); idx < end; idx += 1) {
            maybe<Magic_Effect_Instance_t*> magic_effect_instance = this->magic_effect_instances[idx];
            if (magic_effect_instance) {
                maybe<Magic_Effect_t*> magic_effect = magic_effect_instance->base;
                if (magic_effect) {
                    if (magic_effect->magic_effect_flags.Is_Flagged(Magic_Effect_Flags_e::DETRIMENTAL)) {
                        if (magic_effect->archetype == Magic_Archetype_e::VALUE_MODIFIER) {
                            if (magic_effect->primary_actor_value == Actor_Value_Type_e::HEALTH) {
                                return true;
                            }
                        } else if (magic_effect->archetype == Magic_Archetype_e::DUAL_VALUE_MODIFIER) {
                            if (magic_effect->primary_actor_value == Actor_Value_Type_e::HEALTH ||
                                magic_effect->secondary_actor_value == Actor_Value_Type_e::HEALTH) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    void Magic_Base_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Magic_Base_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "component_name: %s", Name());
        SKYLIB_LOG(indent + SKYLIB_TAB + "form_id: %s", this->form_id.As_String());
        SKYLIB_LOG(indent + SKYLIB_TAB + "form_type: %s", this->form_type.As_String());

        SKYLIB_LOG(indent + SKYLIB_TAB + "keywords:");
        Keywords_c::Log_Component_Keywords(indent + SKYLIB_TAB + SKYLIB_TAB);

        SKYLIB_LOG(indent + "}");
    }

}

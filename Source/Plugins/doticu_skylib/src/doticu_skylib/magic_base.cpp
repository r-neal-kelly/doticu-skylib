/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/magic_base.h"
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

}

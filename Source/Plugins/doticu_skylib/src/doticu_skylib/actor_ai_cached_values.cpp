/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor_ai_cached_values.h"

namespace doticu_skylib {

    Bool_t Actor_AI_Cached_Values_t::Is_Ghost()
    {
        return this->cached_values_flags_2.Is_Flagged(Actor_AI_Cached_Values_Flags_2_e::IS_GHOST);
    }

    void Actor_AI_Cached_Values_t::Is_Ghost(Bool_t value)
    {
        if (value) {
            this->cached_values_flags_2.Flag(Actor_AI_Cached_Values_Flags_2_e::IS_GHOST);
        } else {
            this->cached_values_flags_2.Unflag(Actor_AI_Cached_Values_Flags_2_e::IS_GHOST);
        }
    }

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/component_actor_base_data.h"

namespace doticu_skylib {

    Bool_t Actor_Base_Data_c::Is_Male()
    {
        return !Is_Female();
    }

    Bool_t Actor_Base_Data_c::Is_Female()
    {
        return (actor_base_flags & Actor_Base_Flags_e::IS_FEMALE) != 0;
    }

    Bool_t Actor_Base_Data_c::Is_Unique()
    {
        return (actor_base_flags & Actor_Base_Flags_e::IS_UNIQUE) != 0;
    }

    Bool_t Actor_Base_Data_c::Is_Generic()
    {
        return !Is_Unique();
    }

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/virtual_machine.h"
#include "doticu_skylib/virtual_policy.h"

namespace doticu_skylib { namespace Virtual {

    Handle_Policy_t* Handle_Policy_t::Self()
    {
        return Machine_t::Self()->Handle_Policy();
    }

    Bind_Policy_t* Bind_Policy_t::Self()
    {
        return Machine_t::Self()->Bind_Policy();
    }

}}

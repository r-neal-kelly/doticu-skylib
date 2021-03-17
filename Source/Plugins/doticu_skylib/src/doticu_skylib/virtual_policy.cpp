/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.h"

#include "doticu_skylib/virtual_machine.h"
#include "doticu_skylib/virtual_policy.h"

namespace doticu_skylib { namespace Virtual {

    Handle_Policy_t* Handle_Policy_t::Self()
    {
        return Machine_t::Self()->Get_Handle_Policy_1();
    }

    Object_Policy_t* Object_Policy_t::Self()
    {
        return Machine_t::Self()->Get_Object_Policy_1();
    }

    void Object_Policy_t::Bind_Object(Object_t** object, Raw_Handle_t handle)
    {
        static auto bind_object = reinterpret_cast
            <void(*)(Object_Policy_t*, Object_t**, Raw_Handle_t)>
            (doticu_skylib::Game_t::Base_Address() + Offset_e::BIND_OBJECT);

        bind_object(this, object, handle);
    }

}}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/component_description.h"

#include "doticu_skylib/game.h"

namespace doticu_skylib {

    void Description_c::Description_DString(DString_t& result, some<Form_t*> parent, u32 sub_type)
    {
        static auto get = reinterpret_cast
            <void(*)(Description_c*, DString_t&, Form_t*, u32)>
            (Game_t::Base_Address() + Offset_e::GET);

        SKYLIB_ASSERT_SOME(parent);
        get(this, result, parent(), sub_type);
    }

}

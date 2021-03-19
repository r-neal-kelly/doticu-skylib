/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/component_description.h"

#include "doticu_skylib/game.h"

namespace doticu_skylib {

    DString_t Description_c::Description(some<const Form_t*> parent, u32 sub_type) const
    {
        DString_t description;
        Description(parent, sub_type, description);
        return std::move(description);
    }

    void Description_c::Description(some<const Form_t*> parent, u32 sub_type, DString_t& result) const
    {
        static auto get = reinterpret_cast
            <void(*)(const Description_c*, DString_t&, const Form_t*, u32)>
            (Game_t::Base_Address() + Offset_e::GET);

        SKYLIB_ASSERT_SOME(parent);

        get(this, result, parent(), sub_type);
    }

}

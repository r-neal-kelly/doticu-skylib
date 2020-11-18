/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/utils.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/worldspace.h"
#include "doticu_skylib/actor_base.h"

namespace doticu_skylib {

    const char* Reference_t::Name()
    {
        static auto get_name = reinterpret_cast
            <const char*(*)(Reference_t*)>
            (RelocationManager::s_baseAddr + static_cast<Word_t>(Offset_e::GET_NAME));
        return get_name(this);
    }

    const char* Reference_t::Base_Name()
    {
        return base_form ? static_cast<Actor_Base_t*>(base_form)->name.data : "";
    }

    String_t Reference_t::Any_Name()
    {
        const char* name = Name();
        if (!name || !name[0]) {
            name = base_form ? static_cast<Actor_Base_t*>(base_form)->Name() : "";
            if (!name || !name[0]) {
                return Form_ID_String();
            } else {
                return name;
            }
        } else {
            return name;
        }
    }

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/utils.h"
#include "doticu_skylib/virtual_arguments.h"
#include "doticu_skylib/virtual_variable.h"

namespace doticu_skylib { namespace Virtual {

    Bool_t Arguments_i::Array_t::Resize(u32 count)
    {
        static auto resize = reinterpret_cast
            <Bool_t(*)(Arguments_i::Array_t*, u32)>
            (RelocationManager::s_baseAddr + static_cast<Word_t>(Offset_e::RESIZE));
        return resize(this, count);
    }

    Variable_t* Arguments_i::Array_t::At(u32 idx)
    {
        if (idx < count) {
            return variables + idx;
        } else {
            return nullptr;
        }
    }

}}

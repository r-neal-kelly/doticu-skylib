/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/utils.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/location.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/worldspace.h"
#include "doticu_skylib/actor_base.h"

namespace doticu_skylib {

    Int_t Reference_Count_t::Reference_Count()
    {
        return reference_count & 0x3FF;
    }

    Int_t Reference_Count_t::Increment_Reference()
    {
        return _InterlockedIncrement(static_cast<volatile u32*>(&reference_count)) & 0x3FF;
    }

    Int_t Reference_Count_t::Decrement_Reference()
    {
        Int_t count = _InterlockedDecrement(static_cast<volatile u32*>(&reference_count));
        if ((count & 0x3FF) == 0) {
            delete this;
        }
        return count;
    }

    const char* Reference_t::Name()
    {
        static auto get_name = reinterpret_cast
            <const char*(*)(Reference_t*)>
            (RelocationManager::s_baseAddr + static_cast<Word_t>(Offset_e::GET_NAME));
        return get_name(this);
    }

    String_t Reference_t::Any_Name()
    {
        const char* name = Name();
        if (!name || !name[0]) {
            name = Get_Editor_ID();
            if (!name || !name[0]) {
                return Form_ID_String();
            } else {
                return name;
            }
        } else {
            return name;
        }
    }

    Location_t* Reference_t::Location()
    {
        Cell_t* cell = Cell();
        if (cell) {
            return Cell()->Location();
        } else {
            return nullptr;
        }
    }

    Cell_t* Reference_t::Cell()
    {
        return parent_cell;
    }

}

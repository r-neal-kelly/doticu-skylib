/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/utils.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/location.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/mod.h"
#include "doticu_skylib/worldspace.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/virtual.h"
#include "doticu_skylib/virtual_machine.h"

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
            delete this; // not sure this is right. might want to call MarkForDelete through virtual machine script (as if console)
        }
        return count;
    }

    Reference_t* Reference_t::Create(Form_t* base, u32 count, Reference_t* at, Bool_t force_persist, Bool_t initially_disable)
    {
        static auto place_at_me = reinterpret_cast
            <Reference_t*(*)(Virtual::Machine_t*, Virtual::Stack_ID_t, Reference_t*, Form_t*, u32, Bool_t, Bool_t)>
            (RelocationManager::s_baseAddr + Offset_e::PLACE_AT_ME);
        return place_at_me(Virtual::Machine_t::Self(), 0, at, base, count, force_persist, initially_disable);
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

    Index_t Live_References_t::Index_Of(Reference_t* reference)
    {
        if (reference && reference->Is_Valid()) {
            for (Index_t idx = 0, end = reference_entries.size(); idx < end; idx += 1) {
                if (reference_entries[idx].reference == reference) {
                    return idx;
                }
            }
            return -1;
        } else {
            return -1;
        }
    }

    Bool_t Live_References_t::Has(Reference_t* reference)
    {
        return Index_Of(reference) > -1;
    }

    Bool_t Live_References_t::Add(Reference_t* reference)
    {
        if (reference && reference->Is_Valid() && !Has(reference)) {
            Form_t* base_form = reference->base_form;
            if (base_form && base_form->Is_Valid() && base_form->Is_Static()) {
                Mod_t* base_mod = base_form->Indexed_Mod();
                SKYLIB_ASSERT(base_mod);

                s64 base_mod_index = mod_entries.Index_Of(base_mod);
                if (base_mod_index < 0) {
                    base_mod_index = mod_entries.size();
                    mod_entries.push_back(base_mod);
                }

                s64 reference_mod_index = -1;
                if (reference->Is_Static()) {
                    Mod_t* reference_mod = reference->Indexed_Mod();
                    SKYLIB_ASSERT(reference_mod);
                    reference_mod_index = mod_entries.Index_Of(reference_mod);
                    if (reference_mod_index < 0) {
                        reference_mod_index = mod_entries.size();
                        mod_entries.push_back(reference_mod);
                    }
                }

                reference_entries.emplace(reference_entries.end(),
                                          base_form, reference, base_mod_index, reference_mod_index);

                return true;
            } else {
                // currently don't know how to handle dynamic bases
                return false;
            }
        } else {
            return false;
        }
    }

    Bool_t Live_References_t::Remove(Reference_t* reference)
    {
        Index_t index = Index_Of(reference);
        size_t size = reference_entries.size();
        if (index > -1 && index < size) {
            reference_entries[index] = reference_entries[size - 1];
            reference_entries.erase(reference_entries.end() - 1);
            return true;
        } else {
            return false;
        }
    }

}

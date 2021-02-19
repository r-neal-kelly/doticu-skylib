/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/extra_data.inl"
#include "doticu_skylib/extra_reference_handle.h"
#include "doticu_skylib/reference.h"

namespace doticu_skylib {

    some<Extra_Reference_Handle_t*> Extra_Reference_Handle_t::Create(Reference_Handle_t reference_handle)
    {
        some<Extra_Reference_Handle_t*> x_reference_handle = Extra_Data_t::Create<Extra_Reference_Handle_t>();

        x_reference_handle->reference_handle = reference_handle;
        x_reference_handle->pad_14 = 0;

        return x_reference_handle;
    }

    some<Extra_Reference_Handle_t*> Extra_Reference_Handle_t::Create(some<Reference_t*> reference)
    {
        SKYLIB_ASSERT_SOME(reference);

        return Create(reference->To_Handle());
    }

    void Extra_Reference_Handle_t::Destroy(some<Extra_Reference_Handle_t*> x_reference_handle)
    {
        SKYLIB_ASSERT_SOME(x_reference_handle);

        Extra_Data_t::Destroy<Extra_Reference_Handle_t>(x_reference_handle);
    }

    maybe<Reference_t*> Extra_Reference_Handle_t::Reference()
    {
        return Reference_t::From_Handle(this->reference_handle);
    }

    void Extra_Reference_Handle_t::Reference(some<Reference_t*> reference)
    {
        SKYLIB_ASSERT_SOME(reference);

        this->reference_handle = reference->To_Handle();
    }

    void Extra_Reference_Handle_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Extra_Reference_Handle_t::Log");
        SKYLIB_LOG(indent + "{");

        maybe<Reference_t*> reference = Reference();
        if (reference) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "reference:");
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_TAB + "form_type: %s, form_id: %s, name: %s",
                       Form_Type_e::To_String(reference->form_type),
                       reference->Form_ID_String(),
                       reference->Any_Name());
            if (reference->base_form) {
                SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_TAB + "base_form_type: %s, base_form_id: %s, base_name: %s",
                           Form_Type_e::To_String(reference->base_form->form_type),
                           reference->base_form->Form_ID_String(),
                           reference->base_form->Component_Name());
            }
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "reference: (none)");
        }

        SKYLIB_LOG(indent + "}");
    }

}

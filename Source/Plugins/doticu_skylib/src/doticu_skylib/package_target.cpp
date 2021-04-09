/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/form.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/object.h"
#include "doticu_skylib/package_target.h"
#include "doticu_skylib/reference.h"

namespace doticu_skylib {

    Package_Target_t::Target_u::Target_u() :
        linked_form(none<Form_t*>())
    {
    }

    Package_Target_t::Target_u::~Target_u()
    {
        this->linked_form = none<Form_t*>();
    }

    Alias_ID_t Package_Target_t::Alias_ID() const
    {
        SKYLIB_ASSERT(this->target_type == Package_Target_Type_e::ALIAS_ID);

        return this->target.alias_id;
    }

    void Package_Target_t::Alias_ID(Alias_ID_t alias_id)
    {
        SKYLIB_ASSERT(this->target_type == Package_Target_Type_e::ALIAS_ID);

        this->target.alias_id = alias_id;
    }

    maybe<Form_Type_e> Package_Target_t::Form_Type() const
    {
        SKYLIB_ASSERT(this->target_type == Package_Target_Type_e::FORM_TYPE);

        return this->target.form_type;
    }

    void Package_Target_t::Form_Type(maybe<Form_Type_e> form_type)
    {
        SKYLIB_ASSERT(this->target_type == Package_Target_Type_e::FORM_TYPE);

        this->target.form_type = form_type;
    }

    maybe<Form_t*> Package_Target_t::Linked_Form() const
    {
        SKYLIB_ASSERT(this->target_type == Package_Target_Type_e::LINKED_FORM);

        return this->target.linked_form;
    }

    void Package_Target_t::Linked_Form(maybe<Form_t*> linked_form)
    {
        SKYLIB_ASSERT(this->target_type == Package_Target_Type_e::LINKED_FORM);

        this->target.linked_form = linked_form;
    }

    maybe<Object_t*> Package_Target_t::Object() const
    {
        SKYLIB_ASSERT(this->target_type == Package_Target_Type_e::OBJECT);

        return this->target.object;
    }

    void Package_Target_t::Object(maybe<Object_t*> object)
    {
        SKYLIB_ASSERT(this->target_type == Package_Target_Type_e::OBJECT);

        this->target.object = object;
    }

    maybe<Reference_t*> Package_Target_t::Reference() const
    {
        SKYLIB_ASSERT(this->target_type == Package_Target_Type_e::REFERENCE_HANDLE);

        return Reference_t::From_Handle(this->target.reference_handle);
    }

    void Package_Target_t::Reference(maybe<Reference_t*> reference)
    {
        SKYLIB_ASSERT(this->target_type == Package_Target_Type_e::REFERENCE_HANDLE);

        if (reference) {
            this->target.reference_handle = reference->To_Handle();
        } else {
            this->target.reference_handle = Reference_t::Invalid_Handle();
        }
    }

    void Package_Target_t::Log(std::string indent) const
    {
        SKYLIB_LOG(indent + "Package_Target_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "target_type: %s", this->target_type.As_String());
        SKYLIB_LOG(indent + SKYLIB_TAB + "count_or_distance: %i", this->count_or_distance);

        if (this->target_type == Package_Target_Type_e::ALIAS_ID) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "alias_id: %u", Alias_ID());
        } else if (this->target_type == Package_Target_Type_e::FORM_TYPE) {
            maybe<Form_Type_e> form_type = Form_Type();
            SKYLIB_LOG(indent + SKYLIB_TAB + "form_type: %s", form_type().As_String());
        } else if (this->target_type == Package_Target_Type_e::LINKED_FORM) {
            maybe<Form_t*> linked_form = Linked_Form();
            if (linked_form) {
                SKYLIB_LOG(indent + SKYLIB_TAB + "linked_form:");
                linked_form->Log_Name_And_Type(indent + SKYLIB_TAB + SKYLIB_TAB);
            } else {
                SKYLIB_LOG(indent + SKYLIB_TAB + "linked_form: (none)");
            }
        } else if (this->target_type == Package_Target_Type_e::OBJECT) {
            maybe<Object_t*> object = Object();
            if (object) {
                SKYLIB_LOG(indent + SKYLIB_TAB + "object:");
                object->Log_Name_And_Type(indent + SKYLIB_TAB + SKYLIB_TAB);
            } else {
                SKYLIB_LOG(indent + SKYLIB_TAB + "object: (none)");
            }
        } else if (this->target_type == Package_Target_Type_e::REFERENCE_HANDLE) {
            maybe<Reference_t*> reference = Reference();
            if (reference) {
                SKYLIB_LOG(indent + SKYLIB_TAB + "reference:");
                reference->Log_Name_And_Type(indent + SKYLIB_TAB + SKYLIB_TAB);
            } else {
                SKYLIB_LOG(indent + SKYLIB_TAB + "reference: (none)");
            }
        } else if (this->target_type == Package_Target_Type_e::SELF) {

        } else if (this->target_type == Package_Target_Type_e::UNKNOWN_5) {

        }

        SKYLIB_LOG(indent + "}");
    }

}

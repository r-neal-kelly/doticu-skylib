/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cell.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/object.h"
#include "doticu_skylib/package_location.h"
#include "doticu_skylib/reference.h"

namespace doticu_skylib {

    Package_Location_t::Location_u::Location_u() :
        linked_form(none<Form_t*>())
    {
    }

    Package_Location_t::Location_u::~Location_u()
    {
        this->linked_form = none<Form_t*>();
    }

    Alias_ID_t Package_Location_t::Alias_ID() const
    {
        SKYLIB_ASSERT(this->location_type == Package_Location_Type_e::ALIAS_LOCATION ||
                      this->location_type == Package_Location_Type_e::ALIAS_REFERENCE);

        return this->location.alias_id;
    }

    void Package_Location_t::Alias_ID(Alias_ID_t alias_id)
    {
        SKYLIB_ASSERT(this->location_type == Package_Location_Type_e::ALIAS_LOCATION ||
                      this->location_type == Package_Location_Type_e::ALIAS_REFERENCE);

        this->location.alias_id = alias_id;
    }

    maybe<Cell_t*> Package_Location_t::Cell() const
    {
        SKYLIB_ASSERT(this->location_type == Package_Location_Type_e::CELL);

        return this->location.cell;
    }

    void Package_Location_t::Cell(maybe<Cell_t*> cell)
    {
        SKYLIB_ASSERT(this->location_type == Package_Location_Type_e::CELL);

        this->location.cell = cell;
    }

    maybe<Form_Type_e> Package_Location_t::Form_Type() const
    {
        SKYLIB_ASSERT(this->location_type == Package_Location_Type_e::FORM_TYPE);

        return this->location.form_type;
    }

    void Package_Location_t::Form_Type(maybe<Form_Type_e> form_type)
    {
        SKYLIB_ASSERT(this->location_type == Package_Location_Type_e::FORM_TYPE);

        this->location.form_type = form_type;
    }

    maybe<Form_t*> Package_Location_t::Linked_Form() const
    {
        SKYLIB_ASSERT(this->location_type == Package_Location_Type_e::LINKED_FORM);

        return this->location.linked_form;
    }

    void Package_Location_t::Linked_Form(maybe<Form_t*> linked_form)
    {
        SKYLIB_ASSERT(this->location_type == Package_Location_Type_e::LINKED_FORM);

        this->location.linked_form = linked_form;
    }

    maybe<Object_t*> Package_Location_t::Object() const
    {
        SKYLIB_ASSERT(this->location_type == Package_Location_Type_e::OBJECT);

        return this->location.object;
    }

    void Package_Location_t::Object(maybe<Object_t*> object)
    {
        SKYLIB_ASSERT(this->location_type == Package_Location_Type_e::OBJECT);

        this->location.object = object;
    }

    u32 Package_Location_t::Radius() const
    {
        return this->radius;
    }

    void Package_Location_t::Radius(u32 radius)
    {
        this->radius = radius;
    }

    maybe<Reference_t*> Package_Location_t::Reference() const
    {
        SKYLIB_ASSERT(this->location_type == Package_Location_Type_e::REFERENCE_HANDLE);

        return Reference_t::From_Handle(this->location.reference_handle);
    }

    void Package_Location_t::Reference(maybe<Reference_t*> reference)
    {
        SKYLIB_ASSERT(this->location_type == Package_Location_Type_e::REFERENCE_HANDLE);

        if (reference) {
            this->location.reference_handle = reference->To_Handle();
        } else {
            this->location.reference_handle = Reference_t::Invalid_Handle();
        }
    }

    void Package_Location_t::Log(std::string indent) const
    {
        SKYLIB_LOG(indent + "Package_Location_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "location_type: %s", this->location_type.As_String());

        if (this->location_type == Package_Location_Type_e::ALIAS_LOCATION) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "alias_location_id: %u", Alias_ID());
        } else if (this->location_type == Package_Location_Type_e::ALIAS_REFERENCE) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "alias_reference_id: %u", Alias_ID());
        } else if (this->location_type == Package_Location_Type_e::CELL) {
            maybe<Cell_t*> cell = Cell();
            if (cell) {
                SKYLIB_ASSERT(cell->Is_Cell());
                SKYLIB_LOG(indent + SKYLIB_TAB + "cell:");
                cell->Log_Name_And_Type(indent + SKYLIB_TAB + SKYLIB_TAB);
            } else {
                SKYLIB_LOG(indent + SKYLIB_TAB + "cell: (none)");
            }
        } else if (this->location_type == Package_Location_Type_e::FORM_TYPE) {
            maybe<Form_Type_e> form_type = Form_Type();
            if (form_type) {
                SKYLIB_LOG(indent + SKYLIB_TAB + "form_type: %s", form_type().As_String());
            } else {
                SKYLIB_LOG(indent + SKYLIB_TAB + "form_type: (none)");
            }
        } else if (this->location_type == Package_Location_Type_e::LINKED_FORM) {
            maybe<Form_t*> linked_form = Linked_Form();
            if (linked_form) {
                SKYLIB_LOG(indent + SKYLIB_TAB + "linked_form:");
                linked_form->Log_Name_And_Type(indent + SKYLIB_TAB + SKYLIB_TAB);
            } else {
                SKYLIB_LOG(indent + SKYLIB_TAB + "linked_form: (none)");
            }
        } else if (this->location_type == Package_Location_Type_e::OBJECT) {
            maybe<Object_t*> object = Object();
            if (object) {
                SKYLIB_LOG(indent + SKYLIB_TAB + "object:");
                object->Log_Name_And_Type(indent + SKYLIB_TAB + SKYLIB_TAB);
            } else {
                SKYLIB_LOG(indent + SKYLIB_TAB + "object: (none)");
            }
        } else if (this->location_type == Package_Location_Type_e::REFERENCE_HANDLE) {
            maybe<Reference_t*> reference = Reference();
            if (reference) {
                SKYLIB_LOG(indent + SKYLIB_TAB + "reference:");
                reference->Log_Name_And_Type(indent + SKYLIB_TAB + SKYLIB_TAB);
            } else {
                SKYLIB_LOG(indent + SKYLIB_TAB + "reference: (none)");
            }
        } else if (this->location_type == Package_Location_Type_e::UNKNOWN_10 ||
                   this->location_type == Package_Location_Type_e::UNKNOWN_11) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "unknown: %p", this->location.linked_form);
        }

        SKYLIB_LOG(indent + "}");
    }

}

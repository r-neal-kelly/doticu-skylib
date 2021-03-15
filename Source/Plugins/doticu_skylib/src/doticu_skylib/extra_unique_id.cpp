/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/actor.h"
#include "doticu_skylib/enum_form_type.h"
#include "doticu_skylib/extra_data.inl"
#include "doticu_skylib/extra_unique_id.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/reference.h"

namespace doticu_skylib {

    some<Extra_Unique_ID_t*> Extra_Unique_ID_t::Create()
    {
        some<Extra_Unique_ID_t*> x_unique_id = Extra_Data_t::Create<Extra_Unique_ID_t>();

        x_unique_id->form_id = 0;
        x_unique_id->unique_id = 0;
        x_unique_id->pad_16 = 0;

        return x_unique_id;
    }

    some<Extra_Unique_ID_t*> Extra_Unique_ID_t::Create(Form_ID_t form_id, u16 unique_id)
    {
        some<Extra_Unique_ID_t*> x_unique_id = Create();

        x_unique_id->Form_ID(form_id);
        x_unique_id->Unique_ID(unique_id);

        return x_unique_id;
    }

    some<Extra_Unique_ID_t*> Extra_Unique_ID_t::Create(const Extra_Unique_ID_t& other)
    {
        some<Extra_Unique_ID_t*> x_unique_id = Extra_Data_t::Create<Extra_Unique_ID_t>();

        x_unique_id->form_id = other.form_id;
        x_unique_id->unique_id = other.unique_id;
        x_unique_id->pad_16 = other.pad_16;

        return x_unique_id;
    }

    void Extra_Unique_ID_t::Destroy(some<Extra_Unique_ID_t*> x_unique_id)
    {
        SKYLIB_ASSERT_SOME(x_unique_id);

        Extra_Data_t::Destroy<Extra_Unique_ID_t>(x_unique_id);
    }

    Form_ID_t Extra_Unique_ID_t::Form_ID() const
    {
        return this->form_id;
    }

    void Extra_Unique_ID_t::Form_ID(Form_ID_t form_id)
    {
        this->form_id = form_id;
    }

    u16 Extra_Unique_ID_t::Unique_ID() const
    {
        return this->unique_id;
    }

    void Extra_Unique_ID_t::Unique_ID(u16 unique_id)
    {
        this->unique_id = unique_id;
    }

    maybe<Form_t*> Extra_Unique_ID_t::Form() const
    {
        if (this->form_id) {
            return Game_t::Form(this->form_id);
        } else {
            return none<Form_t*>();
        }
    }

    void Extra_Unique_ID_t::Form(maybe<Form_t*> form)
    {
        if (form) {
            this->form_id = form->form_id;
        } else {
            this->form_id = 0;
        }
    }

    maybe<Reference_t*> Extra_Unique_ID_t::Reference() const
    {
        maybe<Form_t*> form = Form();
        if (form) {
            return form->As_Reference();
        } else {
            return none<Reference_t*>();
        }
    }

    void Extra_Unique_ID_t::Reference(maybe<Reference_t*> reference)
    {
        if (reference) {
            this->form_id = reference->form_id;
        } else {
            this->form_id = 0;
        }
    }

    maybe<Actor_t*> Extra_Unique_ID_t::Actor() const
    {
        maybe<Form_t*> form = Form();
        if (form) {
            return form->As_Actor();
        } else {
            return none<Actor_t*>();
        }
    }

    void Extra_Unique_ID_t::Actor(maybe<Actor_t*> actor)
    {
        if (actor) {
            this->form_id = actor->form_id;
        } else {
            this->form_id = 0;
        }
    }

    void Extra_Unique_ID_t::Log(std::string indent) const
    {
        SKYLIB_LOG(indent + "Extra_Unique_ID_t::Log");
        SKYLIB_LOG(indent + "{");

        maybe<Reference_t*> reference = Reference();
        if (reference) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "form_id: %s, form_type: %s, any_name: %s",
                       reference->form_id.As_String(), reference->form_type.As_String(), reference->Any_Name());
        } else {
            maybe<Form_t*> form = Form();
            if (form) {
                SKYLIB_LOG(indent + SKYLIB_TAB + "form_id: %s, form_type: %s",
                           form->form_id.As_String(), form->form_type.As_String());
            } else {
                SKYLIB_LOG(indent + SKYLIB_TAB + "form_id: (none)");
            }
        }

        SKYLIB_LOG(indent + SKYLIB_TAB + "unique_id: %u", Unique_ID());

        SKYLIB_LOG(indent + "}");
    }

}

/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/extra_data.inl"
#include "doticu_skylib/extra_owner.h"
#include "doticu_skylib/faction.h"

namespace doticu_skylib {

    some<Extra_Owner_t*> Extra_Owner_t::Create()
    {
        some<Extra_Owner_t*> x_owner = Extra_Data_t::Create<Extra_Owner_t>();

        x_owner->form_owner = none<Form_t*>();

        return x_owner;
    }

    some<Extra_Owner_t*> Extra_Owner_t::Create(Form_Owner_t form_owner)
    {
        some<Extra_Owner_t*> x_owner = Extra_Data_t::Create<Extra_Owner_t>();

        x_owner->Form_Owner(form_owner);

        return x_owner;
    }

    some<Extra_Owner_t*> Extra_Owner_t::Create(const Extra_Owner_t& other)
    {
        some<Extra_Owner_t*> x_owner = Extra_Data_t::Create<Extra_Owner_t>();

        x_owner->form_owner = other.form_owner;

        return x_owner;
    }

    void Extra_Owner_t::Destroy(some<Extra_Owner_t*> x_owner)
    {
        SKYLIB_ASSERT_SOME(x_owner);

        Extra_Data_t::Destroy<Extra_Owner_t>(x_owner);
    }

    Form_Owner_t Extra_Owner_t::Form_Owner()
    {
        return this->form_owner;
    }

    void Extra_Owner_t::Form_Owner(Form_Owner_t form_owner)
    {
        this->form_owner = form_owner;
    }

    void Extra_Owner_t::Log(std::string indent) const
    {
        SKYLIB_LOG(indent + "Extra_Owner_t::Log");
        SKYLIB_LOG(indent + "{");

        if (this->form_owner) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "form_owner:");
            this->form_owner.Log(indent + SKYLIB_TAB + SKYLIB_TAB);
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "form_owner: (none)");
        }

        SKYLIB_LOG(indent + "}");
    }

}

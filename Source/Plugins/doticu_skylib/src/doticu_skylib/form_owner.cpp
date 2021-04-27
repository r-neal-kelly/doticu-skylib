/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/faction.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/form_owner.h"

namespace doticu_skylib {

    Form_Owner_t::Form_Owner_t() :
        form(none<Form_t*>())
    {
    }

    Form_Owner_t::Form_Owner_t(Form_t* form) :
        form(form)
    {
    }

    Form_Owner_t::Form_Owner_t(Actor_Base_t* actor_base) :
        form(actor_base)
    {
    }

    Form_Owner_t::Form_Owner_t(Faction_t* faction) :
        form(faction)
    {
    }

    Form_Owner_t::Form_Owner_t(std::nullptr_t form) :
        form(form)
    {
    }

    Form_Owner_t::Form_Owner_t(none<Form_t*> form) :
        form(form())
    {
    }

    Form_Owner_t::Form_Owner_t(none<Actor_Base_t*> actor_base) :
        form(actor_base())
    {
    }

    Form_Owner_t::Form_Owner_t(none<Faction_t*> faction) :
        form(faction())
    {
    }

    Form_Owner_t::Form_Owner_t(maybe<Form_t*> form) :
        form(form)
    {
    }

    Form_Owner_t::Form_Owner_t(maybe<Actor_Base_t*> actor_base) :
        form(actor_base)
    {
    }

    Form_Owner_t::Form_Owner_t(maybe<Faction_t*> faction) :
        form(faction)
    {
    }

    Form_Owner_t::Form_Owner_t(some<Form_t*> form) :
        form(form())
    {
    }

    Form_Owner_t::Form_Owner_t(some<Actor_Base_t*> actor_base) :
        form(actor_base())
    {
    }

    Form_Owner_t::Form_Owner_t(some<Faction_t*> faction) :
        form(faction())
    {
    }

    Form_Owner_t::Form_Owner_t(const Form_Owner_t& other) :
        form(other.form)
    {
    }

    Form_Owner_t::Form_Owner_t(Form_Owner_t&& other) noexcept :
        form(std::exchange(other.form, none<Form_t*>()))
    {
    }

    Form_Owner_t& Form_Owner_t::operator =(const Form_Owner_t& other)
    {
        if (this != std::addressof(other)) {
            this->form = other.form;
        }
        return *this;
    }

    Form_Owner_t& Form_Owner_t::operator =(Form_Owner_t&& other) noexcept
    {
        if (this != std::addressof(other)) {
            this->form = std::exchange(other.form, none<Form_t*>());
        }
        return *this;
    }

    Form_Owner_t::~Form_Owner_t()
    {
        this->form = none<Form_t*>();
    }

    Bool_t Form_Owner_t::Is_Actor_Base() const
    {
        return this->form && this->form->Is_Actor_Base();
    }

    Bool_t Form_Owner_t::Is_Faction() const
    {
        return this->form && this->form->Is_Faction();
    }

    maybe<Form_t*> Form_Owner_t::As_Form() const
    {
        return this->form;
    }

    maybe<Actor_Base_t*> Form_Owner_t::As_Actor_Base() const
    {
        if (this->form) {
            return this->form->As_Actor_Base();
        } else {
            return none<Actor_Base_t*>();
        }
    }

    maybe<Faction_t*> Form_Owner_t::As_Faction() const
    {
        if (this->form) {
            return this->form->As_Faction();
        } else {
            return none<Faction_t*>();
        }
    }

    Form_Owner_t::operator Bool_t() const
    {
        return this->form != none<Form_t*>();
    }

    maybe<Form_t*> Form_Owner_t::operator ()() const
    {
        return this->form;
    }

    void Form_Owner_t::Log(std::string indent) const
    {
        SKYLIB_LOG(indent + "Form_Owner_t::Log");
        SKYLIB_LOG(indent + "{");

        if (this->form) {
            if (this->form->Is_Actor_Base()) {
                SKYLIB_LOG(indent + SKYLIB_TAB + "actor_base:");
                this->form->Log_Name_And_Type(indent + SKYLIB_TAB + SKYLIB_TAB);
            } else if (this->form->Is_Faction()) {
                SKYLIB_LOG(indent + SKYLIB_TAB + "faction:");
                this->form->Log_Name_And_Type(indent + SKYLIB_TAB + SKYLIB_TAB);
            } else {
                SKYLIB_LOG(indent + SKYLIB_TAB + "form:");
                this->form->Log_Name_And_Type(indent + SKYLIB_TAB + SKYLIB_TAB);
            }
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "form: (none)");
        }

        SKYLIB_LOG(indent + "}");
    }

}
